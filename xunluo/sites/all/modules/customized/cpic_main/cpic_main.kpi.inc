<?php


function _fire_main_set_default_chart_data(){
    
    $xdata = array();
    
    $now = time();
    $temp = date("Y-m",$now);

    $i = 0; 
    while ($i<12){
        $xdata[] = $temp;
        $temp = date("Y-m",strtotime("$temp -1month"));
        $ydata[]=0;
        $i ++;
    }
    
    return array(
        'x'=>$xdata,
        'y'=>$ydata
    );
}

// menu callback 
function fire_main_leading_kpi(){


    return 'kpi';
}
function cpic_main_bids(){
    
	return 'bids';
}

function cpic_main_online_chat(){
        return 'online chat';
}

//menu callback 
function fire_main_kpi_analyse(){

    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
   
    $output .= theme('fire_kpi_data', array('node' => $desks, 'dev' => $echart_js_path));
    print $output;
}




function fire_main_org_kpi_data($org_nid){

    $output = '';
    $org_node = node_load($org_nid);
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
   
    $output .= theme('fire_kpi_data', array('node' => $org_node, 'dev' => $echart_js_path));
    print $output;
}

function fire_main_ajax_get_data($type, $org_nid){
    $now = time();
    $date = getdate($now);
    $start = (isset($_POST['start']) && $_POST['start'] !='') ? strtotime($_POST['start']) : mktime(0,0,0,1,1,$date['year']);
    $end = (isset($_POST['end']) && $_POST['end'] !='') ? strtotime($_POST['end']) : mktime(0,0,0,12,31,$date['year']); //本年年底
   
    
    switch($type){
        case 'inspect':
         $data = _fire_main_kpi_retrieve_inspection_data($org_nid, $start, $end);

        break;
        case 'controlroom':
         $data = _fire_main_kpi_retrieve_controlroom_data($org_nid, $start, $end);

        break;
         case 'firelane':
         $data = _fire_main_kpi_retrieve_firelane_data($org_nid, $start, $end);
        case 'hydrant':
         $data = _fire_main_kpi_retrieve_hydrant_data($org_nid, $start, $end);            
            break;
        case 'sprinkler':
         $data = _fire_main_kpi_retrieve_sprinkler_data($org_nid, $start, $end);            
            break;
        case 'box':
         $data = _fire_main_kpi_retrieve_box_data($org_nid, $start, $end);            
            break;
        case 'pool':
         $data = _fire_main_kpi_retrieve_pool_data($org_nid, $start, $end);            
            break;                                    
        break;
    
        
    }
    drupal_json_output($data);

}


/* 计算各个数据
 * 
 */

function _fire_main_kpi_retrieve_inspection_data($org_nid, $start, $end,$org_type='corp') {
    $datas = array();

    $datas['created'][] = date("Y-m", $start);

    $datas['p1'][] = db_select("fire_statics","s")
        ->fields("s", array("inspectrate"))
        ->condition("nid",$org_nid)
        ->condition("year",date("Y",$start))
        ->condition("month",date("m",$start))
        ->condition("type",$org_type)
        ->execute()->fetchField();

    while (($start = strtotime('+1 month', $start)) <= $end) {

        $datas['created'][] = date("Y-m", $start);

        $datas['p1'][] = db_select("fire_statics","s")
            ->fields("s", array("inspectrate"))
            ->condition("nid",$org_nid)
            ->condition("year",date("Y",$start))
            ->condition("month",date("m",$start))
            ->condition("type",$org_type)
          
            ->execute()->fetchField();
    }

    return $datas;
}

function _fire_main_kpi_retrieve_controlroom_data($org_nid, $start, $end,$org_type='corp') {
    $datas = array();

    $datas['created'][] = date("Y-m", $start);

    $datas['p1'][] = db_select("fire_statics","s")
        ->fields("s", array("ctrlroomoff"))
        ->condition("nid",$org_nid)
        ->condition("year",date("Y",$start))
        ->condition("month",date("m",$start))
        ->condition("type",$org_type)
        ->execute()->fetchField();

    while (($start = strtotime('+1 month', $start)) <= $end) {
        
        $datas['created'][] = date("Y-m", $start);

        $datas['p1'][] = db_select("fire_statics","s")
            ->fields("s", array("ctrlroomoff"))
            ->condition("nid",$org_nid)
            ->condition("year",date("Y",$start))
            ->condition("month",date("m",$start))
            ->condition("type",$org_type)
            ->execute()->fetchField();
    }

    return $datas;
}

function _fire_main_kpi_retrieve_firelane_data($org_nid, $start, $end, $org_type='corp') {
    $datas = array();

    $datas['created'][] = date("Y-m", $start);

    $datas['p1'][] = db_select("fire_statics","s")
        ->fields("s", array("firelaneoccp"))
        ->condition("nid",$org_nid)
        ->condition("year",date("Y",$start))
        ->condition("month",date("m",$start))
        ->condition("type",$org_type)
         ->execute()->fetchField();

    while (($start = strtotime('+1 month', $start)) <= $end) {
        
        $datas['created'][] = date("Y-m", $start);

        $datas['p1'][] = db_select("fire_statics","s")
            ->fields("s", array("firelaneoccp"))
            ->condition("nid",$org_nid)
            ->condition("year",date("Y",$start))
            ->condition("month",date("m",$start))
            ->condition("type",$org_type)
            ->execute()->fetchField();
    }

    return $datas;
}


function fire_main_kpi_controlroom($org_nid){
    
    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $org_node = node_load($org_nid); 

    $query = db_select("fire_statics","s");
    $query->fields("s", array("month","ctrlroomoff"));
    $query->condition("nid",$org_nid);
    $query->condition("year",date("Y",time()));

    $results = $query->execute()->fetchAllKeyed();

    $xdata =array();
    $ydata = array();
    foreach ($results as $k => $v) {
        $xdata[] = date("Y",time())."年".$k."月";
        $ydata[] = $v;
    }
    if(empty($xdata)){
        $xy = _fire_main_set_default_chart_data();
        $xdata = $xy['x'];
        $ydata = $xy['y'];
        
    }
    $output .= theme('fire_kpi_controlroom', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata' => drupal_json_encode($xdata), 
        'ydata' => drupal_json_encode($ydata)
        
    ));
    print $output;

}


