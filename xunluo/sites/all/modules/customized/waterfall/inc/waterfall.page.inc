<?php

function waterfall_content()
{	
	//Before creating the content let's add main files required for imce to function properly.
  $path = drupal_get_path('module', 'waterfall');
  drupal_add_js($path . '/js/jquery.masonry.min.js');
  drupal_add_js($path . '/js/jquery.infinitescroll.js');
 // drupal_add_css($path . '/css/waterfall.css');
	
	$output = '';
	$query = db_select('node','n')->extend('PagerDefault');	
    //    $query->join('field_data_field_theme_installed', 'i', 'n.nid = i.entity_id'); // JOIN users with users_roles
	$query->fields('n')
             //   ->fields('i',array('field_theme_installed_value'))
		->condition('n.status', 1)
		->condition('n.type', 'document')
		->limit(12);
	$objects = $query->execute()->fetchAll();
	$rows = array();
	foreach ($objects as $key=>$object) {
            $doc_node = node_load($object -> nid);
		$row = array();
		$row['nid'] = $object -> nid;
		$row['title'] = $object -> title;
                if(count($doc_node->field_image)){
                    $row['uri'] = $doc_node->field_image['und']['0']['uri'];
                }else{
                    $row['uri'] = '#';
                }
               if(count($doc_node->body)){
                    $row['teaser'] = substr($doc_node->body['und'][0]['value'], 0, 80).'... ...';
               }else{
                   $row['teaser'] = '';
               }

                
		$rows[] = $row;
	}
	$output .= theme('waterfall_content', array('rows' => $rows));
	$output .= theme('waterfall_pager');
	//$output .= theme('pager_next', array('text' => t('next ›'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
	//$output .= theme('pager', array('quantity' => 0));
	//$output .= theme('pager_next', array('text' => t('next ›'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
	//$output .= '<div class="pager">'.theme('pager_next', array('text' => 'next >')).'</div>';
	return $output;
}


function waterfall_doctype_content($area_tid,$doc_tid){
    $couny_tid = arg(2);
    
    return $couny_tid.'--'.$doc_tid;
}
