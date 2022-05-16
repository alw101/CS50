import os

#  export API_KEY=

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

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
    """Show portfolio of stocks"""
    symbols = db.execute(
        "SELECT DISTINCT symbol FROM transactions GROUP BY symbol HAVING user_id = ? AND SUM(amount) > 0", session["user_id"])
    holdings = []
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
    total = cash
    change = 0
    for i in range(len(symbols)):
        symbol = symbols[i]['symbol']
        row = {
            "symbol": symbol,
            "name": lookup(symbol)['name'],
            "amount": db.execute("SELECT SUM(amount) FROM transactions WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])[0]["SUM(amount)"],
            "price": lookup(symbol)['price'],
        }
        row["change"] = row["price"]*row["amount"] - db.execute(
            "SELECT SUM(total) FROM transactions GROUP BY symbol HAVING symbol = ? AND user_id = ? ", symbol, session["user_id"])[0]["SUM(total)"]
        total += (row["price"]*row["amount"])
        change += (row["change"])
        holdings.append(row)
    return render_template("index.html", holdings=holdings, cash=cash, total=total, change=change)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        try:
            shares = float(request.form.get("shares"))
        except ValueError:
            return apology("INVALID AMMOUNT")
        if quote == None:
            return apology("INVALID SYMBOL")
        if shares % 1 != 0 or shares <= 0:
            return apology("INVALID AMMOUNT")
        row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        if row[0]["cash"] - quote["price"]*shares < 0:
            return apology("INSUFFICENT FUNDS")
        amount = db.execute("SELECT SUM(amount) FROM transactions WHERE user_id = ? AND symbol = ?",
                            session["user_id"], quote["symbol"])[0]["SUM(amount)"]
        if amount == None:
            amount = 0
        db.execute("INSERT INTO transactions (user_id, symbol, amount, price, owned, total) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], quote["symbol"], shares, quote["price"], amount+shares, quote["price"]*shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", row[0]["cash"]-quote["price"]*shares, session["user_id"])
        flash("Transaction Completed: Bought " + str(shares) + " shares of " +
              quote["symbol"] + " at $" + str(quote["price"]) + " each")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions)


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
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("INVALID SYMBOL")
        return render_template("quoted.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match")

        elif len(request.form.get("password")) < 8:
            return apology("YOU IDIOT! Use a longer password!")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 0:
            return apology("username already exists")

        # Save new username and password
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   request.form.get("username"), generate_password_hash(request.form.get("password")))

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        if quote == None:
            return apology("INVALID SYMBOL")
        if shares % 1 != 0 or shares <= 0:
            return apology("INVALID AMMOUNT")
        row = db.execute("SELECT sum(amount) FROM transactions WHERE user_id = ?", session["user_id"])
        if row[0]["sum(amount)"] < shares:
            return apology("INSUFFICENT SHARES")
        row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        amount = db.execute("SELECT SUM(amount) FROM transactions WHERE user_id = ? AND symbol = ?",
                            session["user_id"], quote["symbol"])[0]["SUM(amount)"]
        if amount == None:
            amount = 0

        db.execute("INSERT INTO transactions (user_id, symbol, amount, price, owned, total) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], quote["symbol"], -shares, -quote["price"], amount-shares, -quote["price"]*shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", row[0]["cash"]+quote["price"]*shares, session["user_id"])
        flash("Transaction Completed: Sold " + str(shares) + " shares of " +
              quote["symbol"] + " at $" + str(quote["price"]) + " each")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)
