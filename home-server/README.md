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

┌──────────────────────────────────────────────┐
│ 1 · CLIENT / ACTEURS                           │
│    Arduino · navigateur · curl · mobile        │
│    « lire ou changer l'état d'un device »      │
└───────────────────┬────────────────────────────┘
                    │   ⇅  JSON via HTTP
                    │      (texte sur le réseau, non typé)
┌───────────────────▼────────────────────────────┐
│ 2 · COUCHE WEB — FastAPI  (main.py)            │
│    @app.get / @app.post                         │
│    reçoit le HTTP → valide (Pydantic) → renvoie │
│    ★ AUCUNE ligne de SQL ici                    │
└───────────────────┬────────────────────────────┘
                    │   ⇅  objets Device (Pydantic)
                    │      typés, validés, en mémoire
┌───────────────────▼────────────────────────────┐
│ 3 · COUCHE REPOSITORY — storage.py             │
│    seul endroit qui connaît la base             │
│    convertit : Row SQL ⇄ Device                 │
│    json.loads / json.dumps sur `state`          │
│    list_devices · get_device · upsert · set_state│
└───────────────────┬────────────────────────────┘
                    │   ⇅  SQL + lignes (Row)
                    │      tuples bruts, jamais exposés vers le haut
┌───────────────────▼────────────────────────────┐
│ 4 · BASE — SQLite  (un fichier .db)            │
│    survit au redémarrage                        │
│    colonne state = TEXT  (du JSON en chaîne)    │
└──────────────────────────────────────────────┘