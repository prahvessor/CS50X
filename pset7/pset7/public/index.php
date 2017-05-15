<?php

    // configuration
    require("../includes/config.php"); 
    
    $balance = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $balance[0];
    
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    $total; // total cost
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => $row["shares"] * $stock["price"]
            ];
        }
    }
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash["cash"]]);

?>
