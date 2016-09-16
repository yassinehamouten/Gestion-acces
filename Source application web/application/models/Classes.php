<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Classes extends CI_Model
{
    public function get_info($id){
        $query = $this->db->get_where('classes', array('idClasse' => $id));
        return $query->result();
    }
    
    public function addClasse($nom){
        $this->db->set('nomClasse', $nom);
        $this->db->insert('classes');
    }
    
    public function updateClasse($id, $nom){
        $this->db->set('nomClasse', $nom);
        $this->db->where('idClasse', $id);
        $this->db->update('classes');
    }
    
}

