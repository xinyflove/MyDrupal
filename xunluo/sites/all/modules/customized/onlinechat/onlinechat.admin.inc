<?php

function cpic_main_init_static_data(){
    $output = '';
    $build_arrays = drupal_get_form('cpic_main_init_data_form');
    
    return render($build_arrays);
}
function cpic_main_init_data_form($form, &$form_state) {
  
  /*  $form['fire_app_key'] = array(
    '#type' => 'textfield',
    '#title' => t('本应用的KEY'),
    '#default_value' => variable_get('fire_app_key', 'vsaas'),
    '#description' => t('如果使用vPaaS,必须得在平台首先创建一个appkey和appsecret,如果不知道，请联系vPaaS管理人员'),
    );
  
  */
    
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('批量初始化统计数据'),
  );

  return $form;
}

/**
 * Submit handler for form_example_element_demo_form().
 */
function cpic_main_init_data_form_submit($form, &$form_state) {
        $year  =  date('Y', strtotime('now'));
        $month =  date('m', strtotime('now'));
        $day =  date('d', strtotime('now'));
        $total_minutes = getMinutesOfMonth($month,$year);
        $type = 'corp';
   
    // 生成所有的企业统计数据
       
        $query = db_select('node','n');
        $query->condition('type', 'org');
        $query->fields('n');
        $results = $query->execute();
        foreach($results as $row){
           $query = db_merge('fire_statics')
              ->key(array(
                'nid' => $row->nid,
                'type' => $type,
                'year' => $year,
                'month' => $month,  
              ))
              ->fields(array(
                'year'=>$year,
                'month'=>$month,  
                'totalmins' => $total_minutes,
                'inspectrate' => 0,
                'ctrlroomoff' => 0,
                'ctrlroom_offtime' => 0,  
                'firelaneoccp' => 0,
                'firelane_occptime' => 0,
                'hydrant_waterpress' => 0,
                'sprinkler_waterpress' => 0,
                'box_waterlevel' => 0,
                'pool_waterlevel' => 0,
                'safeindex' => 0,
                
              ))
              ->execute();
           
          // 水系统排名数据
           $total_duraion = 0; 
           $waterrank = 0;
           $total_device = 0;
           $falut_device = 0;
           
           $query = db_merge('fire_statics_water')
              ->key(array(
                'nid' => $row->nid,
                'type' => $type,
                'year' => $year,
                'month' => $month,  
                'day'=>$day,                                      
              ))
              ->fields(array(
                'year'=>$year,
                'month'=>$month,  
                'day'=>$day,                    
                'totaldevice' => $total_device,
                'falutdevice' => $falut_device,
                'totalduration'=> $total_duraion,
                'waterrank' => $waterrank,
              ))
              ->execute();
           
          _create_fire_statics_task($type, $row->nid);

                  
        }
        
        
        // 添加企业类型的统计数据
         $type = 'btype';
         $vac_modes = taxonomy_vocabulary_machine_name_load('businesstype');
         $terms = taxonomy_get_tree($vac_modes->vid);
         foreach($terms as $term){
            $query = db_merge('fire_statics')
              ->key(array(
                'nid' => $term->tid,
                'type' => $type,
                'year' => $year,
                'month' => $month,  
              ))
              ->fields(array(
                'year'=>$year,
                'month'=>$month,  
                'totalmins' => $total_minutes,
                'inspectrate' => 0,
                'ctrlroomoff' => 0,
                'ctrlroom_offtime' => 0,  
                'firelaneoccp' => 0,
                'firelane_occptime' => 0,
                'hydrant_waterpress' => 0,
                'sprinkler_waterpress' => 0,
                'box_waterlevel' => 0,
                'pool_waterlevel' => 0,
                'safeindex' => 0,
                
              ))
              ->execute();
            
          // 水系统排名数据
           $total_duraion = 0; 
           $waterrank = 0;
           $total_device = 0;
           $falut_device = 0;
           
           $query = db_merge('fire_statics_water')
              ->key(array(
                'nid' => $term->tid,
                'type' => $type,
                'year' => $year,
                'month' => $month,  
                'day'=>$day,                                      
              ))
              ->fields(array(
                'year'=>$year,
                'month'=>$month,  
                'day'=>$day,                    
                'totaldevice' => $total_device,
                'falutdevice' => $falut_device,
                'totalduration'=> $total_duraion,
                'waterrank' => $waterrank,
              ))
              ->execute();
           
        //  _create_fire_statics_task($type, $term->tid);

          
        }
        
        // 添加行政区域的统计数据
       $vac_modes = taxonomy_vocabulary_machine_name_load('district');
       
       $terms = taxonomy_get_tree($vac_modes->vid);
       foreach($terms as $term){
           if($term->parents[0] == 0){ //城市级别 ，比如枣庄，济南
               $type = 'city';
           }else{
               $type = 'district';
               
           }
           $query = db_merge('fire_statics')
              ->key(array(
                'nid' => $term->tid,
                'type' => $type,
                'year' => $year,
                'month' => $month,  
              ))
              ->fields(array(
                'year'=>$year,
                'month'=>$month,  
                'totalmins' => $total_minutes,
                'inspectrate' => 0,
                'ctrlroomoff' => 0,
                'ctrlroom_offtime' => 0,  
                'firelaneoccp' => 0,
                'firelane_occptime' => 0,
                'hydrant_waterpress' => 0,
                'sprinkler_waterpress' => 0,
                'box_waterlevel' => 0,
                'pool_waterlevel' => 0,
                'safeindex' => 0,
                
              ))
              ->execute();
           //水系统排名数据
           $total_duraion = 0; 
           $waterrank = 0;
           $total_device = 0;
           $falut_device = 0;
           
           $query = db_merge('fire_statics_water')
              ->key(array(
                'nid' => $term->tid,
                'type' => $type,
                'year' => $year,
                'month' => $month,  
                'day'=>$day,                                      
              ))
              ->fields(array(
                'year'=>$year,
                'month'=>$month,  
                'day'=>$day,                    
                'totaldevice' => $total_device,
                'falutdevice' => $falut_device,
                'totalduration'=> $total_duraion,
                'waterrank' => $waterrank,
              ))
              ->execute();
                      
   //    _create_fire_statics_task($type, $term->tid);
        
       }
       drupal_set_message('统计数据初始化成功');
   
}