<?php
function vpaas_org_list(){

  $ids = array();
  $enterprises = array();
  $data = array();
  $host= "http://" . $_SERVER['HTTP_HOST'];
  $header = array('企业logo','企业名称','创建时间','修改时间','操作');
    $query = db_select('node', 'n');
    $query->condition('n.status',NODE_PUBLISHED);
        $query->condition('n.type','enterprise');

    $query->fields('n',array('nid'));
    $results = $query->execute();
    foreach ($results as $result){
     $ids[] = $result->nid;
    }
    foreach ($ids as $id) {
      $enterprise = node_load($id);
      $data[] = array(
          '<img src='.$host.'/sites/default/files/'.$enterprise->field_enterprise_logo['und'][0]['filename']. '  width="120" height="50"/>',
          l($enterprise->title, 'node/' . $enterprise->nid, array($enterprise->nid)),
          date('Y-m-d H:i:s',$enterprise->created),date('Y-m-d H:i:s',$enterprise->changed),
          l(t('编辑'), 'node/' . $enterprise->nid.'/edit', array($enterprise->nid)));
    }
  $output = "";
  $output .= theme('table', array('header' => $header, 'rows' => $data));
  $output .= theme('pager');
  
  return $output;
}


/*menu callback
 * 
 */
function vpaas_org_build_orgs_tree() {
    $id = isset($_POST['id']) ? $_POST['id'] : 0;
    $tree_array = array();
    global $user;

    $f = 0;

    //var_export( user_load($user->uid) );
    if ($id) {
        $levels = explode('-', $id);
        if(count($levels) == 2) {//请求二级组织结构 
           if($levels[0] == 'continent') {  //当前点击一级组织， 下级返回市区
            
             $terms = taxonomy_get_children($levels[1]);
             $type = 'country';
           
           foreach($terms as $term){
              $d_id = $term->tid;
              
                  $number = rand(200,3000); // vpaas_org_get_orgs_tree_counts('country',$levels[1],$term->tid);
                   $tree_array[] = array(
                      'id' => 'country-' .$levels[1].'-'.$term->tid,  // taxonomy term id; 
                      'text' => $term->name."(".$number.")",
                      'state' => 'closed',
                      'attributes' => array('lnglat'=>$term->field_lnglat['und'][0]['value'],'nid' => $term->tid, 'type' => $type, 'url' => url('kpi/static/country/' . $term->tid)),
                
                );
              
           }
             
            }
        }



        if(count($levels) == 3) {//请求三级组织结构 
          if($levels[0] == 'country') {  //当前点击一级组织， 下级返回行业类型
             $vac_modes = taxonomy_vocabulary_machine_name_load('doctype');

            $terms = taxonomy_get_tree($vac_modes->vid);
           foreach($terms as $term){
         //   $number = vpaas_org_get_orgs_tree_counts('doctype',$levels[1],$levels[2],$levels[3],$term->tid);
               $number = rand(10,150);
               $tree_array[] = array(
                'id' => 'doctype-' .$levels[1].'-'.$levels[2].'-'.$term->tid,  //$sid,org id; $btid, business type taxonomy term id; 
                'text' => $term->name."(".$number.")",
                'state' => 'closed',
                'attributes' => array('nid' => $term->tid, 'type' => 'doctype', 'url' => url('kpi/static/doctype/' . $term->tid)),
 
            );
           }

             
        }
        }
       
        if(count($levels) == 4) {//请求第4级组织结构 

        if ($levels[0] == 'doctype') {  //当前点击行业类型， 下级返回完成／未完成类型
                    $type = 'docstatus';
                    $link_url = '#';
                   
                    $link_url = url('kpi/static/corp/' . $row->entity_id); //这个设备是最后一个级别，点击后查看这个设备下所有信息
                    $j = 0;
                    $tree_array[$j]['id'] = 'docstatus-' .$levels[1].'-'.$levels[2].'-'. $levels[3].'-0';  //$sid,org id; $btid, business type taxonomy term id; ;
                    $tree_array[$j]['text'] = '进行中';
                    $tree_array[$j]['attributes'] = array('nid' => 0, 'type' => $type, 'url' => $link_url);
                    $tree_array[$j]['state'] = 'closed';
                    $j = 1;
                    $tree_array[$j]['id'] = 'docstatus-' .$levels[1].'-'.$levels[2].'-'. $levels[3].'-0';  //$sid,org id; $btid, business type taxonomy term id; ;
                    $tree_array[$j]['text'] = '已结项目';
                    $tree_array[$j]['state'] = 'closed';
                    $tree_array[$j]['attributes'] = array('nid' => 1, 'type' => $type, 'url' => $link_url);
        
        }
        }
        
        if(count($levels) == 5) {//请求三级组织结构 
          if($levels[0] == 'docstatus') {  //当前点击一级组织， 下级返回行业类型
             $vac_modes = taxonomy_vocabulary_machine_name_load('industry');

            $terms = taxonomy_get_tree($vac_modes->vid);
           foreach($terms as $term){
         //   $number = vpaas_org_get_orgs_tree_counts('doctype',$levels[1],$levels[2],$levels[3],$term->tid);
               $number = rand(10,120);
               $tree_array[] = array(
                'id' => 'industry-' .$levels[1].'-'.$levels[2].'-'.$levels[3].'-'.$term->tid,  //$sid,org id; $btid, business type taxonomy term id; 
                'text' => $term->name."(".$number.")",
                'attributes' => array('nid' => $term->tid, 'type' => 'industry', 'url' => url('kpi/static/industry/' . $term->tid)),
 
            );
           }

             
        }
        }
       
        
        
        
        
    } else {
        $tree_array = array();
            $vac_modes = taxonomy_vocabulary_machine_name_load('country');
           
             $terms = taxonomy_get_tree($vac_modes->vid,0,1);
             $type = 'continent';
           
           foreach($terms as $term){
         //   $number = vpaas_org_get_orgs_tree_counts('province',$term->tid);
               $number =rand(100,2000);
            	 $tree_array[] = array(
             	   	'id' => 'continent-' .$term->tid,  // taxonomy term id; 
                    'text' => $term->name."(".$number.")",
                	'state' => 'closed',
                    'attributes' => array('nid' => $term->tid, 'type' => $type, 'url' => url('kpi/static/continent/' . $term->tid)),
 
            );
           }
           }
    drupal_json_output($tree_array);
}

