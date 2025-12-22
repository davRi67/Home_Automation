from flask import Flask, jsonify

app = Flask(__name__)

@app.route("/temperature")
def temperature():
    return jsonify({"value": 22.5})

@app.route("/")
def index():
    return "Home Automation API — try /temperature", 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
