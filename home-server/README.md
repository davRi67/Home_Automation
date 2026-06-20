# home-server

Backend du hub domotique local : pilotage et supervision des objets connectés
(cat fountain, weather station, mini bar) depuis une Raspberry Pi.

## Stack

- **FastAPI** — API REST du hub
- **Uvicorn** — serveur ASGI
- Python ≥ 3.12

## Démarrage

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -e ".[dev]"
```

Lancer le serveur (TODO — à compléter au Module 3) :

```bash
# uvicorn homeserver.main:app --reload
```

## Documentation

- Exigences du projet : [REQUIREMENTS.md](./REQUIREMENTS.md)
