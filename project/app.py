import os
import urllib.parse
import requests

#  export API_KEY=AIzaSyCowpheB4txaGzRhZjvPvobkl8HvZHVhIw

from flask import Flask, flash, redirect, render_template, request, session, request
from tempfile import mkdtemp

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # return render_template("apology.html",  error="TODO: RESULTS")

        """Look up quote for symbol."""
        origin = request.form.get("origin")
        destination = request.form.get("destination")
        distances = {}

        # Contact API
        try:

            api_key = os.environ.get("API_KEY")
            modes = {"driving", "walking", "bicycling", "bus", "rail"}
            for mode in modes:
                method = mode
                if mode == "bus" or mode == "rail":
                    method = "transit&transit_mode=" + mode
                url = f"https://maps.googleapis.com/maps/api/directions/json?origin={urllib.parse.quote_plus(origin)}&destination={urllib.parse.quote_plus(destination)}&mode={method}&units=metric&key={api_key}"

                response = requests.get(url)
                result = response.json()
                distances[mode] = result["routes"][0]["legs"][0]["distance"]
        except (KeyError, TypeError, ValueError, IndexError):
            return render_template("apology.html",  error="ERROR 404 No Route Found: DESTINATION AND/OR ORIGIN DON'T EXIST OR ARE TOO FAR AWAY")


        emissions = {
            "walking": "{:,}".format(round(distances["walking"]["value"]*0.020)),
            "bicycling": "{:,}".format(round(distances["bicycling"]["value"]*0.016)),
            "bus": "{:,}".format(round(distances["bus"]["value"]*0.105)),
            "rail": "{:,}".format(round(distances["rail"]["value"]*0.035)),
            "driving (medium gas car)": "{:,}".format(round(distances["driving"]["value"]*0.192)),
            "driving (medium EV)": "{:,}".format(round(distances["driving"]["value"]*0.053)),
        }
        distances["driving (medium gas car)"] = distances["driving"]
        distances["driving (medium EV)"] = distances["driving"]
        url = f"https://www.google.com/maps/dir/{urllib.parse.quote_plus(origin)}/{urllib.parse.quote_plus(destination)}/"
        return render_template("response.html",  emissions=emissions, distances=distances, url=url)


    else:
        return render_template("index.html")