<?php
    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        $symbols = [];
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $symbols[] = [
                    "symbol" => $row["symbol"]
                ];
            }
        }
        
        render("sell_request.php", ["title" => "Sell", "symbols" => $symbols]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $row = $rows[0];
        $stock = lookup($_POST["symbol"]);
        
        try {
            // First of all, let's begin a transaction
            CS50::query("START TRANSACTION");
        
            // A set of queries; if one fails, an exception should be thrown
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $row["shares"]*$stock["price"], $_SESSION["id"]);
            
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "SELL", $_POST["symbol"], $row["shares"], $stock["price"]);
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