function fire_main_kpi_firelane($org_nid){
    

    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $org_node = node_load($org_nid); 

    $query = db_select("fire_statics","s");
    $query->fields("s", array("month","firelaneoccp"));
    $query->condition("nid",$org_nid);
    $query->condition("year",date("Y",time()));

    $results = $query->execute()->fetchAllKeyed();

    $xdata =array();
    $ydata = array();
    foreach ($results as $k => $v) {
        $xdata[] = date("Y",time())."年".$k."月";
        $ydata[] = $v;
    }
    if(empty($xdata)){
        $xy = _fire_main_set_default_chart_data();
        $xdata = $xy['x'];
        $ydata = $xy['y'];
        
    }
    $output .= theme('fire_kpi_firelane', array('node' => $org_node, 'dev' => $echart_js_path, 
        'xdata' => drupal_json_encode($xdata), 
        'ydata' => drupal_json_encode($ydata)
          ));
    print $output;
}

function fire_main_kpi_hydrant_waterpress($org_nid){
    

    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $org_node = node_load($org_nid); 

    $query = db_select("fire_statics","s");
    $query->fields("s", array("totalmins","hydrant_waterpress"));
    $query->condition("nid",$org_nid);
    $query->condition("year",date("Y",time()));

    $results = $query->execute()->fetchAll();

    $xdata = 0;
    $ydata = 0;
      
    foreach ($results as $result) {
        $xdata += $result->totalmins-$result->hydrant_waterpress;
        $ydata += $result->hydrant_waterpress;
    }  
    
    if($xdata == 0){ // 如果没有数值，默认为正常。
       $ydata = 100;
    }
   
    $output .= theme('fire_kpi_hydrant_waterpress', array('node' => $org_node, 'dev' => $echart_js_path, 
        'xdata' => drupal_json_encode($xdata), 
        'ydata' => drupal_json_encode($ydata)
                   
            ));
    print $output;
}

function fire_main_kpi_sprinkler_waterpress($org_nid){
    
    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
       $org_node = node_load($org_nid); 

    $query = db_select("fire_statics","s");
    $query->fields("s", array("totalmins","sprinkler_waterpress"));
    $query->condition("nid",$org_nid);
    $query->condition("year",date("Y",time()));

    $results = $query->execute()->fetchAllKeyed();

    $xdata = 0;
    $ydata = 0;    
    foreach ($results as $result) {
        $xdata += $result->totalmins-$result->sprinkler_waterpress;
        $ydata += $result->sprinkler_waterpress;
    }  
    if($xdata ==0){ // 如果没有数值，默认为正常。
       $ydata = 100;
    }
    $output .= theme('fire_kpi_sprinkler_waterpress', array('node' => $org_node, 'dev' => $echart_js_path, 'xdata' => $xdata, 'ydata' => $ydata));
    print $output;
}

function fire_main_kpi_box_waterlevel($org_nid){
    
    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'. $module_path.'/js/echarts/';
    $org_node = node_load($org_nid); 

    $query = db_select("fire_statics","s");
    $query->fields("s", array("totalmins","box_waterlevel"));
    $query->condition("nid",$org_nid);
    $query->condition("year",date("Y",time()));

    $results = $query->execute()->fetchAllKeyed();

    $xdata = 0;
    $ydata = 0;    
    foreach ($results as $result) {
        $xdata += $result->totalmins-$result->box_waterlevel;
        $ydata += $result->box_waterlevel;
    }
    if($xdata == 0){ // 如果没有数值，默认为正常。
       $ydata = 100;
    }
    $output .= theme('fire_kpi_box_waterlevel', array('node' => $org_node, 'dev' => $echart_js_path, 'xdata' => $xdata, 'ydata' => $ydata));
    print $output;
}
function fire_main_kpi_pool_waterlevel($org_nid){
    
    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $org_node = node_load($org_nid); 

    $query = db_select("fire_statics","s");
    $query->fields("s", array("totalmins","pool_waterlevel"));
    $query->condition("nid",$org_nid);
    $query->condition("year",date("Y",time()));

    $results = $query->execute()->fetchAllKeyed();

    $xdata = 0;
    $ydata = 0;    
    foreach ($results as $result) {
        $xdata += $result->totalmins-$result->pool_waterlevel;
        $ydata += $result->pool_waterlevel;
    }
    if($xdata == 0){ // 如果没有数值，默认为正常。
       $ydata = 100;
    }
    $output .= theme('fire_kpi_pool_waterlevel', array('node' => $org_node, 'dev' => $echart_js_path, 'xdata' => $xdata, 'ydata' => $ydata));
    print $output;
}
function fire_main_kpi_safeindex($org_nid){
    
    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = $module_path.'/js/echarts/';
     $org_node = node_load($org_nid); 
  
    $output .= theme('fire_kpi_safeindex', array('node' => $org_node, 'dev' => $echart_js_path));
    print $output;
}




function fire_main_kpi_compare(){
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $output .= theme('fire_kpi_compare', array('node' => $desks, 'dev' => $echart_js_path));
    return $output;
}


//数据对比时候获取各个比较的数据 

