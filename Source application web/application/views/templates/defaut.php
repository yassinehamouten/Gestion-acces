<!DOCTYPE html>
<html>

<head>
    <title><?php echo $titre ?></title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- Fonts -->
    <link href='http://fonts.googleapis.com/css?family=Roboto+Condensed:300,400' rel='stylesheet' type='text/css'>
    <link href='http://fonts.googleapis.com/css?family=Lato:300,400,700,900' rel='stylesheet' type='text/css'>
    <!-- CSS Libs -->
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/bootstrap.min.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/font-awesome.min.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/animate.min.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/bootstrap-switch.min.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/checkbox3.min.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/jquery.dataTables.min.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/dataTables.bootstrap.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/lib/css/select2.min.css")?>">
    <!-- CSS App -->
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/css/style.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/css/themes/flat-blue.css")?>">
</head>

<body class="flat-blue">
    <div class="app-container">
        <div class="row content-container">
            
            <?php $this->load->view("templates/menu/defaut_menu"); ?>
            <!-- Main Content -->
            <div class="container-fluid">
                
                <?php echo $contenu; ?>
        
            </div>
        </div>
        <footer class="app-footer">
            <div class="wrapper">
                <span class="pull-right"><a href="#"><i class="fa fa-long-arrow-up"></i></a></span>Gestion accès 2016
            </div>
        </footer>
    </div>
    <!-- Javascript Libs -->
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/jquery.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/bootstrap.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/Chart.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/bootstrap-switch.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/jquery.matchHeight-min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/jquery.dataTables.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/dataTables.bootstrap.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/select2.full.min.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/ace/ace.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/ace/mode-html.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/lib/js/ace/theme-github.js")?>"></script>
    <!-- Javascript -->
    <script type="text/javascript" src="<?php echo base_url("/assets/js/app.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/js/index.js")?>"></script>

    <script>
        $("#alert").fadeTo(2000, 500).slideUp(500, function(){
            $("#salert").alert('close');
        });
    </script>
</body>

</html>