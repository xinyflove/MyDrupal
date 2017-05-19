
<!-- see http://echarts.baidu.com/doc/example/line6.html -->
<div class="easyui-layout" data-options="fit:true">
    <div class="maintop" data-options="region:'north',border:false">
        <div class="main_header">
            <form id="daQueryForm" method="post">
                <input id="daOrgType" type="hidden" name="orgType" value="device"/>
                <input id="daDevID" type="hidden" name="devID" value="0"/>

                <table class="formTable">
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
                            <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:100" onclick="doDrawDataChart()">查询</a>
                            <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:100" onclick="resetForm('daQueryForm')">重置</a>
                            <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:100" onclick="da_export2file">导出</a>
                        </td>
                    </tr>
                </table>
            </form>
        </div>

    </div>
    <!--main_header end-->
    <div class="main_data" data-options="region:'center',border:false">
        <div class="resultBox">
            <div class="header">

                <div class="switch-wrapper">
                     <a id="drawChartBtn" href="#" class="easyui-linkbutton" data-options="width:60,selected:true,toggle:true,group:'switch'" onclick="switchDrawChart()">折线图</a>
                      <a id="drawTableBtn" href="#" class="easyui-linkbutton" data-options="width:60,toggle:true,group:'switch'" onclick="switchDrawTable()">列表</a>
                </div>
            </div>      
            <div class="result-main">
                <div id="data-chart-inspect" style="height:500px;"></div>

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
                    'echarts/chart/bar' // 使用柱状图就加载bar模块，按需加载
                ],
                function(ec) {
                    // 基于准备好的dom，初始化echarts图表
                    myChart2 = ec.init(document.getElementById('data-chart-inspect'));
                    // 过渡---------------------
                    myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
                    // ajax callback
                    myChart2.hideLoading();

                    option = {
                            title : {
                                text: '消火栓系统水压状态',
                                subtext: '<?php print $node->title; ?>',
                                x:'center',

                            },
                            tooltip : {
                                trigger: 'axis'
                            },
                            legend: {
                                data:<?php print $legend; ?>,
                                x:'left',

                            },
                            toolbox: {
                                show : true,
                                feature : {
                                    mark : {show: true},
                                    dataView : {show: true, readOnly: false},
                                    magicType : {show: true, type: ['line', 'bar']},
                                    restore : {show: true},
                                    saveAsImage : {show: true}
                                }
                            },
                            calculable : true,
                            xAxis : [
                                {
                                    type : 'category',
                                    data : <?php print $xdata; ?>
                                }
                            ],
                            yAxis : [
                                {
                                    type : 'value'
                                }
                            ],
                            series : <?php print $series; ?>,
                        };


                    // 为echarts对象加载数据 
                    myChart2.setOption(option);
                }
        );


        function doDrawDataChart() {
            var start = $('#querystarttime').datetimebox('getValue');   // get datebox value
            var end = $('#queryendtime').datetimebox('getValue');   // get datebox value
            var asset_nid = 1;

            var curTab = $("#nav-tabs").tabs('getSelected');
            var checkedNodes = $('#checkedOrgTree').tree('getChecked');
             var type = 'corp';
             
            if(checkedNodes == null){
                $.messager.show({
                                title: '提示',
                                msg: "请至少选择2至4家企业进行查看"
                            });
                return false; 
            }

            if(checkedNodes.length < 2 || checkedNodes.length >4 ){
                        $.messager.show({
                                title: '提示',
                                msg: "请选择2至4家企业进行查看"
                            });
                return false; 
            }
            var checkNids= [];

            for(var i=0; i<checkedNodes.length; i++){
                checkNids.push(checkedNodes[i].attributes.nid);
                type = checkedNodes[i].attributes.type;
            }


            var s = Date.parse(start.replace(/-/g, "/"));
            var e = Date.parse(end.replace(/-/g, "/"));
            if ((start !== "") && (end !== "")) {
                if (s > e) {
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



                $.post('/kpi/compareanalyse/hydrant/'+type+'/'+checkNids.join('-'), {start: start, end: end, id:checkNids.join('-')}, function(result) {
                    if (result.errorMsg) {
                        myChart2.hideLoading();
                        $.messager.show({// show error message
                            title: '友情提示',
                            msg: result.errorMsg
                        });
                    } else {
                        if (!(result.created)) {  // 如果数据为空
                            myChart2.hideLoading();
                            $.messager.alert('友情提示', "未查询到任何数据");
                            return false;
                        }
                        //获取Y粥最大值 
                        var maxYNumbers = Math.max.apply(Math, result.p1);
                        //*重新绘制图表
                    option1 = {
                        title: {
                            text: '控制室值班脱岗次数对比',
                            subtext:result.subtitle,
                            x:'center',
                        },
                        tooltip: {
                            trigger: 'axis'
                        },
                        toolbox: {
                            show: true,
                            feature: {
                                mark: {show: true},
                                dataView: {show: true, readOnly: false},
                                magicType: {show: true, type: ['bar']},
                                restore: {show: true},
                                saveAsImage: {show: true}
                            }
                        },
                        calculable: true,
                        xAxis: [
                            {
                                type: 'category',
                                data: result.created
                            }
                        ],
                        yAxis: [
                            {
                                type: 'value'
                            }
                        ],
                        series: result.series,

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