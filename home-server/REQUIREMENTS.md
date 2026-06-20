# Exigences — home-server

Hub domotique local pilotant des objets connectés (cat fountain, weather
station, mini bar) depuis une Raspberry Pi.

## Portée (scope)

Backend du hub : API REST locale, communication avec les objets connectés,
supervision et stockage des données.

## Exigences fonctionnelles

| ID    | Exigence                                                        | Statut  |
|-------|-----------------------------------------------------------------|---------|
| FR-1  | Le système expose une API REST accessible localement.           | À faire |
| FR-2  | Le système liste les objets connectés disponibles.              | À faire |
| FR-3  | Le système remonte l'état d'un objet connecté donné.            | À faire |

## Exigences non-fonctionnelles

| ID     | Exigence                                                       | Statut  |
|--------|----------------------------------------------------------------|---------|
| NFR-1  | L'API répond en moins de 200 ms pour une requête de lecture.   | À faire |
| NFR-2  | Aucun secret n'est versionné (gérés via .env, hors Git).       | OK      |

## Matrice de traçabilité

| Exigence | Test(s) associé(s) |
|----------|--------------------|
| FR-1     | _(à venir)_        |
| FR-2     | _(à venir)_        |
| FR-3     | _(à venir)_        |