function fire_main_ajax_get_compared_data($type, $org_type, $nids){
    $now = time();
    $date = getdate($now);
    $start = (isset($_POST['start']) && $_POST['start'] !='') ? strtotime($_POST['start']) : mktime(0,0,0,1,1,$date['year']);
    $end = (isset($_POST['end']) && $_POST['end'] !='') ? strtotime($_POST['end']) : mktime(0,0,0,12,31,$date['year']); //本年年底
    $nids = explode('-', $nids);
    $created = array();
    $series = array();
    $titles = array();

    switch($type){
        case 'inspect':
                foreach($nids as $org_nid){
                    if($org_type == 'district'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_inspection_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'data'=> $data['p1'],
                   );

            
            }
            
        break;
        case 'controlroom':
            foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_controlroom_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'data'=> $data['p1'],
                   );

            
            }
        break;
         case 'firelane':
             foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }
                    $data = _fire_main_kpi_retrieve_firelane_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'data'=> $data['p1'],
                   );

            
            }
            break;
        case 'hydrant':
            foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_hydrant_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'lenend'=>$titles,
                       'data'=> $data['p1'],
                   );

            
            }
            
            break;
        case 'sprinkler':
             foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_hydrant_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'lenend'=>$titles,
                       'data'=> $data['p1'],
                   );

            
            }
           
            break;
        case 'box':
             foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_hydrant_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'lenend'=>$titles,
                       'data'=> $data['p1'],
                   );

            
            }
           
            break;
        case 'pool':
             foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_hydrant_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'lenend'=>$titles,
                       'data'=> $data['p1'],
                   );

            
            }
           
            break;  
        case 'safeindex':
             foreach($nids as $org_nid){
                    if($org_type == 'district' || $org_type == 'btype'){
                        $term = taxonomy_term_load($org_nid);
                        $name = $term->name;
                    }
                    else{
                        $name = node_load($org_nid)->title;
                    }                    
                    $data = _fire_main_kpi_retrieve_hydrant_data($org_nid, $start, $end, $org_type);
                    $titles[]=$name;
                    $created = $data['created'];
                    $series[]=array(
                       'name'=>$name,
                       'type'=>'line',
                       'lenend'=>$titles,
                       'data'=> $data['p1'],
                   );

            
            }
           
            break;                                    
            
    }
    drupal_json_output(array(
        'created'=>$created,
        'subtitle'=> implode('Vs.', $titles),
        'series'=> $series,
    ));

}




function fire_main_kpi_compare_inspect($org_type, $org_nids){
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $ydataValue = array();
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    
        
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_inspect', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'series'=>  drupal_json_encode($series),
            ));
    print $output;

}


function fire_main_kpi_compare_controlroom($org_type, $org_nids){
    
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
   
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $ydataValue = array();
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_controlroom', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>drupal_json_encode($ydata),
        'series'=>  drupal_json_encode($series),
            ));
    print $output;

}


function fire_main_kpi_compare_firelane($org_type,$org_nids){
    
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $ydataValue = array();
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_firelane', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'series'=>  drupal_json_encode($series),
            ));
    print $output;
}

function fire_main_kpi_compare_hydrant_waterpress($org_type,$org_nids){
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_hydrant_waterpress', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'legend'=>  drupal_json_encode($title_array),
        'series'=>  drupal_json_encode($series),
            ));
    
    print $output;
}

function fire_main_kpi_compare_sprinkler_waterpress($org_type,$org_nids){
    
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_sprinkler_waterpress', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'legend'=>  drupal_json_encode($title_array),
        'series'=>  drupal_json_encode($series),
            ));
    
    print $output;
}

function fire_main_kpi_compare_box_waterlevel($org_type,$org_nids){
    
   
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_box_waterlevel', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'legend'=>  drupal_json_encode($title_array),
        'series'=>  drupal_json_encode($series),
            ));
    
    print $output;
}
function fire_main_kpi_compare_pool_waterlevel($org_type,$org_nids){
    
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_pool_waterlevel', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'legend'=>  drupal_json_encode($title_array),
        'series'=>  drupal_json_encode($series),
            ));
    
    print $output;
}
function fire_main_kpi_compare_safeindex($org_type,$org_nids){
    
    $output = '';
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $ydata = array();
    $org_node = new stdClass();
    $org_node->title ='';
    $title_array =array();
    $xy = _fire_main_set_default_chart_data();
    $xdata = $xy['x'];
    $ydata = $xy['y'];
    
    if($org_type == 'district'){
        $tids = explode('-',$org_nids);
        foreach($tids as $tid){
            $term = taxonomy_term_load($tid);
            $title_array[]= $term->name;
           $org_node->nid = $org_nids;
           
           $series[]=array(
               'name'=>$term->name,
               'type'=>'line',
               'data'=> $ydata,
           );

                   
        }
    }
    
    $org_node->title=implode('Vs ',$title_array);
    $output .= theme('fire_kpi_compare_safeindex', array('node' => $org_node, 'dev' => $echart_js_path,
        'xdata'=>  drupal_json_encode($xdata),
        'ydata'=>$ydata,
        'legend'=>  drupal_json_encode($title_array),
        'series'=>  drupal_json_encode($series),
            ));
    
    print $output;
}



//数据统计
/*/*menu callback
 * 
 *
 *  @param, $org_type, 类型， 比如是区域
 *  @param, $id, 一般是企业类型的tID,或者企业的NID，
 */
function fire_main_kpi_static($org_type, $id){
    
    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    $output .= theme('fire_kpi_static', array('node' => $desks, 'dev' => $echart_js_path));
    print $output;
    
}

