<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <div class="page-title">
            <span class="title">Modifier votre mot de passe</span>
            <div class="description"></div>
        </div>
        <div class="row">
            <div class="col-xs-12">
                <?php echo validation_errors(); ?>
                <?php echo form_open(); ?>
                    <div class="row">
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="password">Mot de passe</label>
                                <input type="text" class="form-control" id="password" name="password" placeholder="Mot de passe" value="<?php echo $user[0]->motPasse ?>">
                            </div>
                        </div>
                    </div>

                    <div class="login-button text-center">
                        <input name="submit" type="submit" class="btn btn-primary" value="Enregistrer">
                    </div>
                <?php echo form_close(); ?>
            </div>
        </div>
    </div>
</div>