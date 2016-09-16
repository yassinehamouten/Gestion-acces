<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

/**
* Permet de gérer la connexion à l'espace admin
*
* @author Yassine Hamouten
*/

class Auth {

    private $sel = "";
    private $ci;

    public function __construct(){
        $this->ci = get_instance();
    }

    public function getPassword($mdp){
        return hash('sha256', $this->sel.$mdp.$this->sel);
    }

    public function connect($login, $password){
        $query = $this->ci->db->query("SELECT * FROM utilisateurs WHERE login=? AND motPasse =?", array($login,$password));
        $result = $query->result();
        if(isset($result[0]->prenom)){
            $this->ci->session->set_userdata('username', $result[0]->prenom);
            $this->ci->session->set_userdata('id', $result[0]->idUtilisateur);
        }
    }

    public function connected(){
        $user = $this->ci->session->userdata('username');
        if(isset($user)){
            return true;
        }else{
            return false;
        }
    }

    public function redirectToLogin(){
        redirect('/', 'refresh');
    }

    public function deconnect(){
        $this->ci->session->unset_userdata('username');
        $this->ci->session->unset_userdata('id');
    }

    public function getUser(){
        return $this->ci->session->userdata('username');
    }

    public function getUserId(){
        return $this->ci->session->userdata('id');
    }

}
