<?php

function appmanage_theme()
{
    $output = '<a href="/appmanage/add">添加</a>';

    $rows = array();
    //建立--选择表 并使用分页
    $query = db_select('node', 'n')->extend('PagerDefault');
    //增加查询字段
    $query->addField('n', 'nid');
    $query->condition('n.type', 'appm');
    //条件 status == 1 的
    $query->condition('n.status', 1)->limit(5);
    //ORDER BY
    $query->orderBy('nid', 'ASC');
    $res = $query->execute()->fetchAll();
    foreach($res as $obj)
    {
        $nid = $obj->nid;
        $node = node_load($nid);
        $rows[] = array(
            'name' => $node -> title,
            'descriptions' => $node -> body['und'][0]['value'],
            'url' => $node -> field_app_url['und'][0]['value'],
            'fm' => $node -> field_app_fm['und'][0]['value'],
            'caozuo' => '<a href="'.url('appmanage/edit/'.$nid).'">编辑</a> &nbsp;|&nbsp; <a href="'.url('appmanage/del/'.$nid).'">删除</a>',
        );
    }

    //$header = array('序号','表名','描述','创建人','创建时间','查看详情');
    $header = array(
        array('data' => 'App名称', 'field' => 'name'),
        array('data' => 'App描述', 'field' => 'descriptions'),
        array('data' => 'App回调RUL', 'field' => 'url'),
        //array('data' => 'UID', 'field' => 'uid', 'sort'=>'desc'),
        array('data' => 'FM', 'field' => 'fm'),
        array('data' => '操作', 'field' => 'caozuo'),
    );

    $output .= theme('table', array('header' => $header,'rows' => $rows ,'attributes' => array('class' => array('private-table'))));
    $output .= theme('pager');
    return $output;
}

function appmanage_add_form_theme($form, &$form_state)
{
    $form = array();
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('App名称'),
        '#default_value' => !empty($form_state['values']['name']) ? $form_state['values']['name'] : '',
        '#required'=>true,
    );
    $form['descriptions'] = array(
        '#type' => 'textarea',
        '#title' => t('App描述'),
        '#default_value' => !empty($form_state['values']['descriptions']) ? $form_state['values']['descriptions'] : '',
    );
    $form['url'] = array(
        '#type' => 'textfield',
        '#title' => t('App回调RUL'),
        '#default_value' => !empty($form_state['values']['url']) ? $form_state['values']['url'] : '',
        '#required'=>true,
    );
    $form['fm'] = array(
        '#type' => 'textfield',
        '#title' => t('FM'),
        '#default_value' => !empty($form_state['values']['fm']) ? $form_state['values']['fm'] : '',
        '#required'=>true,
    );

    // Adds a simple submit button that refreshes the form and clears its
    // contents. This is the default behavior for forms.
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => '保存',
    );
    return $form;
}

function appmanage_add_form_theme_validate($form, &$form_state)
{
    // 验证
    if(empty($form_state['values']['name'])) form_set_error('name', t('App名称不能为空'));
    if(empty($form_state['values']['url'])) form_set_error('name', t('App回调RUL不能为空'));
    if(empty($form_state['values']['fm'])) form_set_error('name', t('AFM不能为空'));
}

function appmanage_add_form_theme_submit($form, &$form_state)
{
    $title = trim($form_state['values']['name']);
    $app_url = trim($form_state['values']['url']);
    $app_fm = trim($form_state['values']['fm']);
    $body = empty($form_state['values']['descriptions']) ? '' : trim($form_state['values']['descriptions']);

    $res = save_app($title, $app_url, $app_fm, $body);
    if($res)
    {
        drupal_set_message(t('添加APP成功'));
    }
    else
    {
        drupal_set_message(t('添加APP失败'), 'error');
    }

    drupal_goto(url('appmanage'));
}

// 保存app
function save_app($title, $app_url, $app_fm, $body)
{
    $newNode = new StdClass;
    $newNode->title = $title;
    $newNode->type = 'appm';
    $newNode->uid = 0;
    $newNode->created = strtotime("now");
    $newNode->changed = strtotime("now");
    $newNode->status = 1;
    $newNode->body['und'][0]['value'] = $body;
    $newNode->field_app_url['und'][0]['value'] = $app_url;
    $newNode->field_app_fm['und'][0]['value'] = $app_fm;

    node_object_prepare($newNode);
    // save node
    $newNode = node_submit($newNode);
    node_save($newNode);
    $node_id = $newNode->nid;
    return $node_id;
}

