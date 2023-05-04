import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

MONTHS = ["January","February","March","April","May","June","July","August","September","October","November","December"]
DAYS = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/deleteitem", methods=["POST"])
def deleteitem():

    # Forget registrant
    id = request.form.get("id")
    db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Validate submission
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Remember registrant
        monthno = MONTHS.index(month)
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, monthno+1, day)

        return redirect("/")

    else:

        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html",birthdays=birthdays, months=MONTHS, days=DAYS)