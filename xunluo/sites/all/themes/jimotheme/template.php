<?php

/**
 * Add body classes if certain regions have content.
 */
function jimotheme_preprocess_html(&$variables) {
  
}

function jimotheme_preprocess_page(&$variables) {
    
  if (!empty($variables['node'])) {   
           $variables['theme_hook_suggestions'][] = 'page__node_' . $variables['node']->type;    
          
  }
  
  // print_r($variables['theme_hook_suggestions']);
}

function jimotheme_preprocess_node(&$variables) {
    
    $node = empty($variables['node']) ? FALSE : $variables['node'];
  
      global $user; 
      if ($node) {
          $variables['theme_hook_suggestions'][] = 'node__' . $node->type;    
      } else {
           
      } 
  // print_r($variables['theme_hook_suggestions']);
}

function jimotheme_theme() {
  $items = array();
   
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'jimotheme') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
       'jimotheme_preprocess_user_login'
    ),
  );
 
  return $items;
}    


function jimotheme_preprocess_user_login(&$vars) {
  $vars['intro_text'] = t('This is my awesome login form');
}

function jimotheme_render($node, $field){
    if(isset($node->{$field}['und'])){
        return  $node->{$field}['und'][0]['value'];
    } else {
        return '';
    }
}