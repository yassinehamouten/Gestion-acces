<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Utilisateurs extends CI_Model
{
    
    public function get_info($id){
        $query = $this->db->get_where('utilisateurs', array('idUtilisateur' => $id));
        return $query->result();
    }
    
    public function addUser($nom, $prenom, $idClasse, $codeRFID, $login, $password, $idStatut){
        $this->db->set('nom', $nom);
        $this->db->set('prenom', $prenom);
        $this->db->set('idClasse', $idClasse);
        $this->db->set('codeRFID', $codeRFID);
        $this->db->set('login', $login);
        $this->db->set('motPasse', $password);
        $this->db->set('idStatut', $idStatut);
        $this->db->insert('utilisateurs');
    }
    
    public function updateUser($id, $nom, $prenom, $idClasse, $codeRFID, $login, $password, $idStatut){
        $this->db->set('nom', $nom);
        $this->db->set('prenom', $prenom);
        $this->db->set('idClasse', $idClasse);
        $this->db->set('codeRFID', $codeRFID);
        $this->db->set('login', $login);
        $this->db->set('motPasse', $password);
        $this->db->set('idStatut', $idStatut);
        $this->db->where('idUtilisateur', $id);
        $this->db->update('utilisateurs');
    }
    
}

