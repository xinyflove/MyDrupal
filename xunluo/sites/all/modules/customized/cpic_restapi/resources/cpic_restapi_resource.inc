<?php
/**
 * Created by PhpStorm.
 * User: Caffrey Xin
 * Date: 2016/1/6 0006
 * Time: 上午 10:17
 * Description: 东营公安REST接口
 */

function _cpic_restapi_resource_definition()
{
    $definition = array(
        'sendmsg' => array(	// resource 名称
            'actions' => array(	// 方法
                'test' => array(	// 方法名称
                    'help' => t('测试rest'),	// 在页面提示信息
                    'file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource.pages'),	// 固定写法
                    'callback' => '_cpic_restapi_resource_test',	// 回调函数
                    'args' => array(	// 参数
                        array(
                            'name' => 'name',	// 传递参数名称
                            'optional' => true,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => 'test name',	// 描述信息
                            'source' => array('data' => 'name'),	// 固定写法
                        ),
                    ),

                    'access callback' => '_cpic_restapi_resource_access',
                    'access callback file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource'),
                    'access arguments' => array('view'),
                    'access arguments append' => TRUE,
                ),

                'sendMessage' => array(	// 方法名称
                    'help' => t('按照手机号发送'),	// 在页面提示信息
                    'file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource.pages'),	// 固定写法
                    'callback' => '_cpic_restapi_resource_send_message_by_phone',	// 回调函数
                    'args' => array(	// 参数
                        array(
                            'name' => 'phoneNumber',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => '电话号码',	// 描述信息
                            'source' => array('data' => 'phoneNumber'),	// 固定写法
                        ),
                        array(
                            'name' => 'appId',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => 'APP id',	// 描述信息
                            'source' => array('data' => 'appId'),	// 固定写法
                        ),
                        array(
                            'name' => 'msgId',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => '消息 id',	// 描述信息
                            'source' => array('data' => 'msgId'),	// 固定写法
                        ),
                        array(
                            'name' => 'content',
                            'optional' => true,
                            'type' => 'string',
                            'description' => '信息内容',
                            'source' => array('data' => 'content'),
                        ),
                        array(
                            'name' => 'file',
                            'optional' => true,
                            'type' => 'string',
                            //'default value' => '0',
                            'description' => '文件，可以是图片，声音或者视频段落',
                            'source' => array('data' => 'file'),
                        ),
                        array(
                            'name' => 'ext',
                            'optional' => true,
                            'type' => 'string',
                            'description' => '文件扩展',
                            'source' => array('data' => 'ext'),
                        ),
                    ),

                    'access callback' => '_cpic_restapi_resource_access',
                    'access callback file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource'),
                    'access arguments' => array('view'),
                    'access arguments append' => TRUE,
                ),

                'sendMessageById' => array(	// 方法名称
                    'help' => t('按照身份证发送'),	// 在页面提示信息
                    'file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource.pages'),	// 固定写法
                    'callback' => '_cpic_restapi_resource_send_message_by_id',	// 回调函数
                    'args' => array(	// 参数
                        array(
                            'name' => 'id',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => '身份证号码',	// 描述信息
                            'source' => array('data' => 'id'),	// 固定写法
                        ),
                        array(
                            'name' => 'appId',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => 'APP id',	// 描述信息
                            'source' => array('data' => 'appId'),	// 固定写法
                        ),
                        array(
                            'name' => 'msgId',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => '消息 id',	// 描述信息
                            'source' => array('data' => 'msgId'),	// 固定写法
                        ),
                        array(
                            'name' => 'content',
                            'optional' => false,
                            'type' => 'string',
                            'description' => '信息内容',
                            'source' => array('data' => 'content'),
                        ),
                        array(
                            'name' => 'file',
                            'optional' => true,
                            'type' => 'string',
                            //'default value' => '0',
                            'description' => '文件，可以是图片，声音或者视频段落',
                            'source' => array('data' => 'file'),
                        ),
                        array(
                            'name' => 'ext',
                            'optional' => true,
                            'type' => 'string',
                            'description' => '文件扩展',
                            'source' => array('data' => 'ext'),
                        ),
                    ),

                    'access callback' => '_cpic_restapi_resource_access',
                    'access callback file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource'),
                    'access arguments' => array('view'),
                    'access arguments append' => TRUE,
                ),

                'sendMessageByTag' => array(	// 方法名称
                    'help' => t('按照标签分组发送'),	// 在页面提示信息
                    'file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource.pages'),	// 固定写法
                    'callback' => '_cpic_restapi_resource_send_message_by_tag',	// 回调函数
                    'args' => array(	// 参数
                        array(
                            'name' => 'TagID',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => '身份证号码',	// 描述信息
                            'source' => array('data' => 'TagID'),	// 固定写法
                        ),
                        array(
                            'name' => 'appId',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => 'APP id',	// 描述信息
                            'source' => array('data' => 'appId'),	// 固定写法
                        ),
                        array(
                            'name' => 'msgId',	// 传递参数名称
                            'optional' => false,	// 传递参数是否可以不传
                            'type' => 'string',	// 参数值类型
                            'description' => '消息 id',	// 描述信息
                            'source' => array('data' => 'msgId'),	// 固定写法
                        ),
                        array(
                            'name' => 'content',
                            'optional' => false,
                            'type' => 'string',
                            'description' => '信息内容',
                            'source' => array('data' => 'content'),
                        ),
                        array(
                            'name' => 'file',
                            'optional' => true,
                            'type' => 'string',
                            //'default value' => '0',
                            'description' => '文件，可以是图片，声音或者视频段落',
                            'source' => array('data' => 'file'),
                        ),
                        array(
                            'name' => 'ext',
                            'optional' => true,
                            'type' => 'string',
                            'description' => '文件扩展',
                            'source' => array('data' => 'ext'),
                        ),
                    ),

                    'access callback' => '_cpic_restapi_resource_access',
                    'access callback file' => array('type' => 'inc', 'module' => 'cpic_restapi', 'name' => 'resources/cpic_restapi_resource'),
                    'access arguments' => array('view'),
                    'access arguments append' => TRUE,
                ),
            ),
        ),
    );

    return $definition;
}

function _cpic_restapi_resource_access($op = 'view', $args = array()) {
    return true;
}