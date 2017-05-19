<?php


//menu callback 

function fire_leading_front_page(){
    return '';
}

function fire_leading_homepage(){

	
  $output = '';
  global $user;
 /* $mapkey = '0xm1Xh9EUgfWOuA9pIfs0xWD'; // variable_get('baidu_map_key','0xm1Xh9EUgfWOuA9pIfs0xWD');

  drupal_add_js('http://api.map.baidu.com/api?v=2.0&ak=' . $mapkey, 'external');
  drupal_add_js(drupal_get_path('module', 'cpic_main') . '/js/fire_gis_mapapi.js');

  $output .='<div id="map-container" style="width:100%; height:600px" class="gis-map">这是地图显示的区域。。。</div>';
*/
  $module_path = drupal_get_path('module', 'cpic_main');
  $echart_js_path = '/'.$module_path.'/js/echarts/';
   $desks = array();
  $output .= theme('cpic_main_homepage', array('node' => $desks, 'dev' => $echart_js_path));
  return $output;

}

function fire_leading_homepage_corp_map(){

  $output = '';
  global $user;
  // $output .='<div>欢迎登陆管理界面！</div>';
  $mapkey = variable_get('baidu_map_key','');

  // drupal_add_js('http://api.map.baidu.com/api?v=2.0&ak=' . $mapkey, 'external');
  // drupal_add_js(drupal_get_path('module', 'cpic_main') . '/js/fire_gis_mapapi.js');

  // $output .='<div id="map-container" style="width:100%; height:600px" class="gis-map">这是地图显示的区域。。。</div>';
  // // $output .='<div id="realdlg" title="实时数据" style="width:850px;height:400px;padding:5px 10px"></div>';


  $output .= theme('cpic_main_org_homepage_bmap',array('node'=>null,'dev'=>$mapkey));
  echo $output;
}

/*menu callback
 * 
 */
function cpic_main_homepage_area_corp_map($itemid){
	$arr_itemid = explode('-', $itemid);
	$num_itemid = count($arr_itemid);
	$type = $arr_itemid[0];
	
	if($type == 'btype')
	{
		$lnglat = taxonomy_term_load($arr_itemid[3])->field_lnglat['und'][0]['value'];
	}
	elseif($type == 'province')
	{
		$itemid = '0';
		$lnglat = taxonomy_term_load($arr_itemid[1])->field_lnglat['und'][0]['value'];
	}
	else
	{
		$lnglat = taxonomy_term_load($arr_itemid[$num_itemid-1])->field_lnglat['und'][0]['value'];
	}

  $output .= theme('cpic_main_org_homepage_bmap',array('id_str'=>$itemid, 'lnglat'=>$lnglat));

  print $output;

}


function fire_leading_homepage_corp_list(){
 return 'list'; 
}