// App修改界面
function appmanage_edit_form_theme($form, $form_state, $id)
{
    if($id)
    {
        $node = node_load($id);
        $id = $node->nid;
        $name = $node->title;
        $descriptions = $node->body['und'][0]['value'];
        $url = $node->field_app_url['und'][0]['value'];
        $fm = $node->field_app_fm['und'][0]['value'];

        $form = array();
        $form['name'] = array(
            '#type' => 'textfield',
            // We don't want the user to be able to edit their name here.
            '#disabled' => FALSE,
            '#title' => t('App名称'),
            '#required' => TRUE,
            '#default_value' => urldecode($name),
        );
        $form['descriptions'] = array(
            '#type' => 'textarea',
            '#title' => t('App描述'),
            '#default_value' => !empty($descriptions) ? $descriptions : '',
        );
        $form['url'] = array(
            '#type' => 'textfield',
            '#title' => t('App回调RUL'),
            '#default_value' => !empty($url) ? $url : '',
            '#required'=>true,
        );
        $form['fm'] = array(
            '#type' => 'textfield',
            '#title' => t('FM'),
            '#default_value' => !empty($fm) ? $fm : '',
            '#required'=>true,
        );
        $form['id'] = array(
            '#type' => 'hidden',
            // We don't want the user to be able to edit their name here.
            '#disabled' => FALSE,
            '#title' => t('Appid'),
            '#required' => TRUE,
            '#value' => !empty($id) ? $id : '0',
        );

        // The question to ask the user.
        $confirmation_question = t('');

        // If the user clicks 'no,' they're sent to this path.
        $cancel_path = url('appmanage');

        // Some helpful descriptive text.
        $description = t('');

        // These are the text for our yes and no buttons.
        $yes_button = t('修改');
        $no_button = t('取消');

        // The name Form API will use to refer to our confirmation form.
        $confirm_name = 'app_edit';

        // Finally, call confirm_form() with our information, and then return the form
        // array it gives us.
        return confirm_form(
            $form,
            $confirmation_question,
            $cancel_path,
            $description,
            $yes_button,
            $no_button,
            $confirm_name
        );
    }

    drupal_goto(url('appmanage'));
}

// 修改app验证
function appmanage_edit_form_theme_validate($form, $form_state)
{
    // code
}

// 修改app处理
function appmanage_edit_form_theme_submit($form, $form_state)
{
    $cpnode = node_load($form_state['values']['id']);
    $cpnode->title = $form_state['values']['name'];
    $cpnode->changed = strtotime("now");
    $cpnode->body['und'][0]['value'] = $form_state['values']['descriptions'];
    $cpnode->field_app_url['und'][0]['value'] = $form_state['values']['url'];
    $cpnode->field_app_fm['und'][0]['value'] = $form_state['values']['fm'];

    node_save($cpnode);

    if($cpnode->nid)
    {
        drupal_set_message(t('修改成功'));
    }
    else
    {
        drupal_set_message(t('修改失败'), 'error');
    }

    drupal_goto(url('appmanage'));
    return;
}

// 删除app界面
function appmanage_del_theme($id)
{
    if($id)
    {
        $node = node_load($id);
        //drupal_set_message(t('确定要删除'), 'warning');
        $html = '<p type="color:red">确定要删除 '.$node->title.'</p>';
        $html .= '<p><a href="'.url('appmanage/del/'.$id.'/1').'">确定</a>&nbsp;&nbsp;&nbsp;&nbsp;<a href="'.url('appmanage/del/'.$id.'/0').'">取消</a></p>';
        return $html;
    }
    else
    {
        drupal_goto(url('appmanage'));
    }
}

// App确认删除or取消
function appmanage_del_and_cancel($id, $type)
{
    if($type)
    {
        // 删除
        $cpnode = node_load($id);
        $cpnode->status = 0;
        $cpnode->changed = strtotime("now");

        node_save($cpnode);
        if($cpnode -> nid)
        {
            drupal_set_message(t('删除成功'));
        }
        else
        {
            drupal_set_message(t('删除失败'), 'error');
        }
    }

    drupal_goto(url('appmanage'));
}