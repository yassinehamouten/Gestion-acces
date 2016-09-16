<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <div class="page-title">
            <span class="title">Modifier une plage horaire</span>
            <div class="description">Modifier une plage horaire en base de données.</div>
        </div>
        <div class="row">
            <div class="col-xs-12">
                <?php echo validation_errors(); ?>
                <?php echo form_open(); ?>
                    <div class="row">
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="idSalle">Salle</label><br>
                                <select name="idSalle">
                                    <optgroup label="Salles">
                                        <?php 
                                            $query = $this->db->query('SELECT * FROM salles');
                                            foreach ($query->result() as $row){
                                                echo '<option value="'.$row->idSalle.'">'.$row->nomSalle.'</option>';
                                                
                                            }
                                        ?>
                                    </optgroup>
                                </select>
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
                                <label for="idStatut">Statut</label><br>
                                <select name="idStatut">
                                    <optgroup label="Statuts">
                                        <?php 
                                            $query = $this->db->query('SELECT * FROM statuts');
                                            foreach ($query->result() as $row){
                                                if($row->idStatut == 3){
                                                    echo '<option value="'.$row->idStatut.'" selected>'.$row->nomStatut.'</option>';
                                                }  else {
                                                    echo '<option value="'.$row->idStatut.'">'.$row->nomStatut.'</option>';
                                                }
                                            }
                                        ?>
                                    </optgroup>
                                </select>
                            </div>
                        </div>
                        <div class="col-sm-3">
                            <div class="form-group">
                                <label for="jour">Jour</label><br>
                                <select name="jour">
                                    <optgroup label="Jours">
                                        <?php 
                                            $jours = array('lundi','mardi','mercredi','jeudi','vendredi','samedi','dimanche');
                                            foreach ($jours as $row){
                                                echo '<option value="'.$row.'">'.$row.'</option>';
                                            }
                                        ?>
                                    </optgroup>
                                </select>
                            </div>
                        </div>
                        <div class="col-sm-12">
                            <div class="form-group">
                                <label>Plage horaire</label>
                                <div class="slider"></div>
                            </div>
                        </div>
                        
                        <div class="col-sm-12">
                            <input type="hidden" class="form-control" id="debut" name="debut" value="8">
                        </div>
                        <div class="col-sm-12">
                            <input type="hidden" class="form-control" id="fin" name="fin" value="17">
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