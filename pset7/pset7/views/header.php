<!DOCTYPE html>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <!-- https://jquery.com/ -->
        <script src="/js/jquery-1.11.3.min.js"></script>

        <!-- http://getbootstrap.com/ -->
        <script src="/js/bootstrap.min.js"></script>

        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <div>
                    <a href="/"><img alt="C$50 Finance" src="/img/logo.png"/></a>
                    <br><br>
                </div>
                <?php if (!empty($_SESSION["id"])): ?>
                    
                    <nav class="navbar navbar-inverse">
                        <div class="container-fluid">
                            <div class="navbar-header">
                                <a class="navbar-brand" href="/">C$50 Finance</a>
                            </div>
                            <ul class="nav navbar-nav">
                                <li><a href="quote.php">Quote</a></li>
                                <li><a href="buy.php">Buy</a></li>
                                <li><a href="sell.php">Sell</a></li>
                                <li><a href="history.php">History</a></li>
                                <li><a href="deposit.php">Deposit</a></li>
                            </ul>
                            <ul class="nav navbar-nav navbar-right">
                                <li><a href="settings.php"><span class="glyphicon glyphicon-user"></span> User settings</a></li>
                                <li><a href="logout.php"><span class="glyphicon glyphicon-log-out"></span> Log Out</a></li>
                            </ul>
                        </div>
                    </nav>
                    
                    <!--<ul class="nav nav-pills">-->
                    <!--    <li><a href="quote.php">Quote</a></li>-->
                    <!--    <li><a href="buy.php">Buy</a></li>-->
                    <!--    <li><a href="sell.php">Sell</a></li>-->
                    <!--    <li><a href="history.php">History</a></li>-->
                    <!--    <li><a href="deposit.php">Deposit</a></li>-->
                    <!--    <li><a href="settings.php">User settings</a></li>-->
                    <!--    <li><a href="logout.php"><strong>Log Out</strong></a></li>-->
                    <!--</ul>-->
                <?php endif ?>
            </div>

            <div id="middle">
