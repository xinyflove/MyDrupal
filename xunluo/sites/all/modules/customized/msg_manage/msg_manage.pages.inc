<?php

function msg_manage_get_callmsg()
{
    handle_callback_message();
    return 'run';
}

// 获取ftp文件
function get_ftp_file()
{
    $ftp_host = '121.42.173.144';
    $ftp_port = '21';
    $ftp_user = 'devin';
    $ftp_pass = 'devin123';
    $dir = '/out';

    $conn = ftp_connect($ftp_host);
    if(!$conn) return array('code' => 0, 'msg' => "无法连接到$ftp_host");

    $login_result = ftp_login($conn,$ftp_user,$ftp_pass);
    if(!$login_result) return array('code' => 0, 'msg' => "FTP connection has failed!"."Attempted to connect to $ftp_host for user $ftp_user");

    // 获取目录下的文件数组
    $arr_file = ftp_nlist($conn,$dir);

    $file = array();
    foreach($arr_file as $f)
    {
        $path = 'public://mms'.$f;
        //var_export($path);
        $target = drupal_realpath($path);
        $source = $f;
        $download = ftp_get($conn,$target,$source,FTP_BINARY);
        if($download)
        {
            $file[] = file_get_contents($target);
            // 删除ftp已下载且已读的文件
            ftp_delete($conn, $source);
            // 删除本地下载的已读文件
            del_local_callmsg($path);
        }

        if(count($file) == 10) break;
    }

    ftp_close($conn);
    return array('code' => 1, 'msg' => $file);
}

// 处理获取的回执信息
function handle_callback_message()
{
    $res = get_ftp_file();
    if($res['code'])
    {
        //echo '<pre>';
        foreach($res['msg'] as $fv)
        {
            // 变量每一个文件
            $ret = json_decode($fv);

            foreach($ret as $row)
            {
                $fm = empty($row->fm) ? '' : $row->fm;
                $msgid = empty($row->msgid) ? '' : $row->msgid;
                $msgs = empty($row->s) ? '0' : $row->s;
                $msgto = empty($row->to) ? '' : $row->to;
                $msgts = empty($row->ts) ? '' : $row->ts;

                $msg = array(
                    'app_fm' => $fm,
                    'msgid' => $msgid,
                    'msgs' => $msgs,
                    'msgto' => $msgto,
                    'msgts' => $msgts,
                );

                //var_export($msg);
                //save_callback_msg($msg); // 保存信息

                $query = db_select('field_data_field_app_fm', 'fm')
                    -> condition('bundle', 'appm', '=')
                    -> condition('field_app_fm_value', $fm, '=')
                    -> fields('fm', array('entity_id'));
                $result = $query -> execute();
                if($r = $result -> fetchAssoc())
                {
                    $nid = $r['entity_id'];
                    $node = node_load($nid);
                    if($node)
                    {
                        $app_url = $node -> field_app_url['und'][0]['value'];
                        $data = array(
                            'fm' => $fm,
                            'msgid' => $msgid,
                            's' => $msgs,
                        );
                        callback_msg_send_app($app_url, $data);   // 回执消息返回给app
                    }
                }
            }
        }
    }
    drupal_set_message(t('获取回执信息成功'));
}

// 保存回执信息到数据库
function save_callback_msg($msg)
{
    $newNode = new StdClass;
    $newNode->type = 'cmsgm';
    $newNode->uid = 0;
    $newNode->created = strtotime("now");
    $newNode->changed = strtotime("now");
    $newNode->status = 1;
    $newNode->field_app_fm['und'][0]['value'] = $msg['app_fm'];
    $newNode->field_msgid['und'][0]['value'] = $msg['msgid'];
    $newNode->field_msgs['und'][0]['value'] = $msg['msgs'];
    $newNode->field_msgto['und'][0]['value'] = $msg['msgto'];
    $newNode->field_msgts['und'][0]['value'] = $msg['msgts'];

    node_object_prepare($newNode);
    // save node
    $newNode = node_submit($newNode);
    node_save($newNode);
    $node_id = $newNode->nid;
}

// 回执消息返回给app
function callback_msg_send_app($url, $data)
{
    $data = json_encode($data);
    $options = array(
        'method' => 'POST',
        'data' => $data,
        'timeout' => 15,
        'headers' => array('Content-Type' => 'application/json'),
    );

    $result = drupal_http_request($url, $options);
    // $result->code == '200' success
    //watchdog('PostMsg', 'url:'.$url.';param:'.$data.';data:'.$result->data.';code:'.$result->code);
}

// 删除本地回执信息
function del_local_callmsg($path)
{
    $fid = db_query("SELECT fid FROM {file_managed} WHERE uri = :path", array(':path' => $path))->fetchField();
    if ($fid) {
        $file = file_load($fid);
        file_delete($file);
    }
    else {
        file_unmanaged_delete($path);
    }
}