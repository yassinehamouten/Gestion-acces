<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <?php if ($this->session->flashdata('succes')) { ?>
            <div class="alert alert-success" id="alert"> <?= $this->session->flashdata('succes') ?> </div>
        <?php } ?>
        <?php if ($this->session->flashdata('erreur')) { ?>
            <div class="alert alert-danger" id="alert"> <?= $this->session->flashdata('erreur') ?> </div>
        <?php } ?>
        <div class="row">
            <div class="col-xs-12">
                <div class="card">
                    <div class="card-header">
                        <div class="card-title">
                            <div class="title">Salles</div>
                        </div>
                        <div class="pull-right card-action">
                            <a href="<?php echo base_url("/administration/plageshoraires/add");?>"><input name="submit" type="submit" class="btn btn-primary pull-right" value="Ajouter une plage horaire"></a>
                        </div>
                    </div>
                    <div class="card-body">
                        <table class="datatable table table-striped" cellspacing="0" width="100%">
                            <thead>
                                <tr>
                                    <th>Id plage horaire</th>
                                    <th>Nom classe</th>
                                    <th>Nom salle</th>
                                    <th>Nom statut</th>
                                    <th>Heure début</th>
                                    <th>Heure fin</th>
                                    <th>Jour</th>
                                </tr>
                            </thead>
                            <tfoot>
                                <tr>
                                    <th>Id plage horaire</th>
                                    <th>Nom classe</th>
                                    <th>Nom salle</th>
                                    <th>Nom statut</th>
                                    <th>Heure début</th>
                                    <th>Heure fin</th>
                                    <th>Jour</th>
                                </tr>
                            </tfoot>
                            <tbody>
                                <?php
                                    $query = $this->db->query('SELECT * FROM plageshoraires, salles, classes, statuts WHERE classes.idClasse = plageshoraires.idClasse AND statuts.idStatut = plageshoraires.idStatut AND salles.idSalle = plageshoraires.idSalle');
                                    foreach ($query->result() as $row)
                                    {
                                        echo '<tr>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->idPlageHoraire.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->nomClasse.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->nomSalle.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->nomStatut.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->debut.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->fin.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/plageshoraires/edit/".$row->idPlageHoraire).'">'.$row->jour.'</a></td>';
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
</div>