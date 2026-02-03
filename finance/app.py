import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
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
    id = session.get("user_id")
    cash = db.execute("SELECT cash FROM users WHERE id = ?", id)[0]['cash']
    total_value = cash
    stocks = db.execute('''SELECT symbol,total_shares
                           FROM stocks
                           WHERE user_id = ?''', id)
    for stock in stocks:
        stock_state = lookup(stock['symbol'])
        stock['current_price'] = int(stock_state['price'])
        stock['total_stock_value'] = stock['current_price'] * stock['total_shares']
        total_value += stock['total_stock_value']
        stock['total_stock_value'] = usd(stock['total_stock_value'])
        stock['current_price'] = usd(stock['current_price'])
    return render_template("index.html", stocks = stocks, cash = usd(cash) , total_value = usd(total_value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #Check all the data
        id = session.get("user_id")
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("please type stock symbol")
        elif not shares:
            return apology("please type stock shares to buy")
        try:
            shares = int(shares)
            if shares <=0:
                return apology("please type shares as a positive integer")
        except:
            return apology("please type shares as a positive integer")

        #Quote and try to buy the stock
        quote_result = lookup(symbol)
        if quote_result is not None:
            cash = db.execute("SELECT cash FROM users WHERE id = ?", id)[0]['cash']
            total_price = quote_result['price'] * shares
            if cash > total_price:
                db.execute('''INSERT INTO stocks
                            (user_id,symbol,total_shares) VALUES(?, ?, ?)
                            ON CONFLICT(user_id,symbol) DO
                            UPDATE SET
                            total_shares = total_shares + ?
                            WHERE user_id = ?
                            AND symbol = ?''',
                            id, symbol, shares, shares, id, symbol)
                db.execute('''INSERT INTO transactions
                            (user_id,symbol,shares,price) VALUES(?, ?, ?, ?)''',
                            id, symbol, shares, quote_result['price'])
                db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                            total_price, id)
                return redirect("/")
            else:
                return apology("U R SO POOR")
        else:
            return apology("Company not found")
    else:
        return render_template("buy.html")
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session.get("user_id")
    stock_history = db.execute('''SELECT symbol,shares,price,timestamp
                                FROM transactions
                                WHERE user_id = ?''', id)
    for stock in stock_history:
        stock['price'] = usd(stock['price'])
    return render_template("history.html", stock_history = stock_history)

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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            if not symbol:
                return apology("please type stock symbol")
            quote_result = lookup(symbol)
            quote_result['price'] = usd(quote_result['price'])
            return render_template("quote.html", quote_result = quote_result)
        except:
            return apology("quote fails")
    else:
        return render_template("quote.html", quote_result = {})


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        try:
                # Ensure username was submitted
            if not request.form.get("username"):
                return apology("must provide username", 400)

            # Ensure password was submitted
            elif not request.form.get("password"):
                return apology("must provide password", 400)

            # Ensure confirmation was submitted
            elif not request.form.get("confirmation"):
                return apology("must provide confirmation", 400)
            #Check the password and confirmation and write it into database
            if request.form.get("password") == request.form.get("confirmation"):
                db.execute("INSERT INTO users (username,hash) VALUES(?,?)",
                        request.form.get("username"), generate_password_hash(request.form.get("password")))
            else:
                return apology("Confirmation do not match")
            return redirect("/login")
        except:
            return apology("register fails")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session.get("user_id")
    if request.method == "POST":
        #Check all the data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("please type stock symbol")
        elif not shares:
            return apology("please type stock shares to buy")
        try:
            shares = int(shares)
            if shares <=0:
                return apology("please type shares as a positive integer")
        except:
            return apology("please type shares as a positive integer")
        #Check if user can sell the stocks
        user_stock = db.execute('''SELECT * FROM stocks
                                WHERE user_id = ?
                                AND symbol = ?
                                AND total_shares >= ?''', id, symbol, shares)
        if user_stock:
            quote_result = lookup(symbol)
            total_price = quote_result['price'] * shares
            db.execute('''UPDATE stocks SET
                      total_shares = total_shares - ?
                      WHERE user_id = ?
                      AND symbol = ?''',
                      shares, id, symbol)
            db.execute('''INSERT INTO transactions
                      (user_id,symbol,shares,price) VALUES(?, ?, ?, ?)''',
                      id, symbol, -shares, quote_result['price'])
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                    total_price, id)
            return redirect("/")
        else:
            return apology("Can't Sell the Stocks")

    else:
        stocks = db.execute('''SELECT * FROM stocks
                                WHERE user_id = ?''', id)
        return render_template("sell.html", stocks = stocks)
