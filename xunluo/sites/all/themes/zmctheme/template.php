<?php

/**
 * Add body classes if certain regions have content.
 */
function zmctheme_preprocess_html(&$variables) {
    if (!empty($variables['page']['featured'])) {
        $variables['classes_array'][] = 'featured';
    }

    if (!empty($variables['page']['triptych_first']) || !empty($variables['page']['triptych_middle']) || !empty($variables['page']['triptych_last'])) {
        $variables['classes_array'][] = 'triptych';
    }

    if (!empty($variables['page']['footer_firstcolumn']) || !empty($variables['page']['footer_secondcolumn']) || !empty($variables['page']['footer_thirdcolumn']) || !empty($variables['page']['footer_fourthcolumn'])) {
        $variables['classes_array'][] = 'footer-columns';
    }

    
    //  drupal_add_js(path_to_theme() . '/js/system_crud.js');
    //  drupal_add_js(path_to_theme() . '/js/camera_crud.js');
     //drupal_add_js(path_to_theme() . '/js/datagrid-detailview.js');
  //  print_r($variables['theme_hook_suggestions']);
}

/* hook_theme
 * 
 */
function zmctheme_theme($existing, $type, $theme, $path) {
    $items = array();

    $items['user_login_block'] = array(
        'render element' => 'form',
        'template' => 'templates/user-login',
    );

    return $items;
}


/**
 * Override or insert variables into the page template for HTML output.
 */
function zmctheme_process_html(&$variables) {
    
}

/**
 * Override or insert variables into the page template.
 */
function zmctheme_process_page(&$variables) {

    // Always print the site name and slogan, but if they are toggled off, we'll
    // just hide them visually.
    $variables['hide_site_name'] = theme_get_setting('toggle_name') ? FALSE : TRUE;
    $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
    if ($variables['hide_site_name']) {
        // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
        $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
    }
    if ($variables['hide_site_slogan']) {
        // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
        $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
    }
    // Since the title and the shortcut link are both block level elements,
    // positioning them next to each other is much simpler with a wrapper div.
    if (!empty($variables['title_suffix']['add_or_remove_shortcut']) && $variables['title']) {
        // Add a wrapper div using the title_prefix and title_suffix render elements.
        $variables['title_prefix']['shortcut_wrapper'] = array(
            '#markup' => '<div class="shortcut-wrapper clearfix">',
            '#weight' => 100,
        );
        $variables['title_suffix']['shortcut_wrapper'] = array(
            '#markup' => '</div>',
            '#weight' => -99,
        );
        // Make sure the shortcut link is the first item in title_suffix.
        $variables['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
    }
  // print_r($variables['theme_hook_suggestions']);
}

/**
 * Override or insert variables into the node template.
 */
function zmctheme_preprocess_node(&$variables) {
    if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
        $variables['classes_array'][] = 'node-full';
    }
    //  print_r($variables['theme_hook_suggestions']);
}

/**
 * Override or insert variables into the block template.
 */
function zmctheme_preprocess_block(&$variables) {
    // In the header region visually hide block titles.
    if ($variables['block']->region == 'header') {
        $variables['title_attributes_array']['class'][] = 'element-invisible';
    }
}

/**
 * Implements theme_menu_tree().
 */
function zmctheme_menu_tree($variables) {


    return '<ul class="menu clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree() for oakadmin menu.
 */
function zmctheme_menu_tree__main_menu($variables) {
    return '<div class="easyui-accordion" style="width:180px;">' . $variables['tree'] . '</div>';
}

/**
 * Theme the oakadmin_oakadmin_menu.
 */
function zmctheme_menu_link__main_menu(&$variables) {
    $element = $variables['element']; 
    $sub_menu = '';
    
    if (!$element['#original_link']['plid']) { //there is the first level menu
        if ($element['#original_link']['has_children']) { //has a submenu 
            $parameters = array(
                'active_trail' => array($element['#original_link']['plid']),
                'only_active_trail' => FALSE,
                'min_depth' => $element['#original_link']['depth'] + 1,
                'max_depth' => $element['#original_link']['depth'] + 1,
                'conditions' => array('plid' => $element['#original_link']['mlid']),
            );

            $children = menu_build_tree('main-menu', $parameters);
            foreach ($children as $link) {
         //       $link['link']['localized_options']['attributes']['class'][] = 'easyui-linkbutton';
                $link['link']['localized_options']['attributes']['data-options'][] = 'iconCls:\'icon-add\'';
                $link['link']['localized_options']['attributes']['plain'][] = 'true';
                $link['link']['localized_options']['attributes']['iconAlign'][] = 'top';
                $link['link']['localized_options']['attributes']['onclick'] = 'openTab("'.$link['link']['title'].'","'.$link['link']['href'].'");return false;';


                //   $sub_menu .=  '<a href="'.url($link['link']['href']).'" class="easyui-linkbutton" data-options="iconCls:\'icon-add\'">'.$link['link']['title'].'</a>'; 
                $sub_menu .= '<li>'.l($link['link']['title'], $link['link']['href'], $link['link']['localized_options']).'</li>';
            }
        }
     return '<div title="' . $element['#title'] . '" data-options="iconCls:\'icon-'.$element['#original_link']['mlid'].'\'" style="overflow:auto;padding:2px;"><ul id="menu-tree-'.$element['#original_link']['mlid'].'" class="easyui-tree">'.$sub_menu . '</ul></div>';
            
        
      }
}

/**
 * Implements theme_menu_link().
 */
function zmctheme_menu_link(array $variables) {
    $element = $variables['element'];

    $sub_menu = '';
    if ($element['#below']) {
        $sub_menu = drupal_render($element['#below']);
    }
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . '<div class = "submenucont">' . $sub_menu . "</div></li>\n";
}

/**
 * Implements theme_field__field_type().
 */
function zmctheme_field__taxonomy_term_reference($variables) {
    $output = '';

    // Render the label, if it's not hidden.
    if (!$variables['label_hidden']) {
        $output .= '<h3 class="field-label">' . $variables['label'] . ': </h3>';
    }

    // Render the items.
    $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
    foreach ($variables['items'] as $delta => $item) {
        $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
    }
    $output .= '</ul>';

    // Render the top-level DIV.
    $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '"' . $variables['attributes'] . '>' . $output . '</div>';

    return $output;
}
