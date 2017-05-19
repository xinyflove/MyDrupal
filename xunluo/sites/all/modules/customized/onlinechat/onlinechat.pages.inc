<?php




function onlinechat_landing_page(){
  //  $build_arrays = drupal_get_form('onlinechat_login_form');
  //  return render($build_arrays);
    
    $pass = '666666';
    global $user;
    $name=$user->name;

    if($user->uid == 1)
    {
        $userid = '370687199007120691';
        $name = '18653621610';
    }
    else
    {
        $user_n = user_load($user->uid);
        $userid = empty($user_n->field_userid['und'][0]['value']) ? '' : $user_n->field_userid['und'][0]['value'];
        $mobilephone = empty($user_n->field_mobilephone_sn['und'][0]['value']) ? '' : $user_n->field_mobilephone_sn['und'][0]['value'];
    }
        $url = "http://121.42.173.144:10000/login?u=$name&p=$pass";
        $result = drupal_http_request($url);

        if($result->code == 200){ //数据获取成功
            $data = json_decode($result->data);
            if($data->c==0){ //登录成功
               $jwt = $data->m->j; 
               variable_set('user_jwt_'.$user->uid,$jwt);
             //  drupal_add_js('//cdn.jsdelivr.net/sockjs/1.0.3/sockjs.min.js', 'external');

               drupal_set_message($name.'已经准备好了了聊天');

              }
        }else{
            drupal_set_message('登录错误');
        }
        $output = '';
     /*   drupal_add_js( array ("onlinechat" => array('jwt'=>variable_get('user_jwt_'.$user->uid,'123'))), 'setting');
        drupal_add_js(drupal_get_path('module','onlinechat').'/js/onlinechat.js');
        drupal_add_css(drupal_get_path('module','onlinechat').'/css/chat.css');
        
        $output .='<div class="chatwind">';
        $output .= '<div data-from="Sonu Joshi" id="convo">  
                    <ul class="chat-thread">
                    </ul>';
        $output .='<input style="width:300px;" placeholder="Type here..." class="inputMessage">';

        $output .='</div>';
       */
        $output .="请从左侧选择聊天对象"; 
        return $output; 
}

// 测试信息的广播发送
function onlinechat_broadcast_form($form, &$form_state) {

    $form['description'] = array(
        '#type' => 'item',
        '#title' => t('测试信息的广播发送'),
    );
    $form['selected'] = array(
        '#type' => 'select',
        '#title' => t('选择需要发送的用户'),
        '#options' => array(
            'u000'=>'全体用户',
            'u001'=>'u001',
            'u002'=>'u002',
            'u003'=>'u003',
            'u004'=>'u004',
            'u005'=>'u005',
            'u10001'=>'u10001',
            'u10002'=>'u10002',
            'u10003'=>'u10003',
            'u10004'=>'u10004',
            'u10005'=>'u10005',
            'u10006'=>'u10006',
        ),
        '#multiple' => true,
        '#default_value' => 'u000',
    );

    $form['message'] = array(
        '#type' => 'textarea',
        '#title' => t('发送的消息'),
        '#default_value'=>'这里填写发送的消息',
        '#required'=>true,
    );

    $form['upfile'] = array(
        '#type' => 'file',
        '#title' => t('上传文件'),
        '#description' => t('上传图片、音频、视频文件'),
    );
  
    // Adds a simple submit button that refreshes the form and clears its
    // contents. This is the default behavior for forms.
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => '广播',
    );
    return $form;
}

function onlinechat_broadcast_form_validate($form, &$form_state)
{
    $upfile = file_save_upload('upfile', array(
        // Validates file is really an image.
        //'file_validate_is_image' => array(),
        // Validate extensions.
        //'file_validate_extensions' => array('png gif jpg jpeg mp4 avi 3gp rmvb  wmv mkv  mpg vob mov flv flac ape wav mp3 aac ogg wma'),
        'file_validate_extensions' => array(), // all extensions
    ));
    // If the file passed validation:
    if ($upfile) {
        // Move the file into the Drupal file system.
        if ($upfile = file_move($upfile, 'public://mms')) {
            // Save the file for use in the submit handler.
            $form_state['storage']['upfile'] = $upfile;
        }
        else {
            form_set_error('upfile', t("Failed to write the uploaded file to the site's file folder."));
        }
    }
    else {
        //form_set_error('upfile', t('No file was uploaded.'));

    }
}

function onlinechat_broadcast_form_submit($form, &$form_state) {
    global $user ;
    $name=$user->name;

    $fm = $name;
    $msgid = 'msgid1231';
    $mt = '';

    if(isset($form_state['storage']['upfile']))
    {
        $upfile = $form_state['storage']['upfile'];
        // We are done with the file, remove it from storage.
        unset($form_state['storage']['upfile']);
        // Make the storage of the file permanent.
        $upfile->status = FILE_STATUS_PERMANENT;

        // 文件命名1
        //$upfile -> filename = $fm.'-'.$msgid.'-'.$upfile -> filename;

        // 文件命名2
        $arr_filename = explode('.', $upfile -> filename);
        $ext = end($arr_filename);
        $upfile -> filename = $fm.'-'.$msgid.'-'.time().'.'.$ext;

        // Save file status.
        file_save($upfile);

        $message = $upfile -> filename;
        $ft = explode('/', $upfile->filemime);
        if($ft[0] == 'audio') $mt = 'audio';
        elseif($ft[0] == 'video') $mt = 'video';
        elseif($ft[0] == 'image') $mt = 'image';
        else $mt = 'file';

        _onlinechat_ftp_put_file($upfile->uri,$upfile);
    }
    else
    {
        $message = $form_state['values']['message'];
    }


    if($message == ''){
            form_set_error('message', t('发送内容不能为空'));
    }
    $to = $form_state['values']['selected'];

    if(is_array($to))
    {
        $to = array_keys($form_state['values']['selected']);
    }
    else
    {
        $to = array($to);
    }

    $sendArray = array(
        'e'=> $message,
        'fm'=> $fm,
        'msgid' => $msgid,
        'mt' => $mt,
        'to'=> $to,
    );

    $file_name = 'mms'.time().'.txt'; // xml,pdf,doc etc as you needed
    $dest_file = 'public://mms/' .$file_name;
    $file = file_save_data(json_encode($sendArray),$dest_file);die;

    _onlinechat_ftp_put_file($dest_file,$file);

    drupal_set_message($file_name.'文件已经生成并被交换到FTP区');
        
}

