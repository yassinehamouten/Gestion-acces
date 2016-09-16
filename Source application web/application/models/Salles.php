<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Salles extends CI_Model
{
    public function get_info($id){
        $query = $this->db->get_where('salles', array('idSalle' => $id));
        return $query->result();
    }
    
    public function addSalle($nom){
        $this->db->set('nomSalle', $nom);
        $this->db->insert('salles');
    }
    
    public function updateSalle($id, $nom){
        $this->db->set('nomSalle', $nom);
        $this->db->where('idSalle', $id);
        $this->db->update('salles');
    }
    
}

