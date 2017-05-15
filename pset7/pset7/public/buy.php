<?php
    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        
        render("buy_request.php", ["title" => "Buy"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        
        if ($stock == false)
        {
            apologize("Sorry! You must provide a symbol.");
        }
        
        // check for positive integer number of shares
        if (preg_match("/^\d+$/", $_POST["shares"]) != 1)
        {
            apologize("Wrong namber! Amount of shares must be positive integer");
        }
        
        // check if current cash enough to buy 
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        if ($cash < $_POST["shares"])
        {
            apologize("You have not enough money!");
        }
        
        try {
            // First of all, let's begin a transaction
            CS50::query("START TRANSACTION");
        
            // A set of queries; if one fails, an exception should be thrown
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["shares"]*$stock["price"], $_SESSION["id"]);
            
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
            
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "BUY", strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
            
            // If we arrive here, it means that no exception was thrown
            // i.e. no query has failed, and we can commit the transaction
            CS50::query("COMMIT");
        } catch (Exception $e) {

            CS50::query("ROLLBACK");
        }
        
        redirect("/");
        // header('Location: '.$_SERVER['REQUEST_URI']);
    }

?>