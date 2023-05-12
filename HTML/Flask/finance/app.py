import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

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


@app.route("/")
@login_required
def index():
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    db.execute("CREATE TABLE IF NOT EXISTS shares (share_id INT, symbol TEXT, quantity INT, userid INT);")
    db.execute("CREATE TABLE IF NOT EXISTS transactions (transaction_id INT, date date, time INT, userid INT);")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        results = lookup(symbol) # Lookup symbol using function which returns list of stock details

        # If no results then symbol wrong or empty - tell use to enter a valid symbol
        if results == None:
            return apology("Please enter a valid stock symbol")
        elif shares == None:
            return apology("Invalid shares quantity entered")
        else:
            # List Formatting : {'name': 'Forward Industries, Inc.', 'price': 1.02, 'symbol': 'FORD'}
            # Set page text to output symbol and how much per share (using USD function to make it a valid ticker - as per check50) converting price to string for display
            text = results["symbol"] + " are currently $" + str(usd(results["price"])) + " per share (" + results["name"] + ")"

            cash = db.execute("SELECT cash FROM users where id=",session["user_id"])
            totalprice = results["price"] * int(shares)

            if cash < totalprice:
                return apology("Not enough funds. Please purchase funds and try again.")
            else:
                date = datetime.now()
                # redirect to home
                return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        results = lookup(symbol) # Lookup symbol using function which returns list of stock details

        # If no results then symbol wrong or empty - tell use to enter a valid symbol
        if results == None:
            return apology("Please enter a valid stock symbol")
        else:
            # List Formatting : {'name': 'Forward Industries, Inc.', 'price': 1.02, 'symbol': 'FORD'}
            # Set page text to output symbol and how much per share (using USD function to make it a valid ticker - as per check50) converting price to string for display
            text = results["symbol"] + " are currently $" + str(usd(results["price"])) + " per share (" + results["name"] + ")"
            return render_template("quoted.html", results=text) # Load quoted page with text above as body text

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password1 = request.form.get("password")
        password2 = request.form.get("confirmation")

        # Needed to check if user exists in database
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username was submitted
        if not username:
            return apology("must enter username")

        # Ensure user does not exist in database - if results from database is not equal to 0 it means the username exists as results are returned
        elif not len(rows) == 0:
            return apology("Username taken")

        # Ensure password was submitted
        elif not password1:
            return apology("must enter a password")

        # Ensure password was submitted
        elif not password2:
            return apology("must verify password")

        # Check that the passwords match
        elif password1 != password2:
            return apology("Passwords do not match")

        else:
            hashpw = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
            # Query database for username
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashpw)
            rows = db.execute("SELECT * FROM users WHERE username = ?", username)
            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]

            # Source for looking up flashing messages: https://www.codingninjas.com/codestudio/library/message-flashing-in-flask#:~:text=Flask%20offers%20a%20function%20to,message%20to%20the%20next%20template.
            flash("User registered")

            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
