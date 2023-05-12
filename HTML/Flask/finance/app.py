import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime, date # Source: https://www.w3schools.com/python/python_datetime.asp and https://docs.python.org/3/library/datetime.html

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


def getShares():
    shares = db.execute("SELECT * FROM shares where userid=?;", session["user_id"])
    print(shares)

    sharesdict = []

    for i in range(0,len(shares)):
        shareid = shares[i]["shareID"]
        symbol = shares[i]["symbol"]
        quantity = int(shares[i]["quantity"])
        results = lookup(symbol) # Lookup symbol using function which returns list of stock details
        price = results["price"] # Lookup symbol using function which returns list of stock details

        totalprice = float(price) * quantity

        # Creating a new dictionary to pass thbrough as shares, source: https://www.geeksforgeeks.org/appending-to-list-in-python-dictionary/
        # Adding new key pairs source: https://thispointer.com/add-key-value-pairs-to-an-empty-dictionary-in-python/
        sharesdict.append({'shareid': shareid, 'symbol':symbol, 'quantity':quantity, 'price':usd(price), 'totalprice':usd(totalprice)})
    ## print(shares) # for testing only
    ## print(sharesdict) # for testing only

    return sharesdict

@app.route("/")
@login_required
def index():
    return render_template("index.html",shares=getShares())


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Sources for SQL: https://www.w3schools.com/sql/sql_foreignkey.asp
    # If tables don't exist, then create them for this function
    db.execute("CREATE TABLE IF NOT EXISTS transactions (transactionID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL, price REAL NOT NULL, quantity INTEGER NOT NULL, total REAL NOT NULL, userid int NOT NULL, FOREIGN KEY (userID) REFERENCES users(id));")
    db.execute("CREATE TABLE IF NOT EXISTS shares (shareID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT NOT NULL, quantity INTEGER NOT NULL, userid int NOT NULL, FOREIGN KEY (userID) REFERENCES users(id));")

    # If method is POST
    if request.method == "POST":
        # Get Symbol and Shares
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Invalid shares quantity entered")
        results = lookup(symbol) # Lookup symbol using function which returns list of stock details

        # If no results then symbol wrong or empty - tell user to enter a valid symbol
        if results == None:
            return apology("Please enter a valid stock symbol")
        # if shares is empty or less than 1 - tell user an invalided quantity was entered.
        elif shares == None or shares < 1:
            return apology("Invalid shares quantity entered")
        else:
            # Look up how much cash the current user has in the table
            cash = db.execute("SELECT cash FROM users where id=?",session["user_id"])

            # List Formatting for reference: {'name': 'Forward Industries, Inc.', 'price': 1.02, 'symbol': 'FORD'}
            price = float(results["price"]) # get the price of the searched stock
            #print(cash[0]["cash"])#for testing only
            totalprice = price * int(shares) # calculate the total price
            print(totalprice)

            # If user case is less than the total price then tell the user they do not add funds
            if cash[0]["cash"] < totalprice:
                return apology("Not enough funds. Please add funds and try again.")
            else:
                # SQLite datetime formatting source: https://www.tutorialspoint.com/sqlite/sqlite_date_time.htm
                # get todays date and time in d/m/y and h:m:s format
                tod = date.today().strftime("%d/%m/%y")
                tim = datetime.now().strftime("%H:%M:%S")
                # Add the transaction log to the database table, transactions
                db.execute("INSERT INTO transactions (date, time, price, quantity, total, userid) VALUES (?,?,?,?,?, ?);", tod, tim, price, shares, totalprice, session["user_id"])
                # Update users cash to reflect new amount - Source for help: https://www.w3schools.com/sql/sql_update.asp
                db.execute("UPDATE users SET cash=? where id=?", cash[0]["cash"] - totalprice, session["user_id"])

                currentshares = db.execute("SELECT quantity FROM shares where symbol=? and userid=?", symbol, session["user_id"])
                # print(currentshares) # For testing purposes only
                if len(currentshares) == 0:
                    # Add the shares to the shares table and assign the user ID and link to the transaction ID using the foreign keys s
                    share = db.execute("INSERT INTO shares (symbol, quantity, userid) VALUES (?,?,?);", symbol, shares, session["user_id"])
                else:
                    db.execute("UPDATE shares Set quantity=? where symbol=? and userid=?", int(currentshares[0]["quantity"]) + int(shares), symbol, session["user_id"])

                # Flash message
                flash("Purchased")
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
            text = results["symbol"] + " are currently " + str(usd(results["price"])) + " per share (" + results["name"] + ")"
            return render_template("quoted.html", results=text) # Load quoted page with text above as body text

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # If table doesn't exist, then create them for this function
    db.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);")
    db.execute("CREATE UNIQUE INDEX IF NOT EXISTS username ON users (username);")
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
    if request.method == "POST":
        print("")
    else:
        return render_template("sell.html",shares=getShares())
