<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

/**
* Permet de générer un breadcrumb ( Fil d'Ariane ) automatiquement grace à l'URL
*
* @author Yassine Hamouten
*/

class Breadcrumb {

    public function instance($ci){
        $this->ci = $ci;
    }

    public function get(){
        $segments = $this->ci->uri->segment_array();
        $nbTotal = count($segments);
        $i=0;
        $prec = $this->ci->uri->slash_segment(1);

        echo '<ol class="breadcrumb">';
        foreach ($segments as $segment)
        {
            $i++;
            if($i!=1) $prec = $prec.$segment."/";
            if($i == $nbTotal){
                echo '<li class="active">'.$segment.'</a></li>';
            }else{
                echo '<li><a href="'.base_url($prec).'">'.$segment.'</a></li>';
            }
        }
        echo '</ol><br>';
    }

}
