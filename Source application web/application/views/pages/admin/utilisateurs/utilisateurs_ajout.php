<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <div class="page-title">
            <span class="title">Ajouter un utilisateur</span>
            <div class="description">Ajouter un utilisateur en base de données.</div>
        </div>
        <div class="row">
            <div class="col-xs-12">
                <?php echo validation_errors(); ?>
                <?php echo form_open(); ?>
                    <div class="row">
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="nom">Nom</label>
                                <input type="text" class="form-control" id="nom" name="nom" placeholder="Nom" value="<?php if(isset($utilisateur))echo $utilisateur["nom"];?>">
                            </div>
                        </div>
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="prenom">Prenom</label>
                                <input type="text" class="form-control" id="prenom" name="prenom" placeholder="Prenom" value="<?php if(isset($utilisateur))echo $utilisateur["prenom"];?>">
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
                                                echo '<option value="'.$row->idClasse.'">'.$row->nomClasse.'</option>';
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
                                                echo '<option value="'.$row->idStatut.'">'.$row->nomStatut.'</option>';
                                            }
                                        ?>

                                    </optgroup>
                                </select>
                            </div>
                        </div>
                        <div class="clearfix"></div>  
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="codeRFID">Code RFID</label>
                                <input type="text" class="form-control" id="codeRFID" name="codeRFID" placeholder="Code RFID" value="<?php if(isset($utilisateur))echo $utilisateur["RFID"];?>">
                            </div>
                        </div>
                        <div class="col-sm-4">
                            <div class="form-group">
                                <label for="login">Login (Uniquement pour administrateur!)</label>
                                <input type="text" class="form-control" id="login" name="login" placeholder="Login" value="<?php if(isset($utilisateur))echo $utilisateur["login"];?>">
                            </div>
                        </div>
                        <div class="col-sm-5">
                            <div class="form-group">
                                <label for="password">Mot de passe (Uniquement pour administrateur!)</label>
                                <input type="password" class="form-control" id="password" name="password" placeholder="Mot de passe" value="<?php if(isset($utilisateur))echo $utilisateur["password"];?>">
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