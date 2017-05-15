<?php

    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("user_settings_form.php", ["title" => "User settings"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        
        if (empty($_POST["new_password"]))
        {
            apologize("You must provide your new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide your confirmation new password.");
        }
        else if ($_POST["new_password"] != $_POST["confirmation"])
        {
            apologize("New password and confirmation new password mismatch.");
        }
    
        CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["new_password"], PASSWORD_DEFAULT), $_SESSION["id"]);
       
        // render user settings
        render("user_settings_confirm.php", ["title" => "User settings"]);

        
    }
    
?>