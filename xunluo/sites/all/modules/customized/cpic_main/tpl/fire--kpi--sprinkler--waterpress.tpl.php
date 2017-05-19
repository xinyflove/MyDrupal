
<!-- see http://echarts.baidu.com/doc/example/line6.html -->
<div class="easyui-layout" data-options="fit:true">
    <div class="maintop" data-options="region:'north',border:false">
        <div class="main_header">
            <form id="daQueryForm" method="post">
                <input id="daOrgType" type="hidden" name="orgType" value="device"/>
                <input id="daDevID" type="hidden" name="devID" value="0"/>


                <div class="formTable">
                    <div style="width:100%; height:50px; line-height:50px; text-align:right; font-size:13px; color:#292f34;">
                            <div style=" margin-right:4%; float:right;">
                                <span style="margin-right:5px">起止时间</span>
                                <input class="easyui-datebox" id="querystarttime"  name="querystart" data-options="required:true,showSeconds:false"  style="width:150px">
                                <span>--------</span>
                                <input class="easyui-datebox" id="queryendtime" name="queryend" data-options="required:true,showSeconds:false"  style="width:150px">
                            </div>
                    </div> 
                    <div style="width:96%; height:50px; line-height:50px; text-align:right;">
                        <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:80"  onclick="doDrawDataChart()">查询</a>
                        <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="resetForm('daQueryForm')">重置</a>
                        <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="da_export2file">导出</a>
                    </div>
                </div>
                <!--<table class="formTable">
                    <tr>
                        
               <td>起止时间</td>
               <td>   
                <input class="easyui-datebox" id="querystarttime"  name="querystart"
                data-options="required:true,showSeconds:false"  style="width:150px">
            </td>
            <td>--------</td>
            <td>   
                <input class="easyui-datebox" id="queryendtime" name="queryend"
                data-options="required:true,showSeconds:false"  style="width:150px">
            </td>
        </tr>
        <tr>
            <td></td>
            <td> </td>
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td></td>
            <td></td>
            <td colspan="2">
                <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="doDrawDataChart()">查询</a>
                <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="resetForm('daQueryForm')">重置</a>
                <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="da_export2file">导出</a>
            </td>
        </tr>
    </table>-->
</form>
</div>

</div>
<!--main_header end-->
<div class="main_data" data-options="region:'center',border:false">
    <div class="resultBox">
        <div class="header">

            <div class="switch-wrapper">
                <!--  <a id="drawChartBtn" href="#" class="easyui-linkbutton" data-options="width:60,selected:true,toggle:true,group:'switch'" onclick="switchDrawChart()">折线图</a> -->
                <!--   <a id="drawTableBtn" href="#" class="easyui-linkbutton" data-options="width:60,toggle:true,group:'switch'" onclick="switchDrawTable()">列表</a> -->
            </div>
        </div>      
        <div class="result-main">
            <div id="data-chart-shrinkler" style="height:500px;"></div>

        </div>
    </div>
</div>
</div>

<script src="<?php print $dev; ?>build/dist/echarts.js"></script>
<script type="text/javascript">
        var myChart2;

        // 路径配置
        require.config({
            paths: {
                echarts: '<?php print $dev; ?>/build/dist'
            }
        });
        // 使用
        require(
                [
                    'echarts',
                    'echarts/chart/pie' // 使用柱状图就加载bar模块，按需加载
                ],
                function(ec) {
                    // 基于准备好的dom，初始化echarts图表
                    myChart2 = ec.init(document.getElementById('data-chart-shrinkler'));
                    // 过渡---------------------
                    myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
                    // ajax callback
                    myChart2.hideLoading();

                    option = {
    title : {
        text: '<?php print $node->title; ?>喷淋系统水压异常',
        x:'center'
    },
    tooltip : {
        trigger: 'item',
        formatter: "{a} <br/>{b} : {c} ({d}%)"
    },
    legend: {
        orient : 'vertical',
        x : 'left',
        data:['异常','正常']
    },
    toolbox: {
        show : true,
        feature : {
            mark : {show: true},
            dataView : {show: true, readOnly: false},
            magicType : {
                show: true, 
                type: ['pie', 'funnel'],
                option: {
                    funnel: {
                        x: '25%',
                        width: '50%',
                        funnelAlign: 'left',
                        max: 1548
                    }
                }
            },
            restore : {show: true},
            saveAsImage : {show: true}
        }
    },
    calculable : true,
    series : [
        {
            name:'喷淋系统水压状态',
            type:'pie',
            radius : '55%',
            center: ['50%', '60%'],
            data:[
                {value:<?php print $xdata; ?>, name:'异常'},
                {value:<?php print $ydata; ?>, name:'正常'},
                
            ]
        }
    ]
};
                    

                    // 为echarts对象加载数据 
                    myChart2.setOption(option);
                }
        );


