<nav class="navbar navbar-default navbar-fixed-top navbar-top">
    <div class="container-fluid">
        <div class="navbar-header">
            <button type="button" class="navbar-expand-toggle">
                <i class="fa fa-bars icon"></i>
            </button>
            <ol class="breadcrumb navbar-breadcrumb">
                <li class="active">Administration</li>
            </ol>
            <button type="button" class="navbar-right-expand-toggle pull-right visible-xs">
                <i class="fa fa-th icon"></i>
            </button>
        </div>
        <ul class="nav navbar-nav navbar-right">
            <button type="button" class="navbar-right-expand-toggle pull-right visible-xs">
                <i class="fa fa-times icon"></i>
            </button>
            <li class="dropdown profile">
                <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="true"><?= $this->auth->getUser();?> <span class="caret"></span></a>
                <ul class="dropdown-menu animated fadeInDown">
                    <li>
                        <div class="profile-info">
                            <h4 class="username"><?= $this->auth->getUser();?></h4>
                            <div class="btn-group margin-bottom-2x" role="group">
                                <a href="<?php echo base_url("/administration/profile")?>"><button type="button" class="btn btn-default"><i class="fa fa-user"></i> Profile</button></a>
                                <a href="<?php echo base_url("/administration/logout")?>"><button type="button" class="btn btn-default"><i class="fa fa-sign-out"></i> Logout</button></a>
                            </div>
                        </div>
                    </li>
                </ul>
            </li>
        </ul>
    </div>
</nav>
<div class="side-menu sidebar-inverse">
    <nav class="navbar navbar-default" role="navigation">
        <div class="side-menu-container">
            <div class="navbar-header">
                <a class="navbar-brand" href="<?php echo base_url("/administration")?>">
                    <div class="icon fa fa-paper-plane"></div>
                    <div class="title">Administration</div>
                </a>
                <button type="button" class="navbar-expand-toggle pull-right visible-xs">
                    <i class="fa fa-times icon"></i>
                </button>
            </div>
            <ul class="nav navbar-nav">
                <li <?php if(uri_string() == "administration"){echo 'class="active"';} ?>>
                    <a href="<?php echo base_url("/administration")?>">
                        <span class="icon fa fa-tachometer"></span><span class="title">Dashboard</span>
                    </a>
                </li>
                <li <?php if(strstr(uri_string(),"/utilisateurs")){echo 'class="active"';} ?>>
                    <a href="<?php echo base_url("/administration/utilisateurs")?>">
                        <span class="icon fa fa-user"></span><span class="title">Utilisateurs</span>
                    </a>
                </li>
                <li <?php if(strstr(uri_string(),"/classes")){echo 'class="active"';} ?>>
                    <a href="<?php echo base_url("/administration/classes")?>">
                        <span class="icon fa fa-calendar"></span><span class="title">Classes</span>
                    </a>
                </li>
                <li <?php if(strstr(uri_string(),"/salles")){echo 'class="active"';} ?>>
                    <a href="<?php echo base_url("/administration/salles")?>">
                        <span class="icon fa fa-building"></span><span class="title">Salles</span>
                    </a>
                </li>
                <li <?php if(strstr(uri_string(),"/plageshoraires")){echo 'class="active"';} ?>>
                    <a href="<?php echo base_url("/administration/plageshoraires")?>">
                        <span class="icon fa fa-calendar"></span><span class="title">Plages horaires</span>
                    </a>
                </li>
                <li <?php if(strstr(uri_string(),"/historique")){echo 'class="active"';} ?>>
                    <a href="<?php echo base_url("/administration/historique")?>">
                        <span class="icon fa fa-history"></span><span class="title">Historique</span>
                    </a>
                </li>
            </ul>
        </div>
        <!-- /.navbar-collapse -->
    </nav>
</div>