function fire_main_kpi_ajax_get_static_data($org_type, $id){
    
     
    $now = time();
    $date = getdate($now);
    $start = (isset($_POST['start']) && $_POST['start'] !='') ? strtotime($_POST['start']) : mktime(0,0,0,1,1,$date['year']);
    $end = (isset($_POST['end']) && $_POST['end'] !='') ? strtotime($_POST['end']) : mktime(0,0,0,12,31,$date['year']); //本年年底
    $id = (isset($_POST['id']) && $_POST['id'] !='') ? $_POST['id'] : 0;
    $item = (isset($_POST['item']) && $_POST['item'] !='') ? intval($_POST['item']) : 1;
    $level = (isset($_POST['level']) && $_POST['level'] !='') ? intval($_POST['level']) : 1;

    $pageNumber = isset($_POST['page']) ? $_POST['page'] : 1;
    $pageSize = isset($_POST['rows']) ? $_POST['rows'] : 20;
    $offset = $pageSize * ($pageNumber - 1);

    
    
    
    $datas = array();
    $data = array();
    $query = db_select('fire_statics','s');
    if($org_type == 'district'){ //统计某个区下的数据
        $query->join('field_data_field_belong_district','d','d.entity_id=s.nid');
        $query->condition('d.field_belong_district_tid', $id);    
    }
    if($org_type == 'btype'){ //统计某个行业类型
        $query->join('field_data_field_business_type','b','b.entity_id = s.nid');
        $query->condition('b.field_business_type_tid', $id);    
    }
    
    if($item == 1 && $level ==2){ //巡检旅达到80%以上
       $query->condition('s.inspectrate', '80','>');    
    }
    if($item == 1 && $level ==3){ //巡检旅未达到80%
        $query->condition('s.inspectrate', '80','<');    

    }
    if($item == 2 && $level ==2){ //脱岗时间0小时
       $query->condition('s.ctrlroom_offtime', '0');    
    }
    
    if($item == 2 && $level ==3){ //脱岗时间大于0～5小时
       $query->condition('s.ctrlroom_offtime', '300','<');    
       $query->condition('s.ctrlroom_offtime', '0','>');    

    }
    if($item == 2 && $level ==4){ //脱岗时间大于5小时
        $query->condition('s.ctrlroom_offtime', '300','>');    

    }
    
    if($item == 3 && $level ==2){ //占用时间0小时
       $query->condition('s.ctrlroom_offtime', '0');    
    }
    
    if($item == 3 && $level ==3){ //占用时间大于0～5小时
       $query->condition('s.ctrlroom_offtime', '300','<');    
       $query->condition('s.ctrlroom_offtime', '0','>');    

    }
    if($item == 3 && $level ==4){ //占用时间大于5小时
        $query->condition('s.ctrlroom_offtime', '300','>');    

    }
    
    if($item == 4 && $level ==2){ //消火栓系统水压状态 达标
       $query->condition('s.hydrant_waterpress', '300','<');    

    }
    if($item == 4 && $level ==3){ //消火栓系统水压状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.hydrant_waterpress', '300','>');    
 
    }
    if($item == 5 && $level ==2){ //喷淋系统水压状态 达标
       $query->condition('s.sprinkler_waterpress', '300','<');    

    }
    if($item == 5 && $level ==3){ //喷淋系统水压状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.sprinkler_waterpress', '300','>');    
 
    }
    if($item == 6 && $level ==2){ //消防水箱水位状态 达标
       $query->condition('s.box_waterlevel', '300','<');    

    }
    if($item == 6 && $level ==3){ //消防水箱水位状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.box_waterlevel', '300','>');    
 
    }
    if($item == 7 && $level ==2){ //消防水池水位状态 达标
       $query->condition('s.pool_waterlevel', '300','<');    

    }
    if($item == 7 && $level ==3){ //消防水池水位状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.pool_waterlevel', '300','>');    
 
    }
     if($item == 8 && $level ==2){ //消防安全评估 达标
       $query->condition('s.safeindex', '300','<');    

    }
    if($item == 8 && $level ==3){ //消防安全评估 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.safeindex', '300','>');    
 
    }
    
  //  $query->condition('s.type', 'corp');    
    $query->fields('s');
    $query->execute()->rowCount();
    $datas["total"] = $query->execute()->rowCount();

    $query = db_select('fire_statics','s');
    if($org_type == 'district'){ //统计某个区下的数据
        $query->join('field_data_field_belong_district','d','d.entity_id=s.nid');
        $query->condition('d.field_belong_district_tid', $id);    
    }
     if($org_type == 'btype'){ //统计某个行业类型
        $query->join('field_data_field_business_type','b','b.entity_id = s.nid');
        $query->condition('b.field_business_type_tid', $id);    
    }
   
    if($item == 1 && $level ==2){ //巡检旅达到80%以上
       $query->condition('s.inspectrate', '80','>');    
    }
    if($item == 1 && $level ==3){ //巡检旅未达到80%
        $query->condition('s.inspectrate', '80','<');    

    }
    if($item == 2 && $level ==2){ //脱岗时间0小时
       $query->condition('s.ctrlroom_offtime', '0');    
    }
    
    if($item == 2 && $level ==3){ //脱岗时间大于0～5小时
       $query->condition('s.ctrlroom_offtime', '300','<');    
       $query->condition('s.ctrlroom_offtime', '0','>');    

    }
    if($item == 2 && $level ==4){ //脱岗时间大于5小时
        $query->condition('s.ctrlroom_offtime', '300','>');    

    }
    
    if($item == 3 && $level ==2){ //占用时间0小时
       $query->condition('s.ctrlroom_offtime', '0');    
    }
    
    if($item == 3 && $level ==3){ //占用时间大于0～5小时
       $query->condition('s.ctrlroom_offtime', '300','<');    
       $query->condition('s.ctrlroom_offtime', '0','>');    

    }
    if($item == 3 && $level ==4){ //占用时间大于5小时
        $query->condition('s.ctrlroom_offtime', '300','>');    

    }
     if($item == 4 && $level ==2){ //消火栓系统水压状态 达标
       $query->condition('s.hydrant_waterpress', '300','<');    

    }
    if($item == 4 && $level ==3){ //消火栓系统水压状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.hydrant_waterpress', '300','>');    
 
    }
    if($item == 5 && $level ==2){ //喷淋系统水压状态 达标
       $query->condition('s.sprinkler_waterpress', '300','<');    

    }
    if($item == 5 && $level ==3){ //喷淋系统水压状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.sprinkler_waterpress', '300','>');    
 
    }
    if($item == 6 && $level ==2){ //消防水箱水位状态 达标
       $query->condition('s.box_waterlevel', '300','<');    

    }
    if($item == 6 && $level ==3){ //消防水箱水位状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.box_waterlevel', '300','>');    
 
    }
    if($item == 7 && $level ==2){ //消防水池水位状态 达标
       $query->condition('s.pool_waterlevel', '300','<');    

    }
    if($item == 7 && $level ==3){ //消防水池水位状态 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.pool_waterlevel', '300','>');    
 
    }
     if($item == 8 && $level ==2){ //消防安全评估 达标
       $query->condition('s.safeindex', '300','<');    

    }
    if($item == 8 && $level ==3){ //消防安全评估 未达标 问题， 怎么算达标？ 大于5小时的
       $query->condition('s.safeindex', '300','>');    
 
    }
    
   
    
    
    $query->condition('s.type', 'corp');    
    $query->fields('s');
    $query->orderBy('s.nid','DESC');
    
    if ($offset && $limit) {
        $query = $query->range($offset, $limit);
    }
    if (!$offset && $limit) {
        $query = $query->range(0, $limit);
    }
    $results = $query->execute();
    foreach ($results as $row) {
        $corp_node = node_load($row->nid);
        switch($item){
            case 1: // 巡检率
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'rate' => $row->inspectrate,
                );
                break;
            case 2: //控制值班室脱岗时间
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'ctrlroom_offtime' => $row->ctrlroom_offtime,
                );
                break;
             case 3: //消防车道占用时间
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'firelane_occptime' => $row->firelane_occptime,
                );
                break;
             case 4: //消火栓系统水压状态
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'hydrant_waterpress' => $row->hydrant_waterpress,
                );
                break;
             case 5: //喷淋系统水压状态
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'sprinkler_waterpress' => $row->sprinkler_waterpress,
                );
                break;
             case 6: //消防水箱水位状态
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'box_waterlevel' => $row->box_waterlevel,
                );
                break;
             case 7: //消防水池水位状态
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'pool_waterlevel' => $row->pool_waterlevel,
                );
                break;
              case 8: //消防安全评估
                $data[] = array(
                    'id'=>$row->nid,
                    'name' => l($corp_node->title,'node/'.$row->nid),
                    'year' => $row->year,
                    'month' => $row->month,
                    'safeindex' => $row->safeindex,
                );
                break;                    
        }
        
    }


    $datas["rows"] = $data;
    drupal_json_output($data);

    
}