function doDrawDataChart() {
            var start = $('#querystarttime').datetimebox('getValue');   // get datebox value
            var end = $('#queryendtime').datetimebox('getValue');   // get datebox value
            var asset_nid = <?php print $node->nid; ?>;
           
            var curTab = $("#nav-tabs").tabs('getSelected');
            var selectedNode = $("#orgTree").tree('getSelected');
            if(selectedNode == null){
                $.messager.show({
                    title: '提示',
                    msg: "请至少选择一家企业进行查看"
                });
                return false; 
            }


            var s=Date.parse(start.replace(/-/g,"/"));
            var e= Date.parse(end.replace(/-/g,"/"));
            if((start!=="")&&(end !== "")){
                if(s>e){
                    $.messager.alert('错误', '开始日期必须早于结束日期');
                    return false;

                }
            }

            if (asset_nid == '') {
                $.messager.show({// show error message
                    title: '请选择分析条目项',
                    msg: '请必须选择一个分析条目'
                });
            } else {

                    myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
              

                   
                    $.post('/kpi/dataanalyse/sprinkler/<?php print $node->nid; ?>', {start: start, end: end, id: <?php print $node->nid; ?>}, function(result) {
                        if (result.errorMsg) {
                            myChart2.hideLoading();
                        $.messager.show({// show error message
                            title: '友情提示',
                            msg: result.errorMsg
                        });
                    } else {
                        if(!(result.p1)){  // 如果数据为空
                            myChart2.hideLoading();
                            $.messager.alert('友情提示', "未查询到任何数据");
                            return false; 
                        }
                        //获取Y粥最大值 
                        var maxYNumbers = Math.max.apply(Math, result.p1);
                        //*重新绘制图表
                         option1 = {
                            title : {
                               text: '<?php print $node->title; ?>喷淋系统水压状态',
                                subtext: start+'-'+end,
                                x:'center'
                            },
                            tooltip : {
                                trigger: 'item',
                                formatter: "{a} <br/>{b} : {c} ({d}%)"
                            },
                            legend: {
                                orient : 'vertical',
                                x : 'left',
                                data:['正常','异常']
                            },
                            toolbox: {
                                show : true,
                                feature : {
                                    mark : {show: true},
                                    dataView : {show: true, readOnly: false},
                                    magicType : {
                                        show: true, 
                                        type: ['pie', 'funnel'],
                                        option: {
                                            funnel: {
                                                x: '25%',
                                                width: '50%',
                                                funnelAlign: 'left',
                                                max: 1548
                                            }
                                        }
                                    },
                                    restore : {show: true},
                                    saveAsImage : {show: true}
                                }
                            },
                            calculable : true,
                            series : [
                            {
                                name:'喷淋系统状态',
                                type:'pie',
                                radius : '55%',
                                center: ['50%', '60%'],
                                data:result.p1
                            }
                            ]
                        };

                        // 为echarts对象加载数据 
                        myChart2.setOption(option1);
                        //重新绘制完成

                        myChart2.hideLoading();

                    }
                }, 'json');

        }

}
        
        function exportData2file(){
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