<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class User extends CI_Model
{

    public function editMDP($id, $password){
        $this->db->set('motPasse', $password);
        $this->db->where('idUtilisateur', $id);
        $this->db->update('utilisateurs');
    }
    
    public function getUser($id){
        $query = $this->db->get_where('utilisateurs', array('idUtilisateur' => $id));
        return $query->result();
    }
    
}
