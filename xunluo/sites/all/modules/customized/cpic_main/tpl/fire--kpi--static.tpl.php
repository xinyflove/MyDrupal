
<!-- see http://echarts.baidu.com/doc/example/line6.html -->

<div class="easyui-layout" data-options="fit:true">
    <div class="maintop" data-options="region:'north',border:false">
        <div class="main_header">
            <form id="daQueryForm" method="post">
                <input id="daOrgType" type="hidden" name="orgType" value="device"/>
                <input id="daDevID" type="hidden" name="devID" value="0"/>
                

                
             
                <div class="formTable">
                    <div style="width:100%; height:50px; line-height:50px; font-size:13px; color:#292f34;">
                        <div style="margin-left:5%; float:left;">
                            <span style="margin-right:5px;">查询指标</span>
                            <select id="queryIndexCC" class="easyui-combobox" name="queryIndex" style="width:240px;" data-options="
                               valueField : 'value',
                               textField: 'label',
                               onSelect:function(rec){
                                           var url = '/kpi/ajax/datalevel/'+rec.value;
                                            $('#datalevel').combobox('reload', url);
                               }">
                               <option value="1" selected>消防巡检率</option>
                               <option value="2">控制值班室脱岗时间</option>
                               <option value="3">消防车道占用时间</option>
                               <option value="4">消火栓系统水压状态</option>
                               <option value="5">喷淋系统水压状态</option>
                               <option value="6">消防水箱水位状态</option>
                               <option value="7">消防水池水位状态</option>
                               <option value="8">消防安全评估</option>
                           </select>
                        </div>
                        <div style="margin-left:4%; float:left; vertical-align:middle">
                            <span style="margin-right:5px">分阶</span>
                            <input id="datalevel" value=1 class="easyui-combobox" style="width:240px;" name="level"
                                data-options="
                                valueField:'id',
                                textField:'text',
                                data:[
                                {'id':1,
                                'text':'全部'
                                },
                                {'id':1,
                                'text':'巡检率达到80%以上单位'
                                },
                                {'id':1,
                                'text':'巡检率未达到80%以上单位'
                                }
                                
                                ]
                                ">
                        </div>
                        <div style="margin-left:4%; float:left; vertical-align:middle">
                            <span style="margin-right:5px">起止时间</span>
                            <input class="easyui-datetimebox" id="querystarttime" name="queryend"
                data-options="required:true,showSeconds:false" value="3/4/2010 2:3" style="width:150px">
                            <span>--------</span>
                            <input class="easyui-datetimebox" id="queryendtime" name="queryend"
                data-options="required:true,showSeconds:false" value="3/4/2010 2:3" style="width:150px">
                        </div>
                    </div>
                    <div style="width:97%; height:50px; line-height:50px; text-align:right;">
                        <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="doKpiStatic()">查询</a>
                        <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="resetForm('daQueryForm')">重置</a>
                        <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="da_export2file">导出</a>
                    </div>
                </div>
<!--
                <table class="formTable">
                    <tr>
                        <td>查询指标</td>
                        <td>   
                           <select id="queryIndexCC" class="easyui-combobox" name="queryIndex" style="width:260px;" data-options="
                           valueField : 'value',
                           textField: 'label',
                           deltaY:30,
                           onSelect:function(rec){
                                       var url = '/kpi/ajax/datalevel/'+rec.value;
                                        $('#datalevel').combobox('reload', url);
                       }">
                       <option value="1" selected>消防巡检率</option>
                       <option value="2">控制值班室脱岗时间</option>
                       <option value="3">消防车道占用时间</option>
                       <option value="4">消火栓系统水压状态</option>
                       <option value="5">喷淋系统水压状态</option>
                       <option value="6">消防水箱水位状态</option>
                       <option value="7">消防水池水位状态</option>
                       <option value="8">消防安全评估</option>
                   </select>
                     </td>
                    <td></td>
                    <td></td>
                    <td>分阶</td>
                    <td>    
                        <input id="datalevel" value=1 class="easyui-combobox" style="width:260px;" name="level"
                            data-options="
                            valueField:'id',
                            textField:'text',
                            
                            data:[
                            {'id':1,
                            'text':'全部'
                            },
                            {'id':1,
                            'text':'巡检率达到80%以上单位'
                            },
                            {'id':1,
                            'text':'巡检率未达到80%以上单位'
                            }
                            
                            ]
                            ">
                    </td>
            
        </tr>
        <tr>
            <td></td>
            <td></td>
            <td>起止时间</td>
            <td>   
                <input class="easyui-datetimebox" id="querystarttime"  name="querystart"
                data-options="required:true,showSeconds:false" value="3/4/2010 2:3" style="width:150px">
            </td>
            <td>--------</td>
            <td>   
                <input class="easyui-datetimebox" id="queryendtime" name="queryend"
                data-options="required:true,showSeconds:false" value="3/4/2010 2:3" style="width:150px">
            </td>
        </tr>
        <tr>
            <td></td>
            <td> 
            </td>
            <td></td>
            <td>   

            </td>
            <td colspan="2">
                <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:100" onclick="doKpiStatic()">查询</a>
                <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:100" onclick="resetForm('daQueryForm')">重置</a>
                <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:100" onclick="da_export2file">导出</a>
            </td>
        </tr>
    </table>
-->


</form>
</div>

