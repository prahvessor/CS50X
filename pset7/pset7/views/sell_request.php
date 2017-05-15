<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select name="symbol" class="form-control" id="sel1">
                <option disabled selected value="">Symbol</option>
                
                <?php foreach ($symbols as $symbol): ?>
                    <option value="<?= $symbol["symbol"]?>"><?= $symbol["symbol"] ?></option>
                    
                <?php endforeach ?>

            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-warning" type="submit">
                <span aria-hidden="true" ></span>
                Sell
            </button>
        </div>
    </fieldset>
</form>