function _onlinechat_ftp_put_file($file_path, $file){
        $ftp_host = '121.42.173.144';
        $ftp_port = '21';
        $ftp_user = 'devin';
        $ftp_pass = 'devin123';
        
       ini_set('display_errors',1);
       error_reporting(E_ALL|E_STRICT);

    // set up a connection or die
    $conn_id = ftp_connect($ftp_host) or die("无法连接到$ftp_host\n");

    $login_result = ftp_login($conn_id, $ftp_user, $ftp_pass);

    if ((!$conn_id) || (!$login_result)) {
        echo "FTP connection has failed!";
        echo "Attempted to connect to $ftp_host for user $ftp_user";
        exit;
    } else {
        echo "Connected to $ftp_host, for user $ftp_user\n";
    }

    // try to login
    $source_file = drupal_realpath($file_path);  //源地址
    $destination_file = "/in/" .$file->filename;  //目标地址
    $upload = ftp_put($conn_id, $destination_file, $source_file, FTP_BINARY) or die("Couldn't connect to $ftp_host");
   // ftp_quit($conn_id);

    if (!$upload) {
        echo "FTP upload has failed!";
    } else {
        echo "Uploaded $source_file to $ftp_host as $destination_file";
    }
    ftp_close($conn_id);

    // 删除已提交的文件
    $fid = db_query("SELECT fid FROM {file_managed} WHERE uri = :path", array(':path' => $file_path))->fetchField();
    if ($fid) {
        $file = file_load($fid);
        file_delete($file);
    }
    else {
        file_unmanaged_delete($file_path);
    }
}

function onlinechat_send_control_msg_form($form, &$form_state) {
      
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('测试控制信息的发送'),
  );
   $form['selected'] = array(
       '#type' => 'select',
       '#title' => t('选择需要发送的用户'),
       '#options' => array(
          'u000'=>'全部',
          'u001'=>'u001',
           'u002'=>'u002',
           'u003'=>'u003',
           'u004'=>'u004',
           'u005'=>'u005',
            'u006'=>'u006',
           'u10001'=>'u10001',
           'u10002'=>'u10002',
           'u10003'=>'u10003',
           'u10004'=>'u10004',
           'u10005'=>'u10005',
           'u10006'=>'u10006',
       ),
       '#multiple' => true, 
       '#default_value' => 'u001',
   );
   
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('发送的消息'),
    '#default_value'=>'发送的消息包含 云巡逻 三个字，就启动云巡逻app ',
    '#required'=>true,
  );
  
  
  // Adds a simple submit button that refreshes the form and clears its
  // contents. This is the default behavior for forms.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

function onlinechat_send_control_msg_form_submit($form, &$form_state) {
    $message = $form_state['values']['message'];
    if($message == ''){
        form_set_error('message', t('发送内容不能为空'));
    }

    global $user ;
    $name=$user->name;

    $fm = $name;
    $msgid = 'msgid1231';
    $mt = 'controlMsg';


    $to = $form_state['values']['selected'];

    if(is_array($to))
    {
        $to = array_keys($form_state['values']['selected']);
    }
    else
    {
        $to = array($to);
    }

    $sendArray = array(
        'e'=> $message,
        'fm'=> $fm,
        'msgid' => $msgid,
        'mt' => $mt,
        'to'=> $to,
    );

    $file_name = 'cms'.time().'.txt'; // xml,pdf,doc etc as you needed
    $dest_file = 'public://mms/' .$file_name;
    $file = file_save_data(json_encode($sendArray),$dest_file);

    _onlinechat_ftp_put_file($dest_file,$file);

    drupal_set_message($file_name.'文件已经生成并被交换到FTP区');
        
}


/*
 * menu callback
 */
function onlinechat_talk_with_user($username){
       $output = '';
       global $user;
       
        drupal_add_js( array ("onlinechat" => array('from'=>$user->name,"to"=>$username, 'jwt'=>variable_get('user_jwt_'.$user->uid,'123'))), 'setting');
        $module_path = drupal_get_path('module','onlinechat');

        drupal_add_js($module_path.'/js/onlinechat.js');
        drupal_add_css($module_path.'/css/chat.css');
        $output .='<div class="chatwind">';
        $output .='<span class="chat-status">聊天准备就绪</span>';
        $output .='<div id="InterlocutionWrap">
	<div id="Interlocution" class="interlocution">
		
	</div>
</div>';
        $output .= '<div style="width:50%; color:black;"><span>'.$user->name.'说:</span> <input style="width:250px;" placeholder="Type here..." class="inputMessage"></div>';

        $output .='</div>';
        
        return $output; 
}