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
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/css/slide/slider-pips.css")?>">
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
    <script src="https://code.jquery.com/ui/1.11.1/jquery-ui.js"></script>
    <link rel="stylesheet" href="https://code.jquery.com/ui/1.10.4/themes/flick/jquery-ui.css">
    <!-- Javascript -->
    <script type="text/javascript" src="<?php echo base_url("/assets/js/app.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/js/index.js")?>"></script>
    <script type="text/javascript" src="<?php echo base_url("/assets/js/slide/slider-pips.js")?>"></script>
    <?php 
        if(isset($plagehoraire[0]->debut)){
            $debut = $plagehoraire[0]->debut;
        }else{
            $debut = 8;
        }
        if(isset($plagehoraire[0]->fin)){
            $fin = $plagehoraire[0]->fin;
        }else{
            $fin = 17;
        }
    ?>
    <script>
        $(".slider")
            .slider({
                max: 23,
                range: true,
                step: 0.50,
                values: [<?php echo $debut ?>, <?php echo $fin ?>]
            })
            .slider("pips", {
                rest: "label",
                step: 2
            });
    </script>
    <script>
        $(".slider").on("slidechange", function( e, ui ) {
            $("#debut").val( ui.values[0]); 
            $("#fin").val( ui.values[1]); 
        });
    </script>
        <script>
        $("#alert").fadeTo(2000, 500).slideUp(500, function(){
            $("#salert").alert('close');
        });
    </script>
</body>

</html>