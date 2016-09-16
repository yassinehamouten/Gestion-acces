# Gestion accès
Gestion accès a été mon projet de fin d'année de BTS.


## Application web

L'application web est écrite en PHP avec le framework codeigniter.

### Config
##### URL de l'application
fichier: application/config/config.php

$config['base_url'] = 'http://VOTREURL/gestion_acces/';

##### Base de données
fichier: application/config/database.php

'dsn'	=> 'mysql:host=localhost; dbname=gestionacces',
	'hostname' => 'mysql:host=localhost',
	'username' => '',
	'password' => '',
	'database' => 'gestionacces'

### Plus d'infos
- Pas de système de cache  
- Penser à changer l'environnement en "production" fichier index.php
- le site n'est pas complètement sécurisé ( par exemple l'envoie de fichier CSV )
- <a href="https://github.com/tui2tone/flat-admin-bootstrap-templates">Thème utilisé</a>
