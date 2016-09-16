<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <?php if ($this->session->flashdata('erreur')) { ?>
            <div class="alert alert-danger" id="alert"> <?= $this->session->flashdata('erreur') ?> </div>
        <?php } ?>
        <div class="page-title">
            <span class="title">Edition de l'utilisateur <?php echo $user[0]->prenom.' '.$user[0]->nom ?></span>
            <div class="description">Modifier les diférentes informations de l'utilisateur.</div>
        </div>
        <div class="row">
            <div class="col-xs-12">
                <?php echo validation_errors(); ?>
                <?php echo form_open(); ?>
                    <div class="row">
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="nom">Nom</label>
                                <input type="text" class="form-control" id="nom" name="nom" placeholder="Nom" value="<?php echo $user[0]->nom ?>">
                            </div>
                        </div>
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="prenom">Prenom</label>
                                <input type="text" class="form-control" id="prenom" name="prenom" placeholder="Prenom" value="<?php echo $user[0]->prenom ?>">
                            </div>
                        </div>
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="idClasse">Classe</label><br>
                                <select name="idClasse">
                                    <optgroup label="Classes">
                                        <?php 
                                            $query = $this->db->query('SELECT * FROM classes');
                                            foreach ($query->result() as $row){
                                                if($row->idClasse == $user[0]->idClasse){
                                                    echo '<option value="'.$row->idClasse.'" selected>'.$row->nomClasse.'</option>';
                                                }else{
                                                    echo '<option value="'.$row->idClasse.'">'.$row->nomClasse.'</option>';
                                                }
                                            }
                                        ?>
                                    </optgroup>
                                </select>
                            </div>
                        </div>                        
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="idClasse">Statut</label><br>
                                <select name="idStatut">
                                    <optgroup label="Statuts">
                                        <?php 
                                            $query = $this->db->query('SELECT * FROM statuts');
                                            foreach ($query->result() as $row){
                                                if($row->idStatut == $user[0]->idStatut){
                                                    echo '<option value="'.$row->idStatut.'" selected>'.$row->nomStatut.'</option>';
                                                }else{
                                                    echo '<option value="'.$row->idStatut.'">'.$row->nomStatut.'</option>';
                                                }
                                            }
                                        ?>

                                    </optgroup>
                                </select>
                            </div>
                        </div>
                        <div class="clearfix"></div>  
                        <div class="col-sm-6">
                            <div class="form-group">
                                <label for="codeRFID">Code RFID</label>
                                <input type="text" class="form-control" id="codeRFID" name="codeRFID" placeholder="Code RFID" value="<?php echo $user[0]->codeRFID ?>">
                            </div>
                        </div>
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="login">Login</label>
                                <input type="text" class="form-control" id="login" name="login" placeholder="Login" value="<?php echo $user[0]->login ?>">
                            </div>
                        </div>
                        
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="password">Mot de passe</label>
                                <input type="password" class="form-control" id="password" name="password" placeholder="Mot de passe">
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