//综合排名不分
//menu callback 
function fire_main_kpi_rank(){

    $output = '';
     
    $module_path = drupal_get_path('module', 'fire_main');   
    $output .= theme('fire_kpi_rank', array('node' => $desks, 'dev' => $echart_js_path));
    return $output;
}

/*menu callback
 * 
 */
function fire_main_kpi_rank_page($org_list){
     
    $module_path = drupal_get_path('module', 'fire_main');
    $output = '';
    $arr_org_list = explode('-', $org_list);
    $type = $arr_org_list[0];

    $nowDate = date('Y-m-d', time());
    $stime = empty($_GET['s']) ? $nowDate : $_GET['s'];
    $etime = empty($_GET['e']) ? $nowDate : $_GET['e'];

    if($type == 'district')
    {
        // 区页面 - 显示企业列表
        $p_dis = 'city-'.$arr_org_list[1].'-'.$arr_org_list[2];
        $output .= theme('fire_kpi_rank_area', array('p_dis' => $p_dis, 'org_list'=>$org_list));
        print $output;
    }
    elseif($type == 'corp')
    {
        // 公司页面
        $cid = $arr_org_list[1];
        $f = $arr_org_list[2];
        
        $info = kpi_rank_show_corp_info($cid, $f, $stime, $etime);
        
        $output .= theme('fire_kpi_rank_area_corp', $info);
        print $output;
    }
    else
    {
        // 显示城市列表
        $output .= theme('fire_kpi_rank', array('org_list'=>$org_list));
        print $output;
    }
}

// 获取排名数据 - 城市列表
function get_ajax_kpi_rank_data()
{

    $queryIndex = empty($_GET['queryIndex']) ? '1' : $_GET['queryIndex'];
    $nowDate = date('Y-m-d', time());
    $startDate = empty($_GET['startDate']) ? $nowDate : $_GET['startDate'];
    $endDate = empty($_GET['endDate']) ? $nowDate : $_GET['endDate'];

    $org_list = $_GET['org_list'];
    $dislistinfo = get_district_list_info($org_list);
    $dis_list = $dislistinfo['dis_list'];
    $dis_uri = $dislistinfo['dis_uri'];
    
    $i = 0;
    $data = array();

    if($queryIndex == 1)
    {
        $arr_date = get_arr_dur_byday($startDate, $endDate);
        $arrwaterrank = get_water_rank($arr_date, $dis_list, 'district');
        $arr_water = $arrwaterrank['arr_water'];
        $ci = $arrwaterrank['ci'];
        
        foreach ($arr_water as $k => $w) {
            $listprice = $w['listprice']/$ci;
            $unitcost = $w['unitcost']/$ci;
            $attr1 = $w['attr1']/$ci;
            $i++;
            $data[] = array(
                'itemid' => $i,
                'productid' => '<a href="javascript:void(0)" onclick="goAreaPage(\''.$dis_uri[$k].'\');">'.$dis_list[$k].'</a>',
                'listprice' => $listprice,
                'unitcost' => $unitcost,
                'attr1' => $attr1,
                'status' => $listprice-$attr1.'/'.$listprice,
                );
        }
    }

    if($queryIndex == 2)
    {
        $arr_date = get_arr_dur_bymonth($startDate, $endDate);
        $arr_qrcode = get_qrcode_rank($arr_date, $dis_list, 'district');
        
        $arr_QRCode = $arr_qrcode['arr_QRCode'];
        $ci = $arr_qrcode['ci'];
        
        foreach ($arr_QRCode as $k => $w) {
            $total = $w['total']/$ci;
            $inspecteddevice = $w['inspecteddevice']/$ci;
            $falutrate = $w['falutrate']/$ci;
            $inspectrate = $w['inspectrate']/$ci;
            $i++;
            $data[] = array(
                'itemid' => $i,
                'productid' => '<a href="javascript:void(0)" onclick="goAreaPage(\''.$dis_uri[$k].'\');">'.$dis_list[$k].'</a>', // $dis_uri[$k]
                'total' => $total,
                'currmonnum' => $inspecteddevice,
                'status' => 1-$falutrate,
                );
        }
    }

    if($queryIndex == 3)
    {
        $result = db_select('fire_statics', 'fs')
        ->condition('nid', array_keys($dis_list), 'IN')
        ->condition('type', 'district','=')
        ->orderBy('waterrank', 'ASC')
        ->fields('fs')
        ->execute();

        foreach ($result as $row) {
            $alarmnum = rand(1, 30);
            $i++;
            $data[] = array(
                'itemid' => $i,
                'productid' => '<a href="javascript:void(0)" onclick="goAreaPage(\''.$dis_uri[$row->nid].'\');">'.$dis_list[$row->nid].'</a>', // $dis_uri[$k]
                'alarmnum' => $alarmnum,
                );
        }
    }
    

    $datas['total'] = count($data);
    $datas['rows'] = $data;
    echo drupal_json_encode($datas);
}

