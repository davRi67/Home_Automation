from fastapi import FastAPI, HTTPException
from .models import Device, Command


app = FastAPI(title="Home Automation Hub")
DEVICES: dict[str, Device] = {
    "weather-01": Device(id="weather-01", name="BME280", type="sensor", state={"online": True}),
    "cat_fountain-01": Device(
        id="cat_fountain-01", name="Niveau d'eau", type="sensor", state={"online": True}
    ),
}


@app.get("/")
def read_root():
    return {"status": "ok", "service": "home-automation-hub"}


@app.get("/health")
def health_check():
    return {"status": "healthy"}


@app.get("/devices")
def list_devices():
    devices = list(DEVICES.values())
    return {"devices": devices}


@app.get("/devices/{device_id}")
def get_device(device_id: str):
    device = DEVICES.get(device_id)
    if device:
        return {"device": device}
    else:
        raise HTTPException(status_code=404, detail="Device not found")


@app.post("/devices/{device_id}/command")
def add_command(device_id: str, command: Command):
    device = DEVICES.get(device_id)
    if not device:
        raise HTTPException(status_code=404, detail="Device not found")
    # Process the command (implementation depends on your needs)
    device.state["last_command"] = (
        command.command
    )  # Example of updating device state with the command
    return {"message": "Command added successfully", "command": command}