function vpaas_org_build_recent_access_org_tree(){
    $tree_array = array();
    global $user;
 
        
        $i = 0;
        //foreach ($orgs as $org) {
        //    $chld_org_node = node_load($org->nid);

            $tree_array[] = array(
                'id' => 'corp-109' ,
                'text' => '天地人和酒店',
                'state' => 'opened',
                 'attributes' => array('nid' => $cnid, 'type' => 'corp', 'url' => url('dashboard/asset/'.$stype.'/'.$cnid)),

            );
            $i ++;
  //      }

    drupal_json_output($tree_array);
}

function vpaas_org_get_org_list($org_id){

    $id = $org_id;
    $tree_array = array();
    global $user;

    if ($id) {
        $childs = vpaas_org_get_children_orgs($id);
        $j=0;
        foreach($childs as $nid=>$child){
            $type = 'org';
            $device_list = array();
            $link_url = '#';
            if (!empty($child['children'])) {
                $tree_array[$j]['state'] = 'closed';
              }else{
                   $type ='gateway'; //如果是最后一个级别了，就获取所有设备信息 gateway表示是设备组或者上级设备
                   $link_url = url('dashboard/plant/'.$nid); //这个设备是最后一个级别，点击后查看这个设备下所有信息

                    $as = _get_cameras($child['org_id']); //获取摄像头设备
                    if(!empty($as)){
                        foreach($as as $seq=>$device){
                            if(!empty($device['cams'])){
                                
                                foreach($device['cams'] as $cnid=>$cam){
                                    $stype = 'cam';
                                    $device_list[] = array(
                                        'id' => $cnid,
                                        'text' => $cam['name'],
                                        'attributes' => array('nid' => $cnid, 'type' => $stype, 'url' => url('dashboard/asset/'.$stype.'/'.$cnid)),
                                    );
                                }
                            }
                        }
            
                    }
                    $machine_asset = _get_devices($child['org_id']);//获取机器设备的信息
                    if(!empty($machine_asset)){
                                
                                foreach($machine_asset as $dnid=>$dev){
                                    $dtype = 'machine';
                                    $device_list[] = array(
                                        'id' => $dnid,
                                        'text' => $dev['name'],
                                        'attributes' => array('nid' => $nid, 'type' => $dtype, 'url' => url('dashboard/asset/'.$dtype.'/'.$dnid)),
                                    );
                                }
                       
                    }
                    
                    
                    if(!empty($device_list)){
                        $tree_array[$j]['children'] = $device_list;
                    }

            }
            $tree_array[$j]['id'] = $child['org_id'];
            $tree_array[$j]['text'] = $child['title'];
            $tree_array[$j]['attributes'] = array('nid' => $nid, 'type' => $type, 'url' => $link_url);
               
            $j ++;
                
       }
//       print_r($tree_array);exit;

    } else {
        if (in_array('webmaster', array_values($user->roles)) || ($user->uid == 1)) {
            $tree_array=array();
            $child_tree_array=array();

            $root = vpaas_org_get_root_org(variable_get('vpaas_root_org_id', '20002'));
            $org_id = $root->org_id;
            $base_name = $root->title;
            
            $orgs = vpaas_org_get_orgs_list($org_id);
            $i = 0;
            foreach ($orgs as $org) {
                $child_tree_array[$i] = array(
                    'id' => $org['cagid'],
                    'text' => $org['title'],
                );
                if (!empty($org['children'])) {
                    $child_tree_array[$i]['state'] = 'open';
                }
                $i ++;
            }
            
            $tree_array[] = array(
                    'id' => $org_id,
                    'text' => $base_name,
                    'state' => 'closed',
                    'children'=>$child_tree_array,
             );
          
              
        } else if (in_array('customer', array_values($user->roles))) {
            
        } else if (in_array('seller', array_values($user->roles))) {
        
            
        }
    }
    drupal_json_output($tree_array);

}

