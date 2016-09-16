<div class="side-body padding-top">
    <div class="row">
        <?php if ($this->session->flashdata('succes')) { ?>
            <div class="alert alert-success" id="alert"> <?= $this->session->flashdata('succes') ?> </div>
        <?php } ?>
        <?php if ($this->session->flashdata('erreur')) { ?>
            <div class="alert alert-danger" id="alert"> <?= $this->session->flashdata('erreur') ?> </div>
        <?php } ?>
            
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">    
            <div class="card" style="background-color: #ffb8aa; border-color: #fb927d; color: #7c1a06;">
                <div class="card-body">
                    Les fonctionnalités de l'application ( Insertion et modification de données ) ont été bloquées sur cette version.<br/>
                    <a href="https://github.com/yassinehamouten/Gestion-acces">Code source</a>
                    <div class="clear-both"></div>
                </div>
            </div>
        </div>
        <div class="col-lg-4 col-md-6 col-sm-6 col-xs-12">
            <a href="<?php echo base_url("/administration/utilisateurs")?>">
                <div class="card red summary-inline">
                    <div class="card-body">
                        <i class="icon fa fa-user fa-4x"></i>
                        <div class="content">
                            <div class="title"><?php echo $nbUsers ?></div>
                            <div class="sub-title">Nombre d'utilisateurs</div>
                        </div>
                        <div class="clear-both"></div>
                    </div>
                </div>
            </a>
        </div>
        <div class="col-lg-4 col-md-6 col-sm-6 col-xs-12">
            <a href="<?php echo base_url("/administration/historique")?>">
                <div class="card yellow summary-inline">
                    <div class="card-body">
                        <i class="icon fa fa-list fa-4x"></i>
                        <div class="content">
                            <div class="title"><?php echo $nbHistorique ?></div>
                            <div class="sub-title">Nombre de tentatives d'accès aujourd'hui</div>
                        </div>
                        <div class="clear-both"></div>
                    </div>
                </div>
            </a>
        </div>
        <div class="col-lg-4 col-md-6 col-sm-6 col-xs-12">
            <a href="<?php echo base_url("/administration/salles")?>">
                <div class="card green summary-inline">
                    <div class="card-body">
                        <i class="icon fa fa-building fa-4x"></i>
                        <div class="content">
                            <div class="title"><?php echo $nbSalles ?></div>
                            <div class="sub-title">Salles gérer par le système</div>
                        </div>
                        <div class="clear-both"></div>
                    </div>
                </div>
            </a>
        </div>
    </div>
    <div class="row">
        <!--
        <div class="col-sm-6 col-xs-12">
            <div class="card">
                <div class="card-header">
                    <div class="card-title">
                        <div class="title">Tentatives d'accès</div>
                    </div>
                </div>
                <div class="card-body no-padding">
                    <canvas id="tentativesAcces" class="chart"></canvas>
                </div>
            </div>
        </div>
        <-->
        <div class="col-sm-6 col-xs-12">
            <div class="card">
                <div class="card-header">
                    <div class="card-title">
                        <div class="title">Répartition des étudiants</div>
                    </div>
                </div>
                <div class="card-body no-padding">
                    <canvas id="pie-chart" class="chart"></canvas>
                </div>
            </div>
        </div>
    </div>
</div>