// 获取某个区域的
// $type: 当前请求的区域类型 
// $id:  当前请求的区域id
function fire_leading_homepage_area_corp_list($type, $id){

  if($type == 'province')
  {
    global $user;
    $uid = $user->uid;
    $user_node = user_load($uid);
    $dis_id = $user_node->field_belong_district['und'][0]['tid'];

    $f = 0;
    $roles = $user_node->roles;
    if(!empty($roles[11])) $f = 1;  // 消防支队
    elseif(!empty($roles[9])) $f = 2;  // 派出所消防监督员

    switch ($f) {
      case 1:
        $dis_id_child = taxonomy_get_children($dis_id);
        break;

      case 2:
        $dis_id_child = array(taxonomy_term_load($dis_id));
        break;
      
      default:
        $d_taxo = taxonomy_vocabulary_machine_name_load('district');

        $dtquery = db_select('taxonomy_term_data','d')
          ->condition('d.vid', $d_taxo->vid)
          ->fields("d");

        $dis_id_child = $dtquery->execute();  
        break;
    }
  }
  else
  {
    if($type == 'city')
    {
      $dis_id_child = taxonomy_get_children($id);
    }
    elseif($type == 'district')
    {
      $dis_id_child = array(taxonomy_term_load($id));
    }
    else
    {
      $d_taxo = taxonomy_vocabulary_machine_name_load('district');

      $dtquery = db_select('taxonomy_term_data','d')
        ->condition('d.vid', $d_taxo->vid)
        ->fields("d");

      $dis_id_child = $dtquery->execute(); 
    }
  }
  
  $output = '';

  $columns = array();
  $columns[] = array(
    'field' => 'all',
    'title' => '全部',
    'width' => '70', 
  );
    foreach ($dis_id_child as $v) {
      if (in_array($v->tid, array('62','63','76'))) {
        continue;
      }
      $columns[] = array(
        'field' => $v->tid,
        'title' => $v->name,
        'width' => '70', 
      );
    }

  $datas = array();
  $data = array();
  $json_data = '';


  $b_taxo = taxonomy_vocabulary_machine_name_load('businesstype');

  $btquery = db_select('taxonomy_term_data','d')
    ->condition('d.vid', $b_taxo->vid)
    ->fields("d");

  $btresults = $btquery->execute();

  // $datas['total'] = $btresults->rowCount();

  foreach ($btresults as $v) {

    $data['all'] = $v->name;

    foreach ($columns as $cv) {
      if ($cv['field']=='all') {
        continue;
      }
      $nquery = db_select('node','n')
        ->condition('type', 'org')
        ->fields('n');

      $nquery->leftJoin("field_data_field_business_type","fbt","fbt.entity_id=n.nid");
      $nquery->condition("fbt.field_business_type_tid",$v->tid)
        ->fields("fbt");

      $nquery->leftJoin("field_data_field_belong_district","fbd","fbd.entity_id=n.nid");
      $nquery->condition("fbd.field_belong_district_tid",$cv['field'])
        ->fields("fbd");

      $number = $nquery->execute()->rowCount();

      $data[$cv['field']] = $number;
 
    }

    $json_data .= drupal_json_encode($data).',';

  }

// $datas['rows'] = $data;




  $output .= theme('area_corp_table_list',array('node'=>'', 'dev'=>$json_data, 'columns'=>drupal_json_encode($columns)));

  print $output;

}


function fire_leading_homepage_area_corp_list_ajax_get($businesstype, $district)
{
 
  $b_taxo = taxonomy_vocabulary_machine_name_load('businesstype');

  $btquery = db_select('taxonomy_term_data','d')
    ->condition('d.vid', $b_taxo->vid)
    ->fields("d",array('tid'));

  $btresults = $btquery->execute()->fetchField();

  $data = array();
  $datas = array();


  $nquery = db_select('node','n')
    ->condition('type', 'org')
    ->fields('n');

  $nquery->leftJoin("field_data_field_business_type","fbt","fbt.entity_id=n.nid");
  $nquery->condition("fbt.field_business_type_tid",$btresults[$businesstype])
    ->fields("fbt");

  $nquery->leftJoin("field_data_field_belong_district","fbd","fbd.entity_id=n.nid");
  $nquery->condition("fbd.field_belong_district_tid",$district)
    ->fields("fbd");  

  $datas['total'] = $nquery->execute()->rowCount();

  $results = $nquery->execute();

  foreach ($results as $value) {
    $org_node = node_load($value->nid);
    
    $data[] = array(
      'nid' => $value->nid,
      'businesstype' => taxonomy_term_load($org_node->field_business_type['und'][0]['tid'])->name, 
      'title' => $org_node->title, 
      'belongsCustomer' => $org_node->field_charger_name['und'][0]['value'], 
      'belongsDealers' => $org_node->field_charger_phone['und'][0]['value'], 
      'address' => $org_node->field_address['und'][0]['value'], 
      'district' => taxonomy_term_load($org_node->field_belong_district['und'][0]['tid'])->name, 
      );
  }

    $datas["rows"] = $data;
    drupal_json_output($datas);


}

// function cpic_main_org_homepage_bmap($type, $nid)
// {
//   $output = '';
//   global $user;
//   $output .='<div>欢迎登陆管理界面！</div>';
//   $mapkey = variable_get('baidu_map_key','');


//   $output .='<script src="http://api.map.baidu.com/api?v=2.0&ak='. $mapkey.'"></script>';
//   $output .='<script src="/'.drupal_get_path('module', 'cpic_main').'/js/fire_cdb_gis_mapapi.js"></script>';


//   $output .='<div id="map-container" style="width:100%; height:600px" class="gis-map">这是地图显示的区域。。。</div>';
//   $output .='<div id="realdlg" title="实时数据" style="width:850px;height:400px;padding:5px 10px"></div>';
 
//   echo $output;

// }