function cmp($a, $b){
   return $a['waterrank'] - $b['waterrank'];
}
function cmp2($a, $b){
   return $a['inspectrate'] - $b['inspectrate'];
}

// 获取排名数据 区界面
function get_ajax_kpi_rank_data_qu()
{
    $queryIndex = empty($_GET['queryIndex']) ? '1' : $_GET['queryIndex'];
    $nowDate = date('Y-m-d', time());
    $startDate = empty($_GET['startDate']) ? $nowDate : $_GET['startDate'];
    $endDate = empty($_GET['endDate']) ? $nowDate : $_GET['endDate'];

    $org_list = $_GET['org_list'];
    $dis_list = get_corp_list_info($org_list);

    $i = 0;
    $data = array();

    if($queryIndex == 1)
    {
        $arr_date = get_arr_dur_byday($startDate, $endDate);
        $arrwaterrank = get_water_rank($arr_date, $dis_list, 'corp');
        $arr_water = $arrwaterrank['arr_water'];
        $ci = $arrwaterrank['ci'];

        foreach ($arr_water as $k => $w) {
            $listprice = $w['listprice']/$ci;
            $unitcost = $w['unitcost']/$ci;
            $attr1 = $w['attr1']/$ci;
            $i++;
            $data[] = array(
                'itemid' => $i,
                'productid' => '<a href="javascript:void(0)" onclick="goCorpPage(\'corp-'.$k.'-'.$queryIndex.'\')">'.$dis_list[$k].'</a>',
                'listprice' => $listprice,
                'unitcost' => $unitcost,
                'attr1' => $attr1,
                'status' => $listprice-$attr1.'/'.$listprice,
                );
        }
    }

    if($queryIndex == 2)
    {
        $arr_date = get_arr_dur_bymonth($startDate, $endDate);
        $arr_qrcode = get_qrcode_rank($arr_date, $dis_list, 'corp');
        
        $arr_QRCode = $arr_qrcode['arr_QRCode'];
        $ci = $arr_qrcode['ci'];
        
        foreach ($arr_QRCode as $k => $w) {
            $total = $w['total']/$ci;
            $inspecteddevice = $w['inspecteddevice']/$ci;
            $falutrate = $w['falutrate']/$ci;
            $inspectrate = $w['inspectrate']/$ci;
            $i++;
            $data[] = array(
                'itemid' => $i,
                'productid' => '<a href="javascript:void(0)" onclick="goCorpPage(\'corp-'.$k.'-'.$queryIndex.'\')">'.$dis_list[$k].'</a>',
                'total' => $total,
                'currmonnum' => $inspecteddevice,
                'status' => 1-$falutrate,
                );
        }
    }

    if($queryIndex == 3)
    {
        foreach ($results as $row) {
            $dis_list[$row->nid] = $row->title;
        }

        $res = db_select('fire_statics', 'fs')
        ->condition('nid', array_keys($dis_list), 'IN')
        ->condition('type', 'corp','=')
        ->orderBy('waterrank', 'ASC')
        ->fields('fs')
        ->execute();

        foreach ($res as $row1) {
            $alarmnum = rand(1, 30);
            $i++;
            $data[] = array(
                'itemid' => $i,
                'productid' => '<a href="javascript:void(0)" onclick="goCorpPage(\'corp-'.$row1->nid.'-'.$queryIndex.'\')">'.$dis_list[$row1->nid].'</a>',
                'alarmnum' => $alarmnum,
                );
        }
    }

    $datas['total'] = count($data);
    $datas['rows'] = $data;
    echo drupal_json_encode($datas);
}

// 企业信息页面
function kpi_rank_show_corp_info($cid, $f, $stime, $etime)
{
    $com_node = node_load($cid);
    $corp_name = $com_node->title;  // 企业名称

    $dis_tid = $com_node->field_belong_district['und'][0]['tid'];
    $dis_tid_p = taxonomy_get_parents($dis_tid);
    foreach ($dis_tid_p as $k => $v) {
        $dis_tid_pid = $k;
    }
    $dis_tid_p_p = taxonomy_get_parents($dis_tid_pid);
    foreach ($dis_tid_p_p as $key => $val) {
        $dis_tid_p_pid = $key;
    }

    $dis_uri = 'district-'.$dis_tid_p_pid.'-'.$dis_tid_pid.'-'.$dis_tid;

    $info = array();
    if($f == 1)
    {
        $ref_val = '消火栓系统：0.1Mpa；喷淋系统0.05Mpa'; // 参考值

        $arr_date = get_arr_dur_byday($stime, $etime);
        $arrwaterrank = get_water_rank($arr_date, $cid, 'corp');
        $arr_water = $arrwaterrank['arr_water'];
        $ci = $arrwaterrank['ci'];

        foreach ($arr_water as $k => $w) {
            $dev_total = $w['listprice']/$ci;   // 设备总数
        }

        $waterinfo = get_water_info_bycid($cid, $stime, $etime);
 
        $info = array('dis_uri'=> $dis_uri, 'pagetype'=>$f, 'corp_name' => $corp_name, 'dev_total'=>$dev_total,'waterinfo'=>$waterinfo);
    }
    if($f == 2)
    {
        // 企业二维码信息
        $arr_date = get_arr_dur_bymonth($stime, $etime);
        $arr_qrcode = get_qrcode_rank($arr_date, $dis_list, 'corp');
        
        $arr_QRCode = $arr_qrcode['arr_QRCode'];
        $ci = $arr_qrcode['ci'];
        
        foreach ($arr_QRCode as $k => $w) {
            $dev_total = $w['total']/$ci;   // 设备总数
            $currmonnum = $w['inspecteddevice']/$ci;   // 本月巡检次数
            $percent = 1 - $w['falutrate']/$ci; // 合格率
        }
 
        $arr_inspection = array(
            array(
                'dev' => '设备1',
                'instime' => '2015-08-11',
                'isok' => '合格', 
                ),
            array(
                'dev' => '设备4',
                'instime' => '2015-08-11',
                'isok' => '合格', 
                ),
            array(
                'dev' => '设备2',
                'instime' => '2015-08-11',
                'isok' => '不合格', 
                ),
            array(
                'dev' => '设备6',
                'instime' => '2015-08-11',
                'isok' => '合格', 
                ),
            array(
                'dev' => '设备7',
                'instime' => '2015-08-11',
                'isok' => '合格', 
                ),
            );

        $inspection = '';
        foreach ($arr_inspection as $k => $v) {
            $inspection .= drupal_json_encode($v).',';
        }
        
        $info = array('dis_uri'=> $dis_uri, 'pagetype'=>$f, 'corp_name' => $corp_name, 'dev_total' => $dev_total, 'currmonnum' => $currmonnum, 'percent' => $percent, 'inspection' => $inspection);
    }
    if($f == 3)
    {
        $alarmnum = rand(1,5);
        $alarminfo = '';
        for ($i=1; $i <=$alarmnum ; $i++) {
            $data = array(
                'position' => '位置'.$i,
                'alarmtime' => date('Y-m-d H:i:s'),
                'alarmcause' => '占用',
                );
            $alarminfo .= drupal_json_encode($data).',';
        }
        
        $info = array('dis_uri'=> $dis_uri, 'pagetype'=>$f, 'corp_name' => $corp_name, 'alarmnum'=>$alarmnum, 'alarminfo' => $alarminfo);
    }
    
    return $info;
}