function vpaas_org_get_orgs_tree_counts($type, $prov_tid='', $city_tid='', $dis_tid='' ,$bt_tid='')
{
    $number= 0;
  switch ($type) {
    case 'province':
      $terms = taxonomy_get_children($prov_tid);
      // echo "<pre>";
      // print_r($terms);
      // exit;
      foreach ($terms as $term) {
        $city_terms = taxonomy_get_children($term->tid);
        
        foreach ($city_terms as $city_term) {
          $nquery = db_select("field_data_field_belong_district","fbd")  
            ->condition('bundle', 'org')
            ->condition("field_belong_district_tid",$city_term->tid)
            ->fields("fbd");

          $numbers = $nquery->execute()->rowCount(); 
          
          $number += $numbers;
        }

      }

     break;

    case 'city':
      $terms = taxonomy_get_children($city_tid);
      foreach ($terms as $term) {
        $nquery = db_select("field_data_field_belong_district","fbd")  
          ->condition('bundle', 'org')
          ->condition("field_belong_district_tid",$term->tid)
          ->fields("fbd");

        $numbers = $nquery->execute()->rowCount(); 
        
        $number += $numbers;
      }

     break;

    case 'district':
      $nquery = db_select("field_data_field_belong_district","fbd")  
        ->condition('bundle', 'org')
        ->condition("field_belong_district_tid",$dis_tid)
        ->fields("fbd");

      $number = $nquery->execute()->rowCount();  
     break;

    case 'businesstype':

      $nquery = db_select('node','n')
        ->condition('type', 'org')
        ->fields('n');

      $nquery->leftJoin("field_data_field_business_type","fbt","fbt.entity_id=n.nid");
      $nquery->condition("fbt.field_business_type_tid",$bt_tid)
        ->fields("fbt");

      $nquery->leftJoin("field_data_field_belong_district","fbd","fbd.entity_id=n.nid");
      $nquery->condition("fbd.field_belong_district_tid",$dis_tid)
        ->fields("fbd");

      $number = $nquery->execute()->rowCount();  
     break;
    case 'province': 
    default:
      $nquery = db_select('node','n')
        ->condition('type', 'org')
        ->fields('n');

      $number = $nquery->execute()->rowCount();  

     break;

    }           

  

  return $number;
}

