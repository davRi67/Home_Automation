import json
import os
import sqlite3
from contextlib import closing

from .models import Device

# Configurable via env var pour les tests (injecter un chemin temporaire).
# Défaut : "homeserver.db" à la racine du projet.
DB_PATH = os.environ.get("HOMESERVER_DB", "homeserver.db")


def _connect():
    # Point unique d'ouverture : row_factory permet l'accès par nom (row["state"]).
    con = sqlite3.connect(DB_PATH)
    con.row_factory = sqlite3.Row
    return con


def _row_to_device(row) -> Device:
    # Frontière SQL -> modèle API : json.loads restitue le state en dict.
    return Device(
        id=row["id"],
        name=row["name"],
        type=row["type"],
        state=json.loads(row["state"]),
    )


def init_db() -> None:
    # Idempotent : safe à appeler à chaque démarrage.
    with closing(_connect()) as con, con:
        con.execute(
            """CREATE TABLE IF NOT EXISTS devices (
                id    TEXT PRIMARY KEY,
                name  TEXT NOT NULL,
                type  TEXT NOT NULL,
                state TEXT NOT NULL
            )"""
        )


def list_devices() -> list[Device]:
    with closing(_connect()) as con:
        rows = con.execute("SELECT id, name, type, state FROM devices").fetchall()
        return [_row_to_device(r) for r in rows]


def get_device(device_id: str) -> Device | None:
    # Retourne None si absent — l'endpoint en fait un 404.
    with closing(_connect()) as con:
        row = con.execute(
            "SELECT id, name, type, state FROM devices WHERE id = ?",
            (device_id,),
        ).fetchone()
        return _row_to_device(row) if row else None


def set_state(device_id: str, new_state: dict) -> None:
    # dict -> JSON juste avant le SQL.
    with closing(_connect()) as con, con:
        con.execute(
            "UPDATE devices SET state = ? WHERE id = ?",
            (json.dumps(new_state), device_id),
        )


def upsert_device(device: Device) -> None:
    # Prend un Device entier : l'objet du domaine est l'unité d'échange.
    with closing(_connect()) as con, con:
        con.execute(
            """INSERT INTO devices (id, name, type, state)
               VALUES (?, ?, ?, ?)
               ON CONFLICT(id) DO UPDATE SET
                   name  = excluded.name,
                   type  = excluded.type,
                   state = excluded.state""",
            (device.id, device.name, device.type, json.dumps(device.state)),
        )

def count_devices() -> int:
    # Sert au test de garde du seeding : 0 => table vide => on peut semer.
    with closing(_connect()) as con:
        return con.execute("SELECT COUNT(*) FROM devices").fetchone()[0]


def seed_default_devices() -> None:
    # Sème les devices de départ UNIQUEMENT si la table est vide.
    # Le garde-fou empêche d'écraser l'état modifié à chaque redémarrage.
    if count_devices() > 0:
        return  # déjà peuplée : on ne touche à rien

    defaults = [
        Device(id="fountain_01", name="Fontaine du salon", type="fountain",
               state={"motor": "off", "water_level": 1.0}),
        Device(id="weather_01", name="Station météo", type="weather",
               state={"temperature": None, "humidity": None}),
    ]
    for device in defaults:
        upsert_device(device)