// 获取水系统信息
function get_water_info_bycid($org_nid, $stime, $etime)
{
    $waterpress = array();
    $org_devices = vpaas_asset_get_org_devices($org_nid);
    $sensors = array();
    $threshold = '参考值：';
    
    foreach($org_devices as $device){
        $devids[]=$device->field_asset_id['und'][0]['value'];   // 设备编码
        $props = vpaas_asset_get_device_sensors($device->nid);  // $device->nid 设备id

        foreach($props as $prop_id => $p){
            $sensors[$device->field_asset_id['und'][0]['value']][$p->channel_id]= $p->location; // [编码][类型]=>位置
            $cvalue = 0;
            $cvalue = vpaas_asset_get_device_specified_field_value($device->field_asset_id['und'][0]['value'],$prop_id);
            $cvalue = fire_water_calculate_formula($p->channel_id, $cvalue);

            switch($p->channel_id){
                case WATER_DEVICE_PLMD_CHANNEL:
                $limit =  variable_get('fire_water_plmd_press_bottom', '0.050');
                $threshold .= '&nbsp喷淋'.$limit.'Mpa';
                $unit = 'Mpa';
                break;

                case WATER_DEVICE_XHS_CHANNEL:
                $limit =  variable_get('fire_water_xhs_press_bottom', '0.10');
                $threshold .= '&nbsp消火栓'.$limit.'Mpa';
                $unit = 'Mpa';

                break;


                case WATER_DEVICE_TANK_CHANNEL:
                list($min,$max)= explode('-',$device->field_tank_volue['und'][0]['value']);
                $limit = $min;
                $threshold .= '&nbsp水箱水位（'.$min.'米-'.$max.'米)';
                $unit = '米';

                breank;
                case WATER_DEVICE_POOL_CHANNEL:
                list($min,$max)= explode('-',$device->field_max_height['und'][0]['value']);
                $limit = $min;
                $threshold .= '&nbsp水池水位（'.$min.'米-'.$max.'米）';
                $unit = '米';

                break;
            }
            
            $waterpress[$p->channel_id][] = array(
                'device_id'=> $device->field_asset_id['und'][0]['value'],
                'prop_id'=>$prop_id,
                'channel_id'=>$p->channel_id,
                'name'=> $device->title,
                'threshold'=> $limit,
                'unit'=> $unit,
                'value'=>$cvalue,
                'location'=> $p->location,
            );
        }
    }

    if($stime == $etime)
    {
        // 一天
        $start_time = strtotime($stime. ' 00:00:00');
        $end_time = strtotime($stime. ' 23:59:59');
    }
    else
    {
        $start_time = strtotime($stime. ' 00:00:00');
        $end_time = strtotime($etime. ' 23:59:59');
    }

    //获取alarm
    $alarms = array();
    if(!empty($devids)){
        $query =  db_select('water_alarm_info','wa');
        $query->condition('wa.devid', $devids, 'IN')
        ->condition('wa.starttime', array($start_time, $end_time), 'BETWEEN')
        ->orderBy('wa.starttime')
        ->fields('wa')
        ->range(0, 20);
        $results = $query->execute();

        foreach ($results as $row) {
            $alarms[$row->sid] = array(
                'name'=> $sensors[$row->devid][$row->type],
                'cvalue'=>$row->cvalue,
                'starttime'=>$row->starttime,
                'endtime'=>$row->endtime,
                'duration'=>round(($row->duration/60),2).'小时',

                );
            $alarmtime[$row->devid] += round(($row->duration/60),2);
        }
    }
    //var_export($alarmtime);
    $info = array(
        'threshold' => $threshold,
        'waterpress' => $waterpress,
        'alarmtime' => $alarmtime,
        );
    return $info;
}

// 根据日 获取间隔时间数据
function get_arr_dur_byday($sday, $eday)
{
    $dday = array();
    $sday = strtotime($sday);
    $eday = strtotime($eday);
    $fday = 0;
    $di = 0;
    
    while($fday < $eday)
    {
        $fday = $sday+$di*(24*60*60);
        $dday[] = date('Y-m-d', $fday);
        $di++;
    }
    
    return $dday;
}
// 根据月 获取间隔时间数据
function get_arr_dur_bymonth($sday, $eday)
{
    $arrstartDate = explode('-', $sday);
    $arrendDate = explode('-', $eday);
    $smonth = $arrstartDate[0].'-'.$arrstartDate[1];
    $emonth = $arrendDate[0].'-'.$arrendDate[1];

    $dmonth = array();
    $fmonth = '';
    $arr_ym = explode('-', $smonth);
    $y = $arr_ym[0];
    $m = $arr_ym[1];
    
    while($fmonth<$emonth)
    {
        
        if($m>12)
        {
            $m = 1;
            $y += 1;
        }
        if($m<10) $m = '0'.intval($m);
        $fmonth = $y.'-'.$m;
        $dmonth[] = $fmonth;
        $m ++;
    }
    
    return $dmonth; // 间隔的 年-月
}

