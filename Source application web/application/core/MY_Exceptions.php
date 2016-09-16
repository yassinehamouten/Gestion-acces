<?php

defined('BASEPATH') OR exit('No direct script access allowed');
 
class MY_Exceptions extends CI_Exceptions {
   
    function __construct()
    {
        parent::__construct();    
    }
  
    public function show_404_perso($message)
    {
        $header = 'Page non trouvée';
        $template = "perso/error_404";
        $status = 404;
        return $this->show_error($header, $message, $template, $status);
    }
}