<?php
/**
 * Created by PhpStorm.
 * User: Caffrey Xin
 * Date: 2016/1/6 0006
 * Time: 上午 10:17
 * Description: 东营公安普通接口函数
 */


/**
 * 警务信息一键通，按照手机号发送
 * phoneNumber(必填)类型：字符串
 * content(必填)类型：字符串
 * file(可选)类型：文件，可以是图片，声音或者视频段落
 */
function cpic_restapi_send_message_by_phone()
{
    $phoneNumber = empty($_POST['phoneNumber']) ? '' : trim($_POST['phoneNumber']);
    $content = empty($_POST['content']) ? '' : trim($_POST['content']);
    $file = empty($_POST['file']) ? '' : trim($_POST['file']);
    var_export($phoneNumber);
}

/**
 * 警务信息一键通，按照身份证发送
 * id(必填)类型：字符串
 * content(必填)类型：字符串
 * file(可选)类型：文件，可以是图片，声音或者视频段落
 */
function cpic_restapi_send_message_by_id()
{
    $id = empty($_POST['id']) ? '' : trim($_POST['id']);
    $content = empty($_POST['content']) ? '' : trim($_POST['content']);
}

/**
 * 警务信息一键通，按照身份证发送
 * TagID(必填)类型：按照用户标签来发送消息，如果不带参数，则默认全部。
 * content(必填)类型：字符串
 * file(可选)类型：文件，可以是图片，声音或者视频段落
 */
function cpic_restapi_send_message_by_tag()
{
    // $TagID='tag000'是全部
    $TagID = empty($_POST['TagID']) ? 'tag000' : trim($_POST['TagID']);
    $content = empty($_POST['content']) ? '' : trim($_POST['content']);
}
