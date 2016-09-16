<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <?php if ($this->session->flashdata('succes')) { ?>
            <div class="alert alert-success" id="alert"> <?= $this->session->flashdata('succes') ?> </div>
        <?php } ?>
        <?php if ($this->session->flashdata('erreur')) { ?>
            <div class="alert alert-danger" id="alert"> <?= $this->session->flashdata('erreur') ?> </div>
        <?php } ?>
        <div class="page-title">
            <span class="title">Liste des différents utilisateurs</span>
            <div class="description">Liste des différents utilisateurs enregisistrés en base de données.</div>
        </div>
        <div class="row">
            <div class="col-xs-12">
                <div class="card">
                    <div class="card-header">
                        <div class="card-title">
                            <div class="title">Utilisateurs</div>
                        </div>
                        <div class="pull-right card-action">
                            <div class="btn-group" role="group" aria-label="...">
                                <button type="button" class="btn btn-link" data-toggle="modal" data-target="#modalInfo" title="Aide pour importation">?</button>
                            </div>
                            <?php echo form_open("",array("class" => 'form-inline', "style" => "display:inline-block", "enctype" => "multipart/form-data")); ?>
                            
                                <label for="fichier">Fichier CSV</label>
                            <div class="form-group">
                                <input type="file" id="fichier" name="fichier">
                            </div>
                            <div class="form-group">
                                <input name="submit" type="submit" class="btn btn-info" value="Importer la liste">
                            </div>
                            <?php echo form_close(); ?>
                            <a href="<?php echo base_url("/administration/utilisateurs/add");?>"><input name="submit" type="submit" class="btn btn-primary" value="Ajouter un utilisateur"></a>
                        </div>
                    </div>
                    <div class="card-body">
                        <table class="datatable table table-striped" cellspacing="0" width="100%">
                            <thead>
                                <tr>
                                    <th>Id utilisateur</th>
                                    <th>Nom</th>
                                    <th>Prénom</th>
                                    <th>Id classe</th>
                                    <th>Code RFID</th>
                                    <th>Login</th>
                                    <th>Id statut</th>
                                </tr>
                            </thead>
                            <tfoot>
                                <tr>
                                    <th>Id utilisateur</th>
                                    <th>Nom</th>
                                    <th>Prénom</th>
                                    <th>Id classe</th>
                                    <th>Code RFID</th>
                                    <th>Login</th>
                                    <th>Id statut</th>
                                </tr>
                            </tfoot>
                            <tbody>
                                <?php
                                    $query = $this->db->query('SELECT * FROM utilisateurs, classes, statuts WHERE classes.idClasse = utilisateurs.idClasse AND statuts.idStatut = utilisateurs.idStatut');
                                    foreach ($query->result() as $row){
                                        echo '<tr>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->idUtilisateur.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->nom.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->prenom.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->nomClasse.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->codeRFID.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->login.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/utilisateurs/edit/".$row->idUtilisateur).'">'.$row->nomStatut.'</a></td>';
                                        echo '</tr>';
                                    }
                                ?>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
    
    <div class="modal fade modal-primary in" id="modalInfo" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <div class="modal-dialog modal-lg">
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                    <h4 class="modal-title" id="myModalLabel">Comment importer des utilisateurs?</h4>
                </div>
                <div class="modal-body">
                    Le fichier csv doit être formaté comme ceci :<br><br>
                    <blockquote>
                        <p>
                            nom, prenom, idClasse, codeRFID, login, password, idStatut<br>
                            nom, prenom, idClasse, codeRFID, login, password, idStatut<br>
                        </p>
                    </blockquote>
                    <br>
                    exemple :<br><br>
                    <blockquote>
                        <p>Kors, Michael, 1, 123456789568, '', '', 3</p>
                    </blockquote>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-primary" data-dismiss="modal">OK</button>
                </div>
            </div>
        </div>
    </div>
</div>