function cpic_main_bmap_ajax_getall($id)
{
  if(!$id){ //获取地图上所有数据 ，其实只获取30个
    $query = db_select('field_data_field_lnglat', 'l');
    $query->condition('bundle', 'org');
    $query->fields('l', array('entity_id', 'field_lnglat_value'));
    $query->range(0,50);
    $results = $query->execute();

    foreach ($results as $row) {
      $org_node = node_load($row->entity_id);
       list($lng,$lat) = explode(',',$row->field_lnglat_value);
        $return = array(
            'name' => $org_node->title,
            'isalarm' => 0,
            // 'devices' => m2m_main_get_plant_assets($org_node->nid,true),
            'lng' => $lng,
            'lat' => $lat,
            'nid'=>$row->entity_id,
        );
        $points[] = $return;
       
    }
    
  }else{
  $arr = explode('-', $id);
  $type = $arr['0'];

  if ($arr['0']=='city') {
    $dis_id = $arr['2'];
    $dis_id_child = taxonomy_get_children($dis_id);
    $dis_id_child_arr = array();
    foreach ($dis_id_child as $k => $v) {
      $dis_id_child_arr[] = $k;
    }

    $query = db_select('field_data_field_lnglat', 'l');
    $query->condition('bundle', 'org');
    $query->fields('l', array('entity_id', 'field_lnglat_value'));
    $results = $query->execute();

    foreach ($results as $row) {
      $org_node = node_load($row->entity_id);
      $did = $org_node->field_belong_district['und'][0]['tid'];
      
      if(in_array($did, $dis_id_child_arr))
      {
        list($lng,$lat) = explode(',',$row->field_lnglat_value);
        $return = array(
            'name' => $org_node->title,
            'isalarm' => 0,
            // 'devices' => m2m_main_get_plant_assets($org_node->nid,true),
            'lng' => $lng,
            'lat' => $lat,
            'nid'=>$row->entity_id,
        );
        $points[] = $return;
      }
        
    }

  }elseif ($type=='district') {
    $nid = $arr['3'];
    $org_nids = db_select("field_data_field_belong_district", "bd")
      ->condition('bd.bundle', 'org')
      ->condition('bd.field_belong_district_tid', $nid)
      ->fields('bd',array('entity_id'))
      ->execute()->fetchCol();
    if(!empty($org_nids))
    {
      $results = db_select('field_data_field_lnglat', 'l')
        ->condition('l.bundle', 'org')
        ->fields('l', array('entity_id', 'field_lnglat_value'))
        ->condition('l.entity_id', $org_nids, 'IN')
        ->execute();

      foreach ($results as $row) {
          $org_node = node_load($row->entity_id);
          list($lng,$lat) = explode(',',$row->field_lnglat_value);
          $return = array(
              'name' => $org_node->title,
              'isalarm' => 0,
              // 'devices' => m2m_main_get_plant_assets($plant_node->nid,true),
              'lng' => $lng,
              'lat' => $lat,
              'nid'=>$row->entity_id,
          );
          $points[] = $return;
      }
    }
  }
  elseif ($type='btype') {
    $nid = $arr['4'];
    $org_nids = db_select("field_data_field_business_type", "bt")
      ->condition('bt.bundle', 'org')
      ->condition('bt.field_business_type_tid', $nid)
      ->fields('bt',array('entity_id'))
      ->execute()->fetchCol();

    $results = db_select('field_data_field_lnglat', 'l')
      ->condition('l.bundle', 'org')
      ->fields('l', array('entity_id', 'field_lnglat_value'))
      ->condition('l.entity_id', $org_nids, 'IN')
      ->execute();

    foreach ($results as $row) {
        $org_node = node_load($row->entity_id);
        list($lng,$lat) = explode(',',$row->field_lnglat_value);
        $return = array(
            'name' => $org_node->title,
            'isalarm' => 0,
            // 'devices' => m2m_main_get_plant_assets($plant_node->nid,true),
            'lng' => $lng,
            'lat' => $lat,
            'nid'=>$row->entity_id,
        );
        $points[] = $return;
    }

  }
  }

  drupal_json_output(array('data' => $points));
}

function cpic_main_leading_homepage(){
    $output = '';
    global $user; 
    if($user->uid > 0){ //登录用户
        $output .= 'home';
    }else{ //匿名用户
        $output .="news center";
    }
    return $output;
}


