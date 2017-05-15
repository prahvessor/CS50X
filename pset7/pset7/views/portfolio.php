<div class="container">
    <table class="table table-hover">
        <tr>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
        
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><b><?= $position["symbol"] ?></b></td>
                <td><?= $position["shares"] ?></td>
                <td>$<?= number_format($position["price"], 2, '.', ',') ?></td>
                <td>$<?= number_format($position["total"], 2, '.', ',') ?></td>
            </tr>
        <?php endforeach ?>

        <tr>
            <td colspan="3"><b>CASH:</b></td>
            <td>$<?=number_format($cash, 2, '.', ',');?></td>
        </tr>
    </table>

    <!--<iframe allowfullscreen frameborder="0" height="315" src="https://www.youtube.com/embed/oHg5SJYRHA0?autoplay=1&iv_load_policy=3&rel=0" width="420"></iframe>-->
</div>
