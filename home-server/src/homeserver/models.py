from pydantic import BaseModel


class Device(BaseModel):
    # les quatre champs, avec leurs types
    id: str
    name: str
    type: str
    state: dict


class Command(BaseModel):
    # le champ command
    command: str
