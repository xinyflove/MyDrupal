<?php
/**
 * Created by PhpStorm.
 * User: Caffrey Xin
 * Date: 2016/1/6 0006
 * Time: 上午 10:17
 * Description: 东营公安REST接口函数
 */

/**
 * 测试rest
 * @param $name
 * @param $passwd
 */
function _cpic_restapi_resource_test($name)
{
    /*$res = file_get_contents($name);
    if($res)
    {
        $dest_file = 'public://mms/t.png';
        $file_path = drupal_realpath($dest_file);
        $ret = file_put_contents($file_path, $res);
        return $ret;
    }
    return '2';*/
    return 'this is a test message.';
}
/**
 * 警务信息一键通，按照手机号发送
 * phoneNumber(必填)类型：字符串
 * content(必填)类型：字符串
 * file(可选)类型：文件，可以是图片，声音或者视频段落
 */
function _cpic_restapi_resource_send_message_by_phone($phoneNumber, $appId, $msgId, $content, $file = '')
{
    $appId = trim($appId);
    $msgId = trim($msgId);
    $content = trim($content);
    $file = trim($file);

    if(is_array($phoneNumber))
    {
        if(count($phoneNumber) == 0)
        {
            $data = array('code' => 0, 'msg' => 'phoneNumber参数不能为空');
            return $data;
        }
    }
    else
    {
        $phoneNumber = trim($phoneNumber);
        if($phoneNumber == '')
        {
            $data = array('code' => 0, 'msg' => 'phoneNumber参数不能为空');
            return $data;
        }
        $phoneNumber = array($phoneNumber);
    }

    $res = _cpic_restapi_send_message($phoneNumber, $appId, $msgId, $content, $file);
    return $res;
}

/**
 * 警务信息一键通，按照身份证发送
 * id(必填)类型：字符串
 * content(必填)类型：字符串
 * file(可选)类型：文件，可以是图片，声音或者视频段落
 */
function _cpic_restapi_resource_send_message_by_id($id, $appId, $msgId, $content, $file = '')
{
    $appId = trim($appId);
    $msgId = trim($msgId);
    $content = trim($content);
    $file = trim($file);

    if(is_array($id))
    {
        if(count($id) == 0)
        {
            $data = array('code' => 0, 'msg' => 'id参数不能为空');
            return $data;
        }
    }
    else
    {
        $id = trim($id);
        if($id == '')
        {
            $data = array('code' => 0, 'msg' => 'id参数不能为空');
            return $data;
        }
        $id = array($id);
    }

    $res = _cpic_restapi_send_message($id, $appId, $msgId, $content, $file);
    return $res;
}

/**
 * 警务信息一键通，按照身份证发送
 * TagID(必填)类型：按照用户标签来发送消息，如果不带参数，则默认全部。
 * content(必填)类型：字符串
 * file(可选)类型：文件，可以是图片，声音或者视频段落
 */
function _cpic_restapi_resource_send_message_by_tag($TagID, $appId, $msgId, $content, $file = '')
{
    // $TagID='tag000'是全部
    $TagID = empty($TagID) ? 'tag000' : trim($TagID);
    $appId = trim($appId);
    $msgId = trim($msgId);
    $content = trim($content);
    $file = trim($file);

    if(is_array($TagID))
    {
        if(count($TagID) == 0)
        {
            $TagID = 'tag000';
        }
    }
    else
    {
        $TagID = empty($TagID) ? 'tag000' : trim($TagID);
        $TagID = array($TagID);
    }

    if($content == '')
    {
        $data = array('code' => 0, 'msg' => 'content参数不能为空');
        return $data;
    }

    $res = _cpic_restapi_send_message($TagID, $appId, $msgId, $content, $file);
    return $res;
}
