<div style="margin: 5px 10px;"><div><span style="margin-right: 5px;">企业名称：</span> <span><?php print $node->title;?></span></div>    <div id="tt" class="easyui-tabs" style="width:100%;">        <div title="企业基本信息" style="padding:20px;">            <iframe src="<?php print url('node/'.$node->nid.'/edit'); ?>" width="100%" height="400px"></iframe>        </div>        <div title="水系统设备" data-options="closable:false,fit:true" style="overflow:auto;padding:20px; height:500px;" >          <div class="easyui-layout" data-options="fit:true">                <div class="maintop" data-options="region:'north',border:false">                    <div class="main_header">                        <div class="main_title">水系统设备列表</div>                        <div class="main_edit">                            <ul class="editlist">                                 <li class="btn"><a class="add_btn" href="javascript:void(0);" title="添加" onClick="openAddWaterAssetDlg()"><img class="rollover" src="/<?php print path_to_theme('xftheme'); ?>/images/com_ico_add.png" width="17" height="17" alt="添加" /></a></li>                                <li class="btn"><a class="del_btn" href="javascript:void(0);" title="删除" onClick="batchDelWaterAssets()"><img class="rollover" src="/<?php print path_to_theme('xftheme'); ?>/images/com_ico_del.png" width="13" height="17" alt="删除" /></a></li>                                                           </ul>                        </div>                    </div>                    <!--main_header end-->                                    </div>                <div class="main_data" data-options="region:'center',border:false">                 <table id="WaterAssetDg" class="easyui-datagrid" style="width:100%;"                        data-options="singleSelect:true,fit:true, fitColumns:true,url:'<?php print url('/vpaasassets/devices/fetch/1'.'/'.$node->nid); ?>',method:'get'">                        <thead>                            <tr>                                <th data-options="field:'check',checkbox:true"></th>                                <th field="nid" width="20" data-options="align:'center',formatter:formatWaterOperations">操作</th>                                <th field="asset_id" width="20" data-options="">编码</th>                                <th field="title" width="50" data-options="">设备名称</th>                                <th field="type"  width="20" data-options="">类型</th>                                <th field="location"  width="50" data-options="">安装位置</th>                                <th field="dtu"  width="100" data-options="">关联DTU信息</th>                            </tr>                        </thead>                    </table>                     <!--DeviceDatatree end-->                    <div id="editWaterAssetDialog" style="width: 560px;padding:10px;" class="easyui-dialog" title="添加水系统设备" closed="true" data-options="shadow:false,buttons:'#WaterAssetDlg_buttons'">                        <form id="myWaterAssetForm" method="post">                                    <table class="table03">                                        <tbody>                                            <tr>                                                <td colspan="2" >                                                    <input id="corp" name="corp" type="hidden" value="0" />                                                </td>                                            </tr>                                            <tr>                                                <td>设备名称</td>                                                <td><input  name="devname" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td>                                            </tr>                                            <tr>                                                <td>采集RTU手机号</td>                                                <td><input  name="sim" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td>                                            </tr>                                        <!--    <tr>                                                <td>RTU类型</td>                                                <td><input class="easyui-combobox"  name="assettype" style="width:180px;" data-options="                                                    url: '/vpaasassets/prepare/assettypes',                                                    valueField:'value',                                                    textField:'text',                                                    onSelect: function(rec){                                                        var url = '<?php print url('vpaasassets/prepare/assetprops/'); ?>'+ rec.value;                                                        $.post('<?php print url('vpaasassets/prepare/assetprops/'); ?>'+ rec.value, {}, function(result) {                                                         if (result) {                                                           $('#propa1').combobox('loadData', result.res);                                                        $('#propa1').combobox('select',result.res[0].value);                                                                                                                $('#propa2').combobox('loadData', result.res);                                                        $('#propa2').combobox('select',result.res[1].value);                                                        $('#propa3').combobox('loadData', result.res);                                                        $('#propa3').combobox('select',result.res[2].value);                                                        $('#propa4').combobox('loadData', result.res).combobox('select',result.res[3].value);                                                         }                                                                                                              }, 'json');                                                   }                                                   ">                                                 </td>                                            </tr>                                        -->                                        <!--    <tr>                                                <td>采集点位</td>                                                <td>                                                    <table>                                                        <tr><td colspan="3">如果某个通道不接传感器，安装位置不要填写</td></tr>                                                        <tr><td>采集通道</td><td>采集类型</td><td>安装位置</td></tr>                                                        <tr><td>A1</td><td><input id="propa1" name="channel-a1" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:true,valueField: 'value',textField: 'text'"/></td><td><input  name="location-a1" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td></tr>                                                        <tr><td>A2</td><td><input id="propa2" name="channel-a2" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:true,valueField: 'value',textField: 'text'"/></td><td><input  name="location-a2" class="set_input_w01 easyui-validatebox"  data-options="required:false" /></td></tr>                                                        <tr><td>A3</td><td><input id="propa3" name="channel-a3" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:true,valueField: 'value',textField: 'text'"/></td><td><input  name="location-a3" class="set_input_w01 easyui-validatebox"  data-options="required:false" /></td></tr>                                                        <tr><td>A4</td><td><input id="propa4" name="channel-a4" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:true,valueField: 'value',textField: 'text'"/></td><td><input  name="location-a4" class="set_input_w01 easyui-validatebox"  data-options="required:false" /></td></tr>                                                    </table>                                                                                                                                                        </td>                                            </tr>                                         -->                                        <tr>                                            <td>采集点位</td>                                                <td>                                                    <table>                                                        <tr><td colspan="3"><span style="color:red" >如果某个通道不接传感器，安装位置不要填写</span></td></tr>                                                        <tr><td>采集通道</td><td>采集类型</td><td>安装位置</td></tr>                                                        <tr><td>A1</td><td><input id="propa1" name="channel-a1" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:false,valueField: 'value',textField: 'text',data:[{'value':'1','text':'喷淋末端'},{'value':'2','text':'消火栓'},{'value':'3','text':'水箱水位'},{'value':'4','text':'水池水位'}]"/></td><td><input  name="location-a1" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td></tr>                                                        <tr><td>A2</td><td><input id="propa2" name="channel-a2" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:false,valueField: 'value',textField: 'text',data:[{'value':'1','text':'喷淋末端'},{'value':'2','text':'消火栓'},{'value':'3','text':'水箱水位'},{'value':'4','text':'水池水位'}]"/></td><td><input  name="location-a2" class="set_input_w01 easyui-validatebox"  data-options="required:false" /></td></tr>                                                        <tr><td>A3</td><td><input id="propa3" name="channel-a3" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:false,valueField: 'value',textField: 'text',data:[{'value':'1','text':'喷淋末端'},{'value':'2','text':'消火栓'},{'value':'3','text':'水箱水位'},{'value':'4','text':'水池水位'}]"/></td><td><input  name="location-a3" class="set_input_w01 easyui-validatebox"  data-options="required:false" /></td></tr>                                                        <tr><td>A4</td><td><input id="propa4" name="channel-a4" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="readonly:false,valueField: 'value',textField: 'text',data:[{'value':'1','text':'喷淋末端'},{'value':'2','text':'消火栓'},{'value':'3','text':'水箱水位'},{'value':'4','text':'水池水位'}]"/></td><td><input  name="location-a4" class="set_input_w01 easyui-validatebox"  data-options="required:false" /></td></tr>                                                    </table>                                                                                                                                                        </td>                                            </tr>                                                                                        <tr>                                                <td>水箱水位门限制</td>                                                <td><input  name="tankthresh" class="set_input_w01 easyui-validatebox"  data-options="required:true" /><span style="color: red">比如：1.5-2.0,中间为-</span></td>                                            </tr>                                              <tr>                                                <td>水池水位门限制</td>                                                <td><input  name="poolthresh" class="set_input_w01 easyui-validatebox"  data-options="required:true" /><span style="color: red">比如：1.5-2.0,中间为-</span></td>                                            </tr>                                                                                                  </tbody>                                    </table>                        </form>                                            </div>                    <div id="WaterAssetDlg_buttons" class="common_btn">                            <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onClick="saveWaterAsset()">保存</a>                            <a href="javascript:void(0)" class="easyui-linkbutton close_btn" onClick="$('#editWaterAssetDialog').dialog('close')">关闭</a>                        </div>                    <!--editQrCodeDialog end-->                                   </div>                                            </div>            <!--tab2 end -->        </div>        <div title="视频设备" data-options="closable:false,fit:true" style="height:500px;">            <table id="cameradg" class="easyui-datagrid" fit="true" style="height:600px"                   url="<?php print url('vpaasassets/prepare/cloudt/cameras'); ?>" toolbar="#cameratb"                   rownumbers="true" pagination="false">                <thead>                    <tr>                        <th field="name" width="80">名称</th>                        <th field="devtitle" width="150" align="right">设备名称</th>                        <th field="channel" width="120" align="right">所在通道号</th>                        <th field="image" width="350">实时图片</th>                                           </tr>                </thead>            </table>            <div id="cameratb" style="padding:3px">                <span>选择对应的云终端:</span>                <input id="cloudt" class="easyui-combobox" name="cloudt" style="width:140px;" data-options="                       url: '/vpaasassets/prepare/cloudts',                       method: 'get',                       valueField:'value',                       textField:'text',                       groupField:'group',                       onLoadSuccess:function(){                           var selectedNode = $('#orgTree').tree('getSelected');                            $.post('<?php print url('vpaasassets/prepare/cloudt/'); ?>'+selectedNode.id, {}, function(result) {                                            if (result) {                                   $('#cloudt').combobox('setValue',result.vs_no);                                $('#cloudt').combobox('setText',result.vs_pos);                                $('#cloudtsn').textbox('setText', result.vs_no);                                $('#cloudtsn').textbox('setValue', result.vs_no);                                $('#cameradg').datagrid('reload',{sn:result.vs_no});                             }                          }, 'json');                       },                       onSelect: function(rec){                       // var url = '/configuration/seller/ajax/getarea/'+rec.value;                       $('#cloudtsn').textbox('setValue', rec.value);                       $('#cloudtsn').textbox('setText', rec.value);                       $('#cameradg').datagrid('reload',{sn:rec.value});                       }                       ">                或者输入序列号：                    <input id="cloudtsn" name="cloudtsn" class="easyui-textbox" data-options="iconCls:'icon-search'" style="width:300px">                <a href="#" class="easyui-linkbutton" plain="true" iconCls="icon-reload" onclick="assginCloudtToOrg()">关联此云终端</a>            </div>        </div>        <div title="账号管理" data-options="closable:false,fit:true" style="height:500px;">            <table id="accountdg" class="easyui-datagrid" fit="true" style="height:600px"                   url="<?php print url('fireconfiguration/get/orgaccount/'.$node->nid); ?>" toolbar="#accounttb"                   rownumbers="true" pagination="true">                <thead>                    <tr>                        <th field="name" width="80">姓名</th>                        <th field="role" width="150" align="right">角色</th>                        <th field="login" width="120" align="right">登陆帐号</th>                        <th field="phone" width="150">手机号</th>                        <th field="email" width="150">电子邮件</th>                                           </tr>                </thead>            </table>            <div id="accounttb" style="padding:3px">                <a href="#" class="easyui-linkbutton" plain="true" iconCls="icon-add" onclick="createOrgAccount()">添加账户</a>            </div>                         <div id="editOrgAccoutDialog" style="width: 460px;padding:10px;" class="easyui-dialog" title="添加企业帐户" closed="true" data-options="shadow:false,buttons:'#orgAccountDlg_buttons'">                        <form id="orgAccountForm" method="post">                                    <table class="table03">                                        <tbody>                                            <tr>                                                <td colspan="2" >                                                    <input id="accoutcorp" name="accoutcorp" type="hidden" value="0" />                                                </td>                                            </tr>                                             <tr>                                                <td>电子信箱</td>                                                <td><input  name="email" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td>                                            </tr>                                             <tr>                                                <td>手机号码</td>                                                <td><input  name="cellphone" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td>                                            </tr>                                                                                        <tr>                                                <td>用户角色</td>                                                <td>                                                    <input  name="role" class="set_input_w01 easyui-combobox easyui-validatebox"  data-options="valueField: 'value',                                                    textField: 'label',                                                    data: [{                                                            label: '企业普通用户',                                                            value: '6'                                                    },{                                                            label: '企业消防负责人',                                                            value: '7'                                                    },{                                                            label: '企业消防监督员',                                                            value: '8'                                                    }]" />                                                </td>                                            </tr>                                            <tr>                                                <td>真实姓名</td>                                                <td><input  name="truename" class="set_input_w01 easyui-validatebox"  data-options="required:true" /></td>                                            </tr>                                             <tr>                                                <td>备注</td>                                                <td> <textarea name="desc"  style="width:280px;"  cols="30" rows="10" required="true"></textarea></td>                                            </tr>                                                                                                              </tbody>                                    </table>                        </form>                                            </div>                    <div id="orgAccountDlg_buttons" class="common_btn">                            <a href="javascript:void(0)" class="easyui-linkbutton com_btn" onClick="saveOrgAccount()">保存</a>                            <a href="javascript:void(0)" class="easyui-linkbutton close_btn" onClick="$('#editOrgAccoutDialog').dialog('close')">关闭</a>                        </div>                    <!--editOrgAccoutDialog end-->        </div>            </div></div><script type="text/javascript">    $(function(){       })function formatWaterOperations(value,row,index){    return '<a id="btn" href="javascript:void(0);" class="easyui-linkbutton icon_check" data-options="" onClick="popupQRCodeDetailDlg('+index+');" title="查看"></a>&nbsp;' +            '&nbsp;<a id="btn" href="javascript:void(0);" class="easyui-linkbutton icon_del" data-options="" onClick="deldelWaterAssetDlg('+row.nid+','+index+');" title="删除"></a>';}//新增消防设备function openAddWaterAssetDlg(){ var selectedNode = $("#orgTree").tree('getSelected');  $("#corp").val(selectedNode.attributes.nid);  $('#editWaterAssetDialog').dialog('setTitle','添加消防水系统-'+selectedNode.text).dialog('open');           }//查看设备二维码信息function popupWaterAssetDetailDlg(index){    $("#myWaterAssetForm").form('clear');        $("#QRCodeDg").datagrid('selectRow',index); // 选中当前行        var row = $("#QRCodeDg").datagrid('getSelected'); // 获得当前行的值;        $("#QRCodeID").val(row.name);    //$("#Equment").val('setText',row.belongsOrganization);    //$("#Category").combo('setText',row.belongsCustomer);        $("#myQRCodeForm").form('load',{    // AssetGroupRemark:row.devtypeManufacturer    });        $("#editQrCodeDialog").dialog('setTitle','查看二维码').dialog("open");     /* $("#QRCodeID, #Equment").attr("disabled","disabled");    $("#Category").combobox('disable');    $("#QRCodeDlg_buttons01 .easyui-linkbutton").addClass("play_none");    $("#QRCodeDlg_buttons01 .edit_btn").removeClass("play_none");    */    }//点击编辑设备二维码信息function enableEditAssetGroup(){    $("#checkQrCodeDialog").dialog('setTitle','更新二维码');    $("#QRCodeDlg_buttons01 .easyui-linkbutton").removeClass("play_none");    $("#QRCodeDlg_buttons01 .edit_btn").addClass("play_none");    $("#QRCodeID, #Equment").removeAttr("disabled");    $("#Category").textbox('enable');}//添加一组二维码信息function addOneQRCode(){    $("#QRCodeList li.addBtnBox").before($("#Addbelong li.item").clone(true).addClass("item_add"));}//批量添加二维码信息function addQRCodes(){    for(i=0; i<3; i++){        $("#QRCodeList li.addBtnBox").before($("#Addbelong li.item").clone(true).addClass("item_add"));    }}//单行删除function deldelWaterAssetDlg(val,index){    $.messager.confirm("提示", "您确定要删除这些数据吗？", function (res) {//提示是否删除        if(res){            $("#WaterAssetDg").datagrid('deleteRow',index); // 删除当前行            //请到后台删除            $.post('<?php print url('vpaasassets/ajax/delete/'); ?>'+val, {}, function(result) {                               if (result) {                       $.messager.alert('提示','删除成功!');                   } else {                    $.messager.alert('提示','删除失败!');                }            }, 'json');                    }    });}//批量删除function batchDelWaterAssets(){    var rows = $("#QRCodeDg").datagrid('getChecked') || $("#CloudTerminalDg").datagrid('getSelections');        if(rows == undefined || rows == null || rows == ""){        $.messager.alert('提示','请选择要删除的行!!');        return;    } else {        $.messager.confirm("提示", "您确定要删除这些数据吗？", function (res) {//提示是否删除            if(res){                for(i=0;i<=rows.length;i++){                    //请到后台删除                }                $.messager.alert('提示','删除成功!');            }        });    }}//删除一个水系统设备function delWaterAsset(){    console.log($(this).attr("href"));    $(this).parent(".btnBox").parent("li").remove();}function saveWaterAsset(){        var selectedNode = $("#orgTree").tree('getSelected');        var saveUrl = "vpaasassets/ajax/save/"+selectedNode.id;        $('#myWaterAssetForm').form('submit', {            url: saveUrl,            onSubmit: function() {              //  alert('fail');              //  return $(this).form('validate');            },            success: function(result) {                if (result.errorMsg) {                    $.messager.show({                        title: 'Error',                        msg: result.errorMsg                    });                } else {                    $('#editWaterAssetDialog').dialog('close'); // close the dialog                    $('#WaterAssetDg').datagrid('reload'); // reload the user data                }            }        });}   function reAssocDTU(assetNid, sim){ $.post('<?php print url('/vpaasassets/assocdtu/'); ?>'+ assetNid, {sim:sim}, function(result) {                                    $.messager.alert('提示',result.msg);              }, 'json');}    function assginCloudtToOrg(){   var selectedNode = $("#orgTree").tree('getSelected');   var cloudtSn = $("#cloudtsn").textbox('getValue');   if(cloudtSn == ''){        $.messager.show({                        title: '警告',                        msg: '请选择注册的云终端或者输入云终端的序列号'                    });       return false;   }      $.post('<?php print url('vpaasassets/assoccloudt/'); ?>'+selectedNode.id, {sn:cloudtSn}, function(result) {                               if (result.ok) {                       $.messager.alert('提示','绑定成功!');                  } else {                    $.messager.alert('提示','绑定失败!');                }            }, 'json');}function createOrgAccount(){  var selectedNode = $("#orgTree").tree('getSelected');  $("#accoutcorp").val(selectedNode.attributes.nid);  $('#editOrgAccoutDialog').dialog('setTitle','创建帐号-'+selectedNode.text).dialog('open');         }function saveOrgAccount(){    var selectedNode = $("#orgTree").tree('getSelected');        var saveUrl = "/fireconfiguration/save/orgaccount/"+selectedNode.id;  //defined in fire_configuration        $('#orgAccountForm').form('submit', {            url: saveUrl,            onSubmit: function() {              //  alert('fail');              //  return $(this).form('validate');            },            success: function(result) {                if (result.errorMsg) {                    $.messager.show({                        title: 'Error',                        msg: result.errorMsg                    });                } else {                    $('#editOrgAccoutDialog').dialog('close'); // close the dialog                    $('#accountdg').datagrid('reload'); // reload the user data                }            }        });}    </script>    