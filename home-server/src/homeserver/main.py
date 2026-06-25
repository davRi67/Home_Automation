from fastapi import FastAPI

app = FastAPI(title="Home Automation Hub")


@app.get("/")
def read_root():
    return {"status": "ok", "service": "home-automation-hub"}


@app.get("/health")
def health_check():
    return {"status": "healthy"}