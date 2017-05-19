<?php
/**
 * @file
 * Bartik's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template normally located in the
 * modules/system directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['featured']: Items for the featured region.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['triptych_first']: Items for the first triptych.
 * - $page['triptych_middle']: Items for the middle triptych.
 * - $page['triptych_last']: Items for the last triptych.
 * - $page['footer_firstcolumn']: Items for the first footer column.
 * - $page['footer_secondcolumn']: Items for the second footer column.
 * - $page['footer_thirdcolumn']: Items for the third footer column.
 * - $page['footer_fourthcolumn']: Items for the fourth footer column.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see bartik_process_page()
 * @see html.tpl.php
 */
?>
<div class="headerwrap" data-options="region:'north',border:false">
    <div class="header">
        <h1 class="logo">
            <a href="<?php print url('/'); ?>"><img src="<?php print path_to_theme();?>/logo.png" width="147" height="35" alt="云警消息一键通" /></a>
        </h1>
        <div id="Nav">
            <ul>
                <li><a href="<?php print url('onlinechat'); ?>"><span class="bg01">在线交流</span></a></li>
                <li><a href="<?php print url('broadcast'); ?>"><span class="bg02">广播消息</span></a></li>
                <li><a href="<?php print url('controlmsg'); ?>"><span class="bg03">控制消息</span></a></li>
                <li><a href="<?php print url('appmanage'); ?>"><span class="bg04">APP管理</span></a></li>
            </ul>
        </div>
        <div class="userInfo">
            <!--<div class="info"><a class="infolink" href="javascript:void(0);"><img src="<?php /*print path_to_theme();*/?>/images/com_ico001.png" width="14" height="14" alt="信息" /></a></div>-->
            <!--<div class="skin"><a class="skins" href="#"><img src="<?php /*print path_to_theme();*/?>/images/com_ico012.png" width="12" height="12" alt="皮肤"></a></div>-->
            <!--<div class="news"><a href="#">
                <img src="<?php /*print path_to_theme();*/?>/images/com_ico011.png"></a>
                <div class="new_count"></div>
            </div>-->

            <div class="user"><a class="username" href="javascript:void(0);"><?php global $user; print $user->name; ?></a></div>
        </div>
        <!--userInfo end--> 
    </div>
</div>
<!--headerwrap end-->
<div class="infomore">
    <div class="infomorebox">
        <div class="item"><a href="javascript:void(0);">使用帮助</a></div>
        <div class="item"><a href="javascript:void(0);" onclick="$('#SubmitLog').dialog('open')">提交BUG/反馈</a></div>
        <div class="item last"><a href="javascript:void(0);">关于软件</a></div>
    </div>
</div>
<!--usermore end-->
<div class="usermore">
    <div class="usermorebox">
        <div class="item"><a href="javascript:void(0);" onclick="$('#ResetUserInfo').dialog('open')">修改个人信息</a></div>
        <div class="item"><a href="javascript:void(0);" onclick="$('#ResetPW').dialog('open')">修改密码</a></div>
        <div class="item last"><a href="javascript:void(0);">退出登录</a></div>
    </div>
</div>
<!--usermore end-->
<div class="skinmore">
    <div class="skinmorebox">
        <div class="item">
            <a class="skin01" href="#">
                <img src="<?php print path_to_theme();?>/images/com_ico013.png">
            </a>
        </div>
        <div class="item last">
            <a class="skin02" href="#">
                <img src="<?php print path_to_theme();?>/images/com_ico014.png">
            </a>
        </div>
    </div>
</div>
<!--skinmore end-->
<div id="ResetUserInfo" class="easyui-dialog dialog_oneCol" title="修改个人信息" closed="true" data-options="buttons: '#RsetUserBtn'">    
    <form id="HeaderForm01" method="post">
        <table class="table01" cellpadding="5">
            <tr>
                <th>用户名:</th>
                <td colspan="3"><input class="easyui-textbox entry01" type="text" name="name" data-options="prompt:'xxxxx',disabled:true" /></td>
            </tr>
            <tr>
                <th>姓名:</th>
                <td colspan="3"><input class="easyui-textbox entry01" type="text" name="email" data-options="required:true" /></td>
            </tr>
            <tr>
                <th>用户角色:</th>
                <td colspan="3"><select class="easyui-combobox entry01" name="language" data-options="disabled:true"><option value="ar">域管理员</option></select></td>
            </tr>
            <tr>
                <th>邮件地址:</th>
                <td colspan="3"><input class="easyui-textbox entry01" type="text" name="email" data-options="required:true,validType:'email'" /></td>
            </tr>
            <tr>
                <th>电话号码:</th>
                <td colspan="3"><input class="easyui-textbox entry01" name="calling" /></td>
            </tr>
            <tr>
                <th>描述:</th>
                <td colspan="3"><input class="easyui-textbox entry01" name="message" data-options="multiline:true" style="height:60px" /></td>
            </tr>
            <tr>
                <th>创建时间</th>
                <td>2015-02-13 08:23:25</td>
                <th>最后更新时间</th>
                <td>2015-02-15 08:23:25</td>
            </tr>
        </table>
    </form>
    <div id="RsetUserBtn"  class="common_btn">
        <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onclick="submitForm()">保存</a>
        <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onclick="clearForm()">取消</a>
    </div>
</div>
<div id="ResetPW" class="easyui-dialog dialog_oneCol" title="修改密码" closed="true" data-options="buttons: '#RsetPWBtn'">  
    <form id="HeaderForm02" method="post">
        <table class="table01" cellpadding="5">
            <tr>
                <th>原密码:</th>
                <td><input class="easyui-textbox entry01" type="password" data-options="required:true" /></td>
            </tr>
            <tr>
                <th>新密码:</th>
                <td><input class="easyui-textbox entry01" type="password" data-options="required:true" /></td>
            </tr>
            <tr>
                <th>重复密码:</th>
                <td><input class="easyui-textbox entry01"  type="password" data-options="required:true" /></td>
            </tr>
        </table>
    </form>
    <div id="RsetPWBtn"  class="common_btn">
        <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onclick="submitPWForm()">保存</a>
        <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onclick="clearPWForm()">取消</a>
    </div>
</div>
<div id="SubmitLog" class="easyui-dialog dialog_oneCol" title="提交反馈" closed="true" data-options="buttons: '#SubmitLogBtn'"> 
    <form id="HeaderForm03" method="post">
        <table class="table01" cellpadding="5">
            <tr>
                <td class="pb20" colspan="2">请在下方提交您的问题和请求。<br />
                输入您的邮箱地址以便于我们可以相应您的反馈。</td>
            </tr>
            <tr>
                <th>Email(可选):</th>
                <td>
                <p class="mb5"><input class="easyui-textbox entry01" type="text" data-options="required:true" /></p>
                <label><input type="checkbox" /> 送一份副本给我自己</label></td>
            </tr>
            <tr>
                <th>描述:</th>
                <td colspan="3"><input class="easyui-textbox entry01" name="message" data-options="multiline:true" style="height:60px" /></td>
            </tr>
        </table>
    </form>
    <div id="SubmitLogBtn"  class="common_btn">
        <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onclick="submitLogForm()">保存</a>
        <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onclick="clearLogForm()">取消</a>
    </div>
</div>

   <?php print render($page['content']); ?>

<div class="footerwrap" data-options="region:'south',border:false">
    <p class="footer">Copyright © 2015 Airpower Corp.All rights reserved.<span class="ft_text">2015-01-15 09:05:05</span></p>
</div>