function cpic_main_org_homepage($type, $org_nid){
    $org_node = node_load($org_nid);
    $instid = $org_node->field_vpaas_instid['und'][0]['value'];
    $devs = array();
    $waterpress = array();
    $waterpos = array();
    $org_devices = vpaas_asset_get_org_devices($org_nid,1);
    foreach($org_devices as $device){
        $wdata = array();
         $props = vpaas_asset_get_device_sensors($device->nid);
                foreach($props as $prop_id => $p){
                $cvalue = 0; 
               // $prop_id = $device->field_dtu_channel['und'][0]['value'];
                $cvalue = vpaas_asset_get_device_specified_field_value($device->field_asset_id['und'][0]['value'],$prop_id);
               
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
               $cvalue = fire_water_calculate_formula($p->channel_id, $cvalue);

               
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
      /*  $waterpress[] = array(
            'name'=> $device->title,
            'threshold'=> $device->field_threshhold['und'][0]['value'],
            'unit'=>'Mpa',
            'data'=>$wdata,
            );
            */
    }

      
   //获取实时水位 
  /* $waterpos = array(
            '水池' => "0%",
            '水箱' => "0%",
    );
    
    */
      
   //获取实时消防通道告警     
  $query = db_select('vpaas_alarm_info', 'am');
//  $query->leftJoin('organizations', 'o', 'o.org_id=am.instid');
 // $query->join('node', 'n','o.nid=n.nid');
//  $query->fields('n', array('nid', 'title'));
  $query->fields('am');
  $query->orderBy('am.alarmtime','DESC');
  $query->condition('am.eventtype', 10);
  $query->condition('am.instid', $org_node->field_vpaas_instid['und'][0]['value']);
  
  $firelane_data = $query->execute()->fetchObject();
  //获取控制室
  $query = db_select('vpaas_alarm_info', 'am');
 // $query->leftJoin('organizations', 'o', 'o.org_id=am.instid');
 // $query->join('node', 'n','o.nid=n.nid');
 // $query->fields('n', array('nid', 'title'));
  $query->fields('am');
  $query->orderBy('am.alarmtime','DESC');
  $query->condition('am.eventtype', 11);
  $query->condition('am.instid', $org_node->field_vpaas_instid['und'][0]['value']);

  
  $ctrlroom_data = $query->execute()->fetchObject();
  
  
  $data->phone= $org_node->field_charger_phone['und'][0]['value'];
  $data->status= $firelane_data->handle_id ? "已处理" : "未处理";
  $data->position=  "西门口";

  $alarm_number = db_query('select count(*) from vpaas_alarm_info where handle_id=0 and instid=:instid',array(':instid'=>$instid))->fetchField();
  $inspect_rate = _fire_inspect_calcuate_total_inspect_rate($org_nid);
  $maintentance_inspect_rate = _fire_inspect_calcuate_total_inspect_rate($org_nid, INSPECTION_EXECUTOR_MAINTENTANCE);

  $saferate = cpic_main_calculate_safeindex($org_nid);
  $qr_number = fire_inspect_get_total_inspected_device_number($org_nid);
  $xhs_number =  1;
  $plmd_number    = 1;
  $box_number = 1; 
  $poor_number = 1; 
  $camera_number = 1; 
  
  $data = array(
        'alarm' => $alarm_number,
        'rate'  => $inspect_rate."%",
        'irate'  => $inspect_rate."%",
        'mrate'  => $maintentance_inspect_rate."%",
        'water' => 0,
        'room' => rand(0,10),
        'lane' => rand(0,10),
        'saferate' => round($saferate) ,
        'waterpress' => $waterpress,
        'waterpos'=>$waterpos,
        'frielane'=>$firelane_data,
        'controlroom'=>$ctrlroom_data,
        'qrcode_number'=>$qr_number,
        'xhs_number'=>$xhs_number,
        'plmd_number'=>$plmd_number,
        'box_number'=>$box_number,
        'poor_number'=>$poor_number,
        'camera_number'=>$camera_number,
     
    );
    $module_path = drupal_get_path('module', 'cpic_main');
    $echart_js_path = '/'.$module_path.'/js/echarts/';
    echo theme('cpic_main_org_homepage',array('node'=>$org_node,'dev'=>$data,'epath'=>$echart_js_path)) ;
}


function fire_leading_select_homepage(){
    drupal_add_css(drupal_get_path('module','cpic_main').'/css/cpic_main.css');
    return theme('cpic_main_selection',array('node'=>null,'dev'=>$devs)) ;
}