function vpaas_org_ajax_add_org($distrct,$btype){
    
  //$newNode = vpaas_org_create_org_node($distrct,)
    $corp_title = $_POST['title'];
    $corpowner = $_POST['corpowner'];
    $ownerphone = $_POST['ownerphone'];
    $desc = $_POST['desc'];
    $lnglat = $_POST['lnglat'];
    
    global $user; 
    
    //先去VPAAS里的base_inst来创建一个组织，VPAAS使用
    $parent_inst = '20205'; //枣庄市去
    $vpaas_inst_id = 0;
    db_set_active('vpdata');
    $vpaas_inst_id = db_insert('base_inst')
                    ->fields(array(
                        'parent_id' => $parent_inst,
                        'inst_name' => $corp_title,
                        'inst_memo' => $corp_title,
                      
                    ))
                    ->execute();
     db_set_active('default');
           
   $node = vpaas_org_create_org_node($corp_title, $desc, $user->uid, $corpowner, $ownerphone, $distrct,$btype ,$lnglat,$vpaas_inst_id,0);
    if($node){ //如果创建出组织来了，那么创建一个告警组 new_alarm_event_grp 
        $alarm_grp_id = 0; 
         db_set_active('vpdata');
         $alarm_grp_id = db_insert('new_alarm_event_grp')
                    ->fields(array(
                        'event_grp_name' => $corp_title.'告警组',
                        'event_grp_other' => $corp_title,
                        'inst_id' => $vpaas_inst_id,
                    ))
                    ->execute();
     // 到这个告警组插入两个告警 中控室离岗和消防通道占用 
         $event_types = array(10,11);
         if($alarm_grp_id){
             foreach($event_types as $type) {
             $event_id = 0;
             if($type == 10){
                 $text = '中控室离岗告警';
             }
             if($type == 11){
                 $text = '消防通道占用告警';
             }
             
             $event_id = db_insert('new_alarm_event')
                    ->fields(array(
                        'event_name'=>$corp_title.$text,
                        'event_type' => $type,//中控室离岗
                        'event_grp_id' => $alarm_grp_id,
                        'event_level' => 1,
                        'event_guard'=>1,
                        'event_operate'=>1,
                        'event_autoguard'=> 0,
                        'map_id'=>0,
                        'link_cam_id'=>0
                        
                    ))
                    ->execute();
             //订阅出这个信息，允许VPAAS上传告警
             if($event_id){
               $post_url = url('alarmreceive/'.$event_id,array('absolute'=>TRUE));

             $link_id = db_insert('new_alarm_event_link_out')
                    ->fields(array(
                        'event_id'=>$event_id,
                        'link_type' => 12,// link_type为12 表示订阅
                        'link_action_ex1' => $post_url,
                      
                    ))
                    ->execute();
             }
           } 
         }
    
     db_set_active('default');
     
    }
    drupal_json_output(array('nid' => $node->nid));

}


function vpaas_org_ajax_delete_org($org_nid){
    if($org_nid){
        $org_node = node_load($org_nid);
        //删除VPAAS_INST ID； 
    db_set_active('vpdata');
    $vpaas_inst_id = db_delete('base_inst')
                     ->condition('inst_id',$org_node->field_vpaas_instid['und'][0]['value'])
                    ->execute();
     db_set_active('default');
    
         //删除应用信息
        node_delete($org_nid);
        //delete all other ,such as water system.  //fix me later
        //设置水系统的企业ID为0， 但是不删除。
        
        // 删除告警订阅信息
        
        
        drupal_json_output(array('success' => $org_nid));

    }else{
        drupal_json_output(array('errorMsg'=>'Internal Error, Try later'));
    }
}

function vpaas_org_edit_org($org_nid){
    
    global $user; 
    $org_node = node_load($org_nid);
    
    $output .=theme('vpaas_org_editorg_page',array('node'=>$org_node, 'dev'=>''));
    print $output; 
}



/*menu callbck 
 * 
 */
function vpaas_org_prepare_insts_json(){
    db_set_active('vpdata');
    
    $root_id = 0;
    $data = array();
    $query = db_select('base_inst', 'bs');
    $query->fields('bs');
    $query->condition('bs.parent_id',$root_id);
    $results = $query->execute();
    $i = 0; 
    foreach ($results as $row) {

        $data[$i] = array(
            'value' => $row->inst_id,
            'text' => $row->inst_name,
        );
        //第二层
        $sroot_id = $row->inst_id;
        $sdata = array();
        $query = db_select('base_inst', 'bs');
        $query->fields('bs');
        $query->condition('bs.parent_id',$sroot_id);
        $results = $query->execute();
        $j = 0; 
        foreach ($results as $srow) {
           $data[$i]['children'][$j] = array(
            'value' => $srow->inst_id,
            'text' => $srow->inst_name,
        ); 
           //第三层 
            $troot_id = $srow->inst_id;
            $sdata = array();
            $query = db_select('base_inst', 'bs');
            $query->fields('bs');
            $query->condition('bs.parent_id',$troot_id);
            $results = $query->execute();
            foreach ($results as $trow) {
               $data[$i]['children'][$j]['children'][] = array(
                'value' => $trow->inst_id,
                'text' => $trow->inst_name,
            ); 
            } 
            $j++;
        }

        
        $i++;
    }


    db_set_active('default');
    drupal_json_output($data);

}