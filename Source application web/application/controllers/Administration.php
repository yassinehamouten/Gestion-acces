<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Administration extends CI_Controller {

    public function __construct(){
        parent::__construct();
        if(!$this->auth->connected()){
            $this->auth->redirectToLogin();
            die();
        }
        $this->breadcrumb->instance($this);
    }

    public function logout()
    {
        $this->auth->deconnect();
        $this->session->set_flashdata("succes","Vous avez été déconnecté avec succès");
        redirect('/', 'refresh');
    }

    public function profil()
    {
        $this->load->model('user');
        if($this->input->post('submit')){
            $this->form_validation->set_rules('password', 'Mot de passe', 'trim|required|min_length[5]');
            if ($this->form_validation->run() == FALSE){
                echo "erreur";
            }else{
                $password = $this->input->post('password');

                $this->user->editMDP($this->auth->getUserId(), $password);
                $this->session->set_flashdata("succes","Mot de passe changé");
                redirect('/administration', 'refresh');
            }
        }
        $data["user"] = $this->user->getUser($this->auth->getUserId());
        $data["contenu"] = $this->load->view('pages/admin/profil', $data, true);
        $this->load->view('templates/defaut', $data);
    }

    public function index(){
        $data["user"] = $this->auth->getUser();
        $data["nbUsers"] = $this->db->count_all('utilisateurs');
        $data["nbSalles"] = $this->db->count_all('salles');
        $date = date('Y-m-d');
        $this->db->like('dateTentative', $date);
        $this->db->from('historique');
        $data["nbHistorique"] = $this->db->count_all_results();
        $data["titre"] = "Accueil";
        $query = $this->db->query("SELECT nomClasse, COUNT( * ) AS nb_etudiants FROM utilisateurs, classes WHERE utilisateurs.idClasse = classes.idClasse GROUP BY utilisateurs.idClasse");
        $data["charts"]["etudiants"] = $query->result();
        $date = date('Y-m');
        $query = $this->db->query("SELECT DATE_FORMAT(dateTentative,'%Y-%m-%d') AS jour, etat, COUNT( * ) AS nb_tentatives FROM historique WHERE dateTentative > '$date' GROUP BY DATE_FORMAT(dateTentative,'%Y-%m-%d'), etat");
        $arrayJours = array('01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12', '13', '14','15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31');
        $tbJours[0]['jour'] = 01;
        $tbJours[0]['nb'] = 0;
        $tbJours[0]['etat'] = 0;
        foreach($query->result() as $jours){
            $jour = explode('-',$jours->jour);
            $jour =  end($jour);
            foreach($arrayJours as $tjours){
                if($tjours == $jour){
                    $tbJours[$tjours]['jour'] = $jour;
                    $tbJours[$tjours]['nb'] = $jours->nb_tentatives;
                    $tbJours[$tjours]['etat'] = $jours->etat;
                }else{
                    $tbJours[$tjours]['jour'] = $tjours;
                    $tbJours[$tjours]['nb'] = 0;
                    $tbJours[$tjours]['etat'] = 0;
                }
            }
        }
        $data["charts"]["historique"] = $tbJours;
        $data["contenu"] = $this->load->view('pages/admin/index', $data, true);
        $this->load->view('templates/accueil', $data);
    }

    public function utilisateurs($action = null, $id = null, $paramEnTrop = null){
        if($paramEnTrop){
            show_404_perso("Cette page n'existe pas", get_instance());
            die();
        }
        $data["user"] = $this->auth->getUser();
        $this->load->model('utilisateurs');
        if(isset($action)){
            if($action == "edit"){
                // modifie un utilisateur
                if(isset($id)){
                    if($this->input->post('submit')){
                        $this->form_validation->set_rules('prenom', 'Prenom', 'trim|required|min_length[3]');
                        $this->form_validation->set_rules('nom', 'Nom', 'trim|required|min_length[4]');
                        $this->form_validation->set_rules('idClasse', 'ID Classe', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('idStatut', 'ID Statut', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('codeRFID', 'Code RFID', 'trim|required|min_length[12]|max_length[12]');
                        $this->form_validation->set_rules('login', 'Login', 'trim|min_length[1]');
                        $this->form_validation->set_rules('password', 'Mot de passe', 'trim|min_length[1]');
                        if ($this->form_validation->run() == FALSE){
                            $this->session->set_flashdata("erreur","Veuillez verifier les champs!");
                        }else{
                            $nom = $this->input->post('nom');
                            $prenom = $this->input->post('prenom');
                            $idClasse = $this->input->post('idClasse');
                            $codeRFID = $this->input->post('codeRFID');
                            $login = $this->input->post('login');
                            $password = $this->input->post('password');
                            $idStatut = $this->input->post('idStatut');

                            $this->utilisateurs->updateUser($id, $nom, $prenom, $idClasse, $codeRFID, $login, $password, $idStatut);
                            $this->session->set_flashdata("succes","Vous venez de modifié un utilisateur");
                            redirect('/administration/utilisateurs', 'refresh');
                        }
                    }
                    $data["user"] = $this->utilisateurs->get_info($id);
                    if(!empty($data["user"])){
                        $data["titre"] = "Edition utilisateur : ". $data["user"][0]->prenom ." ". $data["user"][0]->nom;
                        $data["id"] = $id;
                        $data["contenu"] =  $this->load->view('pages/admin/utilisateurs/utilisateurs_edit', $data, true);
                        $this->load->view('templates/defaut', $data);
                    }else{
                        // redirection page utilisateur -> pas d'utilisateur avec cet id
                        redirect('/administration/utilisateurs', 'refresh');
                    }
                }else{
                    redirect('/administration/utilisateurs', 'refresh');
                }
            }
            if($action == "add"){
                // ajout d'un utilisateur
                if($this->input->post('submit')){
                    $this->form_validation->set_rules('prenom', 'Prenom', 'trim|required|min_length[3]');
                    $this->form_validation->set_rules('nom', 'Nom', 'trim|required|min_length[4]');
                    $this->form_validation->set_rules('idClasse', 'ID Classe', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('idStatut', 'ID Statut', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('codeRFID', 'Code RFID', 'trim|required|min_length[12]|max_length[12]');
                    $this->form_validation->set_rules('login', 'Login', 'trim|min_length[1]');
                    $this->form_validation->set_rules('password', 'Mot de passe', 'trim|min_length[1]');
                    $nom = $this->input->post('nom');
                    $prenom = $this->input->post('prenom');
                    $idClasse = $this->input->post('idClasse');
                    $codeRFID = $this->input->post('codeRFID');
                    $login = $this->input->post('login');
                    $password = $this->input->post('password');
                    $idStatut = $this->input->post('idStatut');
                    if ($this->form_validation->run() == FALSE){
                        $this->session->set_flashdata("erreur","Veuillez verifier les champs!");
                        $data["utilisateur"]["nom"] = $nom;
                        $data["utilisateur"]["prenom"] = $prenom;
                        $data["utilisateur"]["idClasse"] = $idClasse;
                        $data["utilisateur"]["RFID"] = $codeRFID;
                        $data["utilisateur"]["login"] = $login;
                        $data["utilisateur"]["password"] = $password;
                        $data["utilisateur"]["idStatut"] = $idStatut;
                    }else{
                        $this->utilisateurs->addUser($nom, $prenom, $idClasse, $codeRFID, $login, $password, $idStatut);
                        $this->session->set_flashdata("succes","Vous venez d'ajouté un utilisateur");
                        redirect('/administration/utilisateurs', 'refresh');
                    }
                }
                $data["titre"] = "Ajouter un utilisateur";
                $data["contenu"] =  $this->load->view('pages/admin/utilisateurs/utilisateurs_ajout', $data, true);
                $this->load->view('templates/defaut', $data);
            }
        }else{
            if($this->input->post('submit')){
                $uploadfile = './temp/'.$_FILES['fichier']['name'];
                move_uploaded_file($_FILES['fichier']['tmp_name'], $uploadfile);
                $csv = array_map('str_getcsv', file($uploadfile));
                $nbUtilisateurs = count($csv);
                foreach($csv as $user){
                    $this->utilisateurs->addUser($user[1], $user[2], $user[3], $user[4], $user[5], $user[6], $user[7]);
                }
                unlink('./temp/'.$_FILES['fichier']['name']);
                $this->session->set_flashdata("succes","Vous venez d'importé une liste de ".$nbUtilisateurs." utilisateurs");
                redirect("/administration/utilisateurs");
            }
            $data["titre"] = "Utilisateurs";
            $data["contenu"] =  $this->load->view('pages/admin/utilisateurs/utilisateurs', '', true);
            $this->load->view('templates/defaut', $data);
        }
    }

    public function historique($paramEnTrop = null){
        if($paramEnTrop){
            show_404_perso("Cette page n'existe pas", get_instance());
            die();
        }
        $data["user"] = $this->auth->getUser();
        $data["titre"] = "historique";
        $data["contenu"] =  $this->load->view('pages/admin/historique', '', true);
        $this->load->view('templates/defaut', $data);
    }

    public function salles($action = null, $id = null, $paramEnTrop = null){
        if($paramEnTrop){
            show_404_perso("Cette page n'existe pas", get_instance());
            die();
        }
        $data["user"] = $this->auth->getUser();
        $this->load->model('salles');
        if(isset($action)){
            if($action == "edit"){
                // modification d'un utilisateur
                if(isset($id)){
                    if($this->input->post('submit')){
                        $this->form_validation->set_rules('nom', 'Nom de la salle', 'trim|required|min_length[1]');
                        if ($this->form_validation->run() == FALSE){
                            echo "erreur";
                        }else{
                            $nom = $this->input->post('nom');

                            $this->salles->updateSalle($id, $nom);
                            $this->session->set_flashdata("succes","Modification enregistrée");
                            redirect('/administration/salles', 'refresh');
                        }
                    }
                    $data["salle"] = $this->salles->get_info($id);
                    if(!empty($data["salle"])){
                        $data["titre"] = "Edition de la salle : ". $data["salle"][0]->nomSalle;
                        $data["id"] = $id;
                        $data["contenu"] =  $this->load->view('pages/admin/salles/salles_edit', $data, true);
                        $this->load->view('templates/defaut', $data);
                    }else{
                        // redirection page salles -> pas de salle avec cet id
                        redirect('/administration/salles', 'refresh');
                    }
                }else{
                    redirect('/administration/salles', 'refresh');
                }
            }
            if($action == "add"){
                // ajout d'une salle
                if($this->input->post('submit')){
                    $this->form_validation->set_rules('nom', 'Nom de la salle', 'trim|required|min_length[1]');
                    if ($this->form_validation->run() == FALSE){
                        echo "erreur";
                    }else{
                        $nom = $this->input->post('nom');

                        $this->salles->addSalle($nom);
                            $this->session->set_flashdata("succes","Ajout effectué avec succés");
                        redirect('/administration/salles', 'refresh');
                    }
                }
                $data["titre"] = "Ajouter une salle";
                $data["contenu"] =  $this->load->view('pages/admin/salles/salles_ajout', $data, true);
                $this->load->view('templates/defaut', $data);
            }
        }else{
            $data["titre"] = "salles";
            $data["contenu"] =  $this->load->view('pages/admin/salles/salles', '', true);
            $this->load->view('templates/defaut', $data);
        }
    }

    public function plageshoraires($action = null, $id = null, $paramEnTrop = null){
        if($paramEnTrop){
            show_404_perso("Cette page n'existe pas", get_instance());
            die();
        }
        $data["user"] = $this->auth->getUser();
        $this->load->model('plageshoraires');
        if(isset($action)){
            if($action == "edit"){
                // modification d'un utilisateur
                if(isset($id)){
                    if($this->input->post('submit')){
                        $this->form_validation->set_rules('idSalle', 'Nom de la salle', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('idClasse', 'Nom de la classe', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('idStatut', 'Nom du statut', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('jour', 'Nom du jour', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('debut', 'Debut', 'trim|required|min_length[1]');
                        $this->form_validation->set_rules('fin', 'Fin', 'trim|required|min_length[1]');
                        if ($this->form_validation->run() == FALSE){
                            echo "erreur";
                        }else{
                            $idSalle = $this->input->post('idSalle');
                            $idClasse = $this->input->post('idClasse');
                            $idStatut = $this->input->post('idStatut');
                            $jour = $this->input->post('jour');
                            $debut = $this->input->post('debut');
                            $fin = $this->input->post('fin');

                            $this->plageshoraires->updatePlagehoraire($id, $idClasse, $idSalle, $idStatut, $debut, $fin, $jour);
                            $this->session->set_flashdata("succes","Modification enregistrée");
                            redirect('/administration/plageshoraires', 'refresh');
                        }
                    }
                    $data["plagehoraire"] = $this->plageshoraires->get_info($id);
                    if(!empty($data["plagehoraire"])){
                        $data["titre"] = "Edition plage horaire";
                        $data["id"] = $id;
                        $data["contenu"] =  $this->load->view('pages/admin/plageshoraires/plageshoraires_edit', $data, true);
                        $this->load->view('templates/plagehoraire', $data);
                    }else{
                        // redirection page plageshoraires -> pas de plage horaire avec cet id
                        redirect('/administration/plageshoraires', 'refresh');
                    }
                }else{
                    redirect('/administration/plageshoraires', 'refresh');
                }
            }
            if($action == "add"){
                // ajout d'une salle
                if($this->input->post('submit')){
                    $this->form_validation->set_rules('idSalle', 'Nom de la salle', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('idClasse', 'Nom de la classe', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('idStatut', 'Nom du statut', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('jour', 'Nom du jour', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('debut', 'Debut', 'trim|required|min_length[1]');
                    $this->form_validation->set_rules('fin', 'Fin', 'trim|required|min_length[1]');
                    if ($this->form_validation->run() == FALSE){
                        echo "erreur";
                    }else{
                        $idSalle = $this->input->post('idSalle');
                        $idClasse = $this->input->post('idClasse');
                        $idStatut = $this->input->post('idStatut');
                        $jour = $this->input->post('jour');
                        $debut = $this->input->post('debut');
                        $fin = $this->input->post('fin');

                        $this->plageshoraires->addPlagehoraire($idClasse, $idSalle, $idStatut, $debut, $fin, $jour);
                        $this->session->set_flashdata("succes","Ajout effectué avec succés");
                        redirect('/administration/plageshoraires', 'refresh');
                    }
                }
                $data["titre"] = "Ajouter une plage horaire";
                $data["contenu"] =  $this->load->view('pages/admin/plageshoraires/plageshoraires_ajout', $data, true);
                $this->load->view('templates/plagehoraire', $data);
            }
        }else{
            $data["titre"] = "historique";
            $data["contenu"] =  $this->load->view('pages/admin/plageshoraires/plageshoraires', '', true);
            $this->load->view('templates/defaut', $data);
        }
    }

    public function classes($action = null, $id = null, $paramEnTrop = null){
        if($paramEnTrop){
            show_404_perso("Cette page n'existe pas", get_instance());
            die();
        }
        $data["user"] = $this->auth->getUser();
        $this->load->model('classes');
        if(isset($action)){
            if($action == "edit"){
                // Modification d'une classe
                if(isset($id)){
                    if($this->input->post('submit')){
                        $this->form_validation->set_rules('nom', 'Nom de la classe', 'trim|required|min_length[1]');
                        if ($this->form_validation->run() == FALSE){
                            echo "erreur";
                        }else{
                            $nom = $this->input->post('nom');

                            $this->classes->updateClasse($id, $nom);
                            $this->session->set_flashdata("succes","Modification enregistrée");
                            redirect('/administration/classes', 'refresh');
                        }
                    }
                    $data["classe"] = $this->classes->get_info($id);
                    if(!empty($data["classe"])){
                        $data["titre"] = "Edition de la classe : ". $data["classe"][0]->nomClasse;
                        $data["id"] = $id;
                        $data["contenu"] =  $this->load->view('pages/admin/classes/classes_edit', $data, true);
                        $this->load->view('templates/defaut', $data);
                    }else{
                        // redirection page classes -> pas de classe avec cet id
                        redirect('/administration/classes', 'refresh');
                    }
                }else{
                    redirect('/administration/classes', 'refresh');
                }
            }
            if($action == "add"){
                // ajout d'une salle
                if($this->input->post('submit')){
                    $this->form_validation->set_rules('nom', 'Nom de la classe', 'trim|required|min_length[1]');
                    if ($this->form_validation->run() == FALSE){
                        echo "erreur";
                    }else{
                        $nom = $this->input->post('nom');

                        $this->classes->addClasse($nom);
                        $this->session->set_flashdata("succes","Ajout effectué avec succés");
                        redirect('/administration/classes', 'refresh');
                    }
                }
                $data["titre"] = "Ajouter une classe";
                $data["contenu"] =  $this->load->view('pages/admin/classes/classes_ajout', $data, true);
                $this->load->view('templates/defaut', $data);
            }
        }else{
            $data["titre"] = "classes";
            $data["contenu"] =  $this->load->view('pages/admin/classes/classes', '', true);
            $this->load->view('templates/defaut', $data);
        }
    }

}