</div>
<!--main_header end-->
<div class="main_data" data-options="region:'center',border:false">
    <div class="resultBox">
        <div class="header">

            <div class="switch-wrapper">
                <a id="drawChartBtn" href="#" class="easyui-linkbutton" data-options="width:60,selected:true,toggle:true,group:'switch'" onclick="switchDrawTable()">列表</a>
                <a id="drawTableBtn" href="#" class="easyui-linkbutton" data-options="width:60,toggle:true,group:'switch'" onclick="switchDrawMap()">地图</a>
            </div>
        </div>      
        <div class="result-main">
            <div id="table-list">
                <table id="static-dg"></table>
            </div>
            <div id="map-list" style="display:none">
             <div id="map-container" style="width:100%; height:600px;" class="gis-map">这是地图显示的区域。。。</div>
            </div>
        </div>
    </div>
</div>
</div>
<script type="text/javascript">
function switchDrawTable(){
    $("#table-list").show();
    $("#map-list").hide();
}

function switchDrawMap(){
    $("#table-list").hide();
    var map = new BMap.Map("map-container");
     map.setCurrentCity("济南");
            //    var point = new BMap.Point(120.420127,36.104052);
            var point = new BMap.Point(116.998521,36.676765);

            map.centerAndZoom(point, 12);
            map.addControl(new BMap.NavigationControl());  //添加默认缩放平移控件
            map.enableScrollWheelZoom();


    $("#map-list").show();
}


function doKpiStatic() {
            var start = $('#querystarttime').datetimebox('getValue');	// get datebox value
            var end = $('#queryendtime').datetimebox('getValue');	// get datebox value
            var asset_nid = 13;
            var index = $("#queryIndexCC").combobox('getValue'); 
            var indexText = $("#queryIndexCC").combobox('getText'); 
            var level = $("#datalevel").combobox('getValue'); 
            var levelText = $("#datalevel").combobox('getText'); 
            
            var type = 'corp';
            var id = 0;
            var curTab = $("#nav-tabs").tabs('getSelected');
            var selectedNode = $("#orgTree").tree('getSelected');
            if(selectedNode == null){
                $.messager.show({
                    title: '提示',
                    msg: "请至少选择一个范围进行查看"
                });
                return false; 
            }else{
                type = selectedNode.attributes.type;
                id=selectedNode.attributes.nid;
            }
            var s=Date.parse(start.replace(/-/g,"/"));
            var e= Date.parse(end.replace(/-/g,"/"));
            
            if((start!=="")&&(end !== "")){
                if(s>e){
                    $.messager.alert('错误', '开始日期必须早于结束日期');
                    return false;

                }
            }

            if (level == '' || index == '') {
                $.messager.show({// show error message
                    title: '请选择分析条目项',
                    msg: '请必须选择一个分析条目'
                });
            } else {
                            
                    if(index == 1){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'rate',title:'巡检率',width:100,align:'right'}
                            ]]
                        });
                    }
                    if(index == 2){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'ctrlroom_offtime',title:'脱岗时间',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                    if(index == 3){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'firelane_occptime',title:'消防通道占用时间',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                     if(index == 4){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'hydrant_waterpress',title:'消火栓系统水压状态',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                     if(index == 5){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'sprinkler_waterpress',title:'喷淋系统水压状态',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                     if(index == 6){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'box_waterlevel',title:'消防水箱系统水位状态',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                     if(index == 7){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'pool_waterlevel',title:'消防水池水位状态',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                     if(index == 8){
                    
                            $('#static-dg').datagrid({
                            url:'/kpi/staticanalyse/'+type+'/'+id,
                            queryParams:{
                                start:start,
                                end: end,
                                id: id,
                                level:level,
                                item:index
                            },
                            columns:[[
                                {field:'id',title:'企业编号',width:100},
                                {field:'name',title:'企业名称',width:200},
                                {field:'year',title:'年份',width:100},
                                {field:'month',title:'月份',width:100},
                                {field:'safeindex',title:'消防安全评估',width:100,align:'right'}
                            ]]
                        });
                    }
                    
                    
                    
    
               /*   $.post('/kpi/staticanalyse/'+type+'/'+id, {start: start, end: end, id: id, level:level, item: index}, function(result) {
                        if (result.errorMsg) {
                        $.messager.show({// show error message
                            title: '友情提示',
                            msg: result.errorMsg
                        });
                    } else {
                    
                    }

            }); */
        }

}

function da_export2file(){
    var asset=$('#seltree2').combo('getValue');
        var start = $('#start2').datebox('getValue');	// get datebox value
        var end = $('#end2').datebox('getValue');	// get datebox value
        var p1 =  $('#linefilter').combo('getValue');    
        var s=Date.parse(start.replace(/-/g,"/"));
        var e= Date.parse(end.replace(/-/g,"/"));
        if((start!=="")&&(end !== "")){
            if(s>e){
                $.messager.alert('错误', '开始日期必须早于结束日期');
                return false;

            }
        }

        if(asset == ''|| p1==''){
            $.messager.show({// show error message
                title: '错误',
                msg: '请先选择一个设备'
            });
            return false;
        }else{
            window.location.href='m2m/excel/export/data?as='+asset+'&s='+start+'&e='+end+'&p1='+p1;
        }
    }
    
    </script>
    <script type="text/javascript" src="http://api.map.baidu.com/api?v=2.0&amp;ak=66lx08pkMGCxEhAMGGlGHH1j"></script>
