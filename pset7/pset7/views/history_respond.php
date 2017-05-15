<div class="container">
    <table class="table table-hover">
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
        
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= ($position["transaction"] == "BUY") ? $arrow = "<img alt=\"BUY\" src=\"/img/green_arrow_small.png\"/>" :  $arrow = "<img alt=\"SELL\" src=\"/img/red_arrow_small.png\"/>"; ?>
                    <?= $position["transaction"] ?></td>
                <td><?= $position["date_time"] ?></td>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td>$<?= number_format($position["price"], 2, '.', ',') ?></td>
            </tr>
        <?php endforeach ?>

    </table>

</div>
