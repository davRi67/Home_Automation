from contextlib import asynccontextmanager

from fastapi import FastAPI, HTTPException

from . import storage
from .models import Command, Device  # noqa: F401  (Device utile si tu types ailleurs)


@asynccontextmanager
async def lifespan(app: FastAPI):
    storage.init_db()
    storage.seed_default_devices()
    yield


app = FastAPI(title="Home Automation Hub", lifespan=lifespan)
# Plus de dict DEVICES : la base SQLite est désormais l'unique source de vérité.


@app.get("/")
def read_root():
    return {"status": "ok", "service": "home-automation-hub"}


@app.get("/health")
def health_check():
    return {"status": "healthy"}


@app.get("/devices")
def list_devices():
    # storage rend une list[Device] ; on garde l'enveloppe pour ne rien changer côté client.
    return {"devices": storage.list_devices()}


@app.get("/devices/{device_id}")
def get_device(device_id: str):
    device = storage.get_device(device_id)
    if device is None:                       # None venu du repository = device absent
        raise HTTPException(status_code=404, detail="Device not found")
    return {"device": device}


@app.post("/devices/{device_id}/command")
def add_command(device_id: str, command: Command):
    device = storage.get_device(device_id)
    if device is None:
        raise HTTPException(status_code=404, detail="Device not found")

    # On modifie le dict state EN MÉMOIRE...
    device.state["last_command"] = command.command
    # ...puis on PERSISTE via la couche stockage. Sans cette ligne, rien n'est écrit.
    storage.set_state(device_id, device.state)

    return {"message": "Command added successfully", "command": command}