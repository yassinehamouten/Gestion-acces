<div class="container">
        <div class="login-box">
            <?php if ($this->session->flashdata('succes')) { ?>
                <div class="alert alert-success" id="alert"> <?= $this->session->flashdata('succes') ?> </div>
            <?php } ?>
            <?php if ($this->session->flashdata('erreur')) { ?>
                <div class="alert alert-danger" id="alert"> <?= $this->session->flashdata('erreur') ?> </div>
            <?php } ?>
            <div>
                <div class="login-form row">
                    <div class="col-sm-12 text-center login-header">
                        <i class="login-logo fa fa-connectdevelop fa-5x"></i>
                        <h4 class="login-title">Administration Gestion Accès</h4>
                    </div>
                    <div class="col-sm-12">
                        <div class="login-body">
                            <div class="progress hidden" id="login-progress">
                                <div class="progress-bar progress-bar-success progress-bar-striped active" role="progressbar" aria-valuenow="100" aria-valuemin="0" aria-valuemax="100" style="width: 100%">
                                    Log In...
                                </div>
                            </div>
                            <?php echo validation_errors(); ?>
                            <?php echo form_open(); ?>
                                <div class="control">
                                    <input name="username" type="text" class="form-control" value="admin" />
                                </div>
                                <div class="control">
                                    <input name="password" type="password" class="form-control" value="admin" />
                                </div>
                                <div class="login-button text-center">
                                    <input name="submit" type="submit" class="btn btn-primary" value="Se connecter">
                                </div>
                            <?php echo form_close(); ?>
                        </div>
                        <div class="login-footer">
                            <span class="text-right">Gestion accès</span>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>