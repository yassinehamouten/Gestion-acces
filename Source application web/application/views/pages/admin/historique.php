<div class="container-fluid">
    <div class="side-body">
        <?php $this->breadcrumb->get() ?>
        <div class="row">
            <div class="col-xs-12">
                <div class="card">
                    <div class="card-header">
                        <div class="card-title">
                        <div class="title">Historique</div>
                        </div>
                    </div>
                    <div class="card-body">
                        <table class="datatable table table-striped" cellspacing="0" width="100%">
                            <thead>
                                <tr>
                                    <th>Id historique</th>
                                    <th>Code RFID</th>
                                    <th>Nom</th>
                                    <th>Prenom</th>
                                    <th>Date tentative</th>
                                    <th>Etat</th>
                                </tr>
                            </thead>
                            <tfoot>
                                <tr>
                                    <th>Id historique</th>
                                    <th>Code RFID</th>
                                    <th>Nom</th>
                                    <th>Prenom</th>
                                    <th>Date tentative</th>
                                    <th>Etat</th>
                                </tr>
                            </tfoot>
                            <tbody>
                                <?php
                                    $query = $this->db->query('SELECT * FROM historique, utilisateurs WHERE historique.codeRFID = utilisateurs.codeRFID');
                                    foreach ($query->result() as $row)
                                    {
                                        if($row->etat != 1){
                                            echo '<tr class="danger">';
                                        }else{
                                            echo '<tr>';
                                        }
                                        echo '<td>'.$row->idHistorique.'</td>';
                                        echo '<td>'.$row->codeRFID.'</td>';
                                        echo '<td>'.$row->nom.'</td>';
                                        echo '<td>'.$row->prenom.'</td>';
                                        echo '<td>'.$row->dateTentative.'</td>';
                                        if($row->etat == 1){
                                            echo '<td>Autorisé</td>';
                                        }else{
                                            echo '<td>Refusé</td>';
                                        }
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