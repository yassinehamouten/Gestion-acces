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
                            <a href="<?php echo base_url("/administration/salles/add");?>"><input name="submit" type="submit" class="btn btn-primary pull-right" value="Ajouter une salle"></a>
                        </div>
                    </div>
                    <div class="card-body">
                        <table class="datatable table table-striped" cellspacing="0" width="100%">
                            <thead>
                                <tr>
                                    <th>Id salle</th>
                                    <th>Nom salle</th>
                                </tr>
                            </thead>
                            <tfoot>
                                <tr>
                                    <th>Id salle</th>
                                    <th>Nom salle</th>
                                </tr>
                            </tfoot>
                            <tbody>
                                <?php
                                    $query = $this->db->query('SELECT * FROM salles');
                                    foreach ($query->result() as $row)
                                    {
                                        echo '<tr>';
                                        echo '<td><a href="'.base_url("/administration/salles/edit/".$row->idSalle).'">'.$row->idSalle.'</a></td>';
                                        echo '<td><a href="'.base_url("/administration/salles/edit/".$row->idSalle).'">'.$row->nomSalle.'</a></td>';
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