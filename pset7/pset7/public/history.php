<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $positions = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
        
        // render history
        render("history_respond.php", ["positions" => $positions, "title" => "History"]);
    }

?>
