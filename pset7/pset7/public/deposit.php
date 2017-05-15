<?php
    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("deposit_request.php", ["title" => "Deposit"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // check for positive integer number of shares
        if (preg_match("/^\d+$/", $_POST["money"]) != 1)
        {
            apologize("Wrong namber! Amount of shares must be positive integer");
        }
        
        // request user's cash 
        $balance = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $balance[0];
        // $old_cash["old_cash"] = $balance[0];
        
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["money"], $_SESSION["id"]);
        
        // render respond
        render("deposit_respond.php", ["title" => "Deposit", "cash" => $cash["cash"]]);
    }

?>