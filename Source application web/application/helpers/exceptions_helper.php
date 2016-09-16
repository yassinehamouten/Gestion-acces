<?php
defined('BASEPATH') OR exit('No direct script access allowed');
/**
 * Defines common exception functions that are globally available
 */
 
if ( ! function_exists('show_404_perso'))
{
    function show_404_perso($message, $instance)
    {
        $_error =& load_class('Exceptions', 'core');
        $_error->config =& $instance->config;
        $_error->myform =& $instance->myform;
        $_error->load =& $instance->load;
        
        echo $_error->show_404_perso($message);
        exit;
    }
}