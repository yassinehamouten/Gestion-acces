<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Welcome extends CI_Controller {

    public function index()
    {
        if($this->input->post('submit')){
            $this->form_validation->set_rules('username', 'Utilisateur', 'trim|required|min_length[4]');
            $this->form_validation->set_rules('password', 'Mot de passe', 'trim|required|min_length[4]');

            if ($this->form_validation->run() == FALSE){
                echo "erreur";
            }else{
                $login = $this->input->post('username');
                $password = $this->input->post('password');

                $this->auth->connect($login,$password);
                if($this->auth->connected()){
                    $this->session->set_flashdata("succes","Vous êtes connecté !");
                    redirect('/administration', 'refresh');
                }else{
                    $this->session->set_flashdata("erreur","Vérifier vos identifiants de connexion !");
                    redirect('/', 'refresh');
                }
            }
        }
        $data["titre"] = "Login";
        $data["contenu"] = $this->load->view('pages/login', '', true);
        $this->load->view('templates/login', $data);
    }
    
}
