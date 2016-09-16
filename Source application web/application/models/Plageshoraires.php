<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Plageshoraires extends CI_Model
{
    public function get_info($id){
        $this->db->select('*');
        $this->db->from('plageshoraires');
        $this->db->join('classes', 'classes.idClasse = plageshoraires.idClasse');
        $this->db->join('salles', 'salles.idSalle = plageshoraires.idSalle');
        $this->db->join('statuts', 'statuts.idStatut = plageshoraires.idStatut');
        $this->db->where('idPlagehoraire', $id);
        $query = $this->db->get();
        return $query->result();
    }
    
    public function addPlagehoraire($idClasse, $idSalle, $idStatut, $debut, $fin, $jour){
        $this->db->set('idClasse', $idClasse);
        $this->db->set('idSalle', $idSalle);
        $this->db->set('idStatut', $idStatut);
        $this->db->set('debut', $debut);
        $this->db->set('fin', $fin);
        $this->db->set('jour', $jour);
        $this->db->insert('plageshoraires');
    }
    
    public function updatePlagehoraire($id, $idClasse, $idSalle, $idStatut, $debut, $fin, $jour){
        $this->db->set('idClasse', $idClasse);
        $this->db->set('idSalle', $idSalle);
        $this->db->set('idStatut', $idStatut);
        $this->db->set('debut', $debut);
        $this->db->set('fin', $fin);
        $this->db->set('jour', $jour);
        $this->db->where('idPlagehoraire', $id);
        $this->db->update('plageshoraires');
    }
    
}

