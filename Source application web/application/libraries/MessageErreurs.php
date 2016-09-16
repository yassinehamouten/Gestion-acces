<?php
if ( ! defined('BASEPATH')) exit('No direct script access allowed');

/**
* Permet de gérer les 404
*
* @author Yassine Hamouten
*/

class MessageErreurs {

    public $erreur;

    public function setErreur($erreur){

        $this->erreur = $erreur;

    }

    public function getErreur(){

        return $this->erreur;

    }

}
