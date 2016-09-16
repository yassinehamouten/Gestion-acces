<!DOCTYPE html>
<html>

<head>
    <title>404 Page non trouvée!</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/css/404_core.css")?>">
    <link rel="stylesheet" type="text/css" href="<?php echo base_url("/assets/css/404.css")?>">
</head>
<body>
    <div class="container">
        <div class="wrapper row2">
            <div id="container" class="clear">
              <section id="fof" class="clear">
                <div class="hgroup clear">
                  <h1>404</h1>
                  <h2>Erreur ! <span>Page non trouvée</span></h2>
                </div>
                <p><?php echo $message;?></p>
                <p><a href="javascript:history.go(-1)">&laquo; Retour en arrière</a> / <a href="http://lab.yassinehamouten.ovh/gestion_acces/administration/">Page d'accueil &raquo;</a></p>
              </section>
            </div>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.4/jquery.min.js"></script>
    <script>
        $(".container").height($(window).height());

        $(window).resize(function(){
            $(".container").height($(window).height());
        });
    </script>
</body>