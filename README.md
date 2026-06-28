# Home Automation

Système domotique personnel : un hub local sur Raspberry Pi pilotant et
supervisant des objets connectés faits maison, accessible à distance.

## Vision

Une plateforme d'automatisation **contrôlée localement** et **accessible à
distance**, construite avec du code sur mesure plutôt qu'une solution clé en
main — pour la maintenabilité et la traçabilité.

L'indépendance vis-à-vis d'internet est une exigence de premier ordre : le hub
fonctionne sur le réseau local, sans dépendre du cloud.

## Architecture

Un point central unique — le Raspberry Pi 4 — agrège les données des devices via
MQTT, exécute la logique d'automatisation et expose les dashboards. Les objets
connectés communiquent sur le réseau local ; l'accès distant passe par un VPN
WireGuard (Tailscale), sans port forwarding.

## Composants

| Dossier        | Rôle                                          |
|----------------|-----------------------------------------------|
| `home-server/` | Backend du hub (API REST FastAPI, persistance, logique métier) |
| `firmware/`    | Firmware des objets connectés (Arduino / ESP32, PlatformIO) |
| `hardware/`    | Conception des PCB custom (LibrePCB) — _emplacement réservé_ |

## Objets connectés

Le projet est construit objet par objet, chacun isolé pour maîtriser une
complexité à la fois.

- 🐱 **Cat fountain** — fontaine à eau connectée avec détection de niveau et
  protection contre le fonctionnement à sec _(Phase 2)_
- 🌦️ **Weather station** — station météo : température, humidité, pression,
  affichage local _(Phase 3)_
- 🍸 **Mini bar** — bar automatisé _(Phase 5)_

L'ordre des phases reflète la roadmap d'architecture, pas l'état d'avancement —
celui-ci est suivi dans les commits et la roadmap détaillée.

## Stack technique

- **Backend :** Python, FastAPI, MQTT (Mosquitto), SQLite, InfluxDB, Grafana
- **Firmware :** Arduino / ESP32 (ESP32-S3), PlatformIO
- **Hardware :** LibrePCB
- **Accès distant :** Tailscale (VPN WireGuard)

## Approche

Le projet suit une démarche _requirements-first_ : les exigences fonctionnelles
et non-fonctionnelles sont tracées (FR / NFR), liées à des tests, eux-mêmes liés
aux commits. Voir [`home-server/REQUIREMENTS.md`](./home-server/REQUIREMENTS.md)
pour les exigences du backend.

## Documentation

Chaque composant possède son propre README. Démarrage du backend :
voir [`home-server/README.md`](./home-server/README.md).