// 根据id 获取区域列表信息
function get_district_list_info($org_list)
{
    $dis_list = array();
    $dis_uri = array();

    $arr_org_list = explode('-', $org_list);
    $type = $arr_org_list[0];
    $org_nid = $arr_org_list[1];

    if($type == 'province')
    {
        // 省级
        $s_dis = taxonomy_get_children($org_nid);
        foreach ($s_dis as $k => $v) {
            $q_dis = taxonomy_get_children($k);
            foreach ($q_dis as $key => $val) {
                $dis_list[$key] = $val->name;
                $dis_uri[$key] = 'district-'.$org_nid.'-'.$k.'-'.$key;
            }
        }
    }

    if($type == 'city')
    {
        // 市区级
        $dis_id = $arr_org_list[2];
        $q_dis = taxonomy_get_children($dis_id);
        $p_dis = taxonomy_get_parents($dis_id);
        foreach ($p_dis as $k => $v) {
            $p_disid = $k;
        }
        foreach ($q_dis as $key => $val) {
            $dis_list[$key] = $val->name;
            $dis_uri[$key] = 'district-'.$p_disid.'-'.$dis_id.'-'.$key;
        }
    }

    $data['dis_list'] = $dis_list;
    $data['dis_uri'] = $dis_uri;
    return $data;
}

// 根据 所属行政区域 获取 企业信息
function get_corp_list_info($org_list)
{
    $arr_org_list = explode('-', $org_list);
    $qid = $arr_org_list[3];
    $dis_list = array();

    $query = db_select('node', 'n');
    $query->join('field_data_field_belong_district','d','d.entity_id = n.nid');
    $query->condition('n.type','org');
    $query->condition('d.field_belong_district_tid',$qid);
    $query->fields('n',array('nid', 'title'));
    $results = $query->execute();

    foreach ($results as $row1) {
        $dis_list[$row1->nid] = $row1->title;
    }

    return $dis_list;
}

// 获取水系统排名
function get_water_rank($arr_date, $dis_list, $type)
{
    $arr_water = array();
    $ci = 0;
    foreach ($arr_date as $fdate) {
        $arr_fdate = explode('-', $fdate);
        $fyear = $arr_fdate[0];
        $fmonth = $arr_fdate[1];
        $fday = $arr_fdate[2];

        if(is_array($dis_list))
        {
            $result = db_select('fire_statics_water', 'fsw')
            ->condition('nid', array_keys($dis_list), 'IN')
            ->condition('type', $type,'=')
            ->condition('year', $fyear,'=')
            ->condition('month', $fmonth,'=')
            ->condition('day', $fday,'=')
            //->orderBy('waterrank', 'ASC')
            ->fields('fsw')
            ->execute();
        }
        else
        {
            $result = db_select('fire_statics_water', 'fsw')
            ->condition('nid', $dis_list, '=')
            ->condition('type', $type,'=')
            ->condition('year', $fyear,'=')
            ->condition('month', $fmonth,'=')
            ->condition('day', $fday,'=')
            //->orderBy('waterrank', 'ASC')
            ->fields('fsw')
            ->execute();
        }

        foreach ($result as $row) {
            if(!isset($arr_water[$row->nid]['listprice'])) $arr_water[$row->nid]['listprice'] = 0;
            if(!isset($arr_water[$row->nid]['unitcost'])) $arr_water[$row->nid]['unitcost'] = 0;
            if(!isset($arr_water[$row->nid]['attr1'])) $arr_water[$row->nid]['attr1'] = 0;
            if(!isset($arr_water[$row->nid]['waterrank'])) $arr_water[$row->nid]['waterrank'] = 0;
            $arr_water[$row->nid]['listprice'] = $arr_water[$row->nid]['listprice'] + $row->totaldevice;   // 检测点
            $arr_water[$row->nid]['unitcost'] = $arr_water[$row->nid]['unitcost'] + $row->totalduration;   // 报警时间
            $arr_water[$row->nid]['attr1'] = $arr_water[$row->nid]['attr1'] + $row->falutdevice;   // 故障点
            $arr_water[$row->nid]['waterrank'] = $arr_water[$row->nid]['waterrank'] + $row->waterrank;   // 水系统排名
        }

        $ci++ ;
    }

    uasort($arr_water, 'cmp');
    $data['arr_water'] = $arr_water;
    $data['ci'] = $ci;
    return $data;
}

// 获取二维码巡检排名
function get_qrcode_rank($arr_date, $dis_list, $type)
{
    $arr_QRCode = array();
    $ci = 0;
    foreach ($arr_date as $fdate) {
        $arr_fdate = explode('-', $fdate);
        $fyear = $arr_fdate[0];
        $fmonth = $arr_fdate[1];

        $result = db_select('fire_statics_inspect', 'fsi')
        ->condition('nid', array_keys($dis_list), 'IN')
        ->condition('type', $type,'=')
        ->condition('year', $fyear,'=')
        ->condition('month', $fmonth,'=')
        //->orderBy('inspectrate', 'ASC')
        ->fields('fsi')
        ->execute();

        foreach ($result as $row) {
            if(!isset($arr_QRCode[$row->nid]['total'])) $arr_QRCode[$row->nid]['total'] = 0;
            if(!isset($arr_QRCode[$row->nid]['inspecteddevice'])) $arr_QRCode[$row->nid]['inspecteddevice'] = 0;
            if(!isset($arr_QRCode[$row->nid]['falutrate'])) $arr_QRCode[$row->nid]['falutrate'] = 0;
            if(!isset($arr_QRCode[$row->nid]['inspectrate'])) $arr_QRCode[$row->nid]['inspectrate'] = 0;
            $arr_QRCode[$row->nid]['total'] += $row->totaldevice;   // 总数
            $arr_QRCode[$row->nid]['inspecteddevice'] += $row->inspecteddevice;   // 本月巡检数
            $arr_QRCode[$row->nid]['falutrate'] += $row->falutrate;   // 故障率
            $arr_QRCode[$row->nid]['inspectrate'] += $row->inspectrate;   // 巡检率
        }

        $ci++ ;
    }

    uasort($arr_QRCode, 'cmp2');
    $data['arr_QRCode'] = $arr_QRCode;
    $data['ci'] = $ci;
    return $data;
}
