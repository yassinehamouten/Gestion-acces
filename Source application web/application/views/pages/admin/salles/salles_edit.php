<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <div class="page-title">
            <span class="title">Ajouter une salle</span>
            <div class="description">Ajouter une salle en base de données.</div>
        </div>
        <div class="row">
            <div class="col-xs-12">
                <?php echo validation_errors(); ?>
                <?php echo form_open(); ?>
                    <div class="row">
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="nom">Nom de la salle</label>
                                <input type="text" class="form-control" id="nom" name="nom" placeholder="Nom de la salle" value="<?php echo $salle[0]->nomSalle ?>">
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