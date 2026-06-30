from fastapi.testclient import TestClient
from homeserver.main import app

client = TestClient(app)


def test_health():
    response = client.get("/health")
    # assertion 1 : le status_code doit valoir 200
    # assertion 2 : le json() doit valoir {"status": "healthy"}
    assert response.status_code == 200
    assert response.json() == {"status": "healthy"}