
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
                            <select id="queryIndexCC" class="easyui-combobox" name="queryIndex" style="width:260px;" data-options="
                           valueField : 'value',
                           textField: 'label',
                           onSelect:function(rec){

                       }">
                            <option value="1">周期内消防巡检率</option>
                            <option value="2">周期内控制值班室脱岗次数</option>
                            <option value="3">周期内消防车道占用次数</option>
                            <option value="4">周期内消火栓系统水压状态</option>
                            <option value="5">周期内喷淋系统水压状态</option>
                            <option value="6">周期内消防水箱系统水位状态</option>
                            <option value="7">周期内消防水池水位状态</option>
                            </select>
                        </div>
                        
                        <div style="margin-left:4%; float:left; vertical-align:middle">
                            <span style="margin-right:5px">起止时间</span>
                            <input class="easyui-datetimebox" id="querystarttime"  name="querystart"
                data-options="required:true,showSeconds:false" value="3/4/2010 2:3" style="width:150px">
                            <span>--------</span>
                            <input class="easyui-datetimebox" id="queryendtime" name="queryend"
                data-options="required:true,showSeconds:false" value="3/4/2010 2:3" style="width:150px">
                        </div>
                    </div>
                    <div style="width:97%; height:50px; line-height:50px; text-align:right;">
                         <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="doDrawDataChart()">查询</a>
                <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:80"  onclick="resetForm('daQueryForm')">重置</a>
                <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:80"  onclick="da_export2file">导出</a>
                    </div>
                </div>
                <!--<table class="formTable">
                    <tr>
                        <td>查询指标</td>
                        <td>   
                           <select id="queryIndexCC" class="easyui-combobox" name="queryIndex" style="width:260px;" data-options="
                           valueField : 'value',
                           textField: 'label',
                           onSelect:function(rec){

                       }">
                       <option value="1">周期内消防巡检率</option>
                       <option value="2">周期内控制值班室脱岗次数</option>
                       <option value="3">周期内消防车道占用次数</option>
                       <option value="4">周期内消火栓系统水压状态</option>
                       <option value="5">周期内喷淋系统水压状态</option>
                       <option value="6">周期内消防水箱系统水位状态</option>
                       <option value="7">周期内消防水池水位状态</option>
                   </select>
               </td>
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
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td></td>
            <td> 
            </td>
            <td></td>
            <td>   

            </td>
            <td colspan="2">
                <a id="queryBtn" href="#" class="easyui-linkbutton" data-options="width:80" onclick="doDrawDataChart()">查询</a>
                <a id="resetBtn" href="#" class="easyui-linkbutton" data-options="width:80"  onclick="resetForm('daQueryForm')">重置</a>
                <a id="exportBtn" href="#" class="easyui-linkbutton" data-options="width:80"  onclick="da_export2file">导出</a>
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
                <a id="drawChartBtn" href="#" class="easyui-linkbutton" data-options="width:60,selected:true,toggle:true,group:'switch'" onclick="switchDrawChart()">曲线图</a>
                <!--   <a id="drawTableBtn" href="#" class="easyui-linkbutton" data-options="width:60,toggle:true,group:'switch'" onclick="switchDrawTable()">列表</a> -->
            </div>
        </div>      
        <div class="result-main">
            <div id="main-chart-line" style="height:500px; display:none;"></div>
            <div id="main-chart-pie" style="height:500px; "></div>

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
                    'echarts/chart/line' , // 使用柱状图就加载bar模块，按需加载
                    'echarts/chart/pie' // 使用柱状图就加载bar模块，按需加载
                    ],
                    function(ec) {
                    // 基于准备好的dom，初始化echarts图表
                    myChart1 = ec.init(document.getElementById('main-chart-line'));
                    // 过渡---------------------
                    myChart1.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
                    // ajax callback
                    myChart1.hideLoading();

                    option1 = {
                        title: {
                            text: '消防大数据分析',
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
                                restore: {show: true},
                                saveAsImage: {show: true}
                            }
                        },
                        dataZoom: {
                            show: true,
                            realtime: true,
                            start: 0,
                            end: 100,
                            y: 490
                        },
                        calculable: true,
                        xAxis: [
                        {
                            type: 'category',
                            boundaryGap: false,
                            data: ['1', '2', '3', '4', '5', '6', '7']
                        }
                        ],
                        yAxis: [
                        {
                            name: '立方/分钟',
                            position: 'left',
                            type: 'value',
                                axisLine: {// 轴线
                                    show: true,
                                    lineStyle: {
                                        color: '＃f27979',
                                        type: 'dashed',
                                        width: 2
                                    }
                                },
                            },
                            
                            ],
                            series: [
                            {
                                name: '数据条目',
                                type: 'line',
                                data: [0, 0, 0, 0, 0, 0, 0],
                                markPoint: {
                                    data: [
                                    {type: 'max', name: '最大值'},
                                    {type: 'min', name: '最小值'}
                                    ]
                                },

                            },
                            
                            ]
                        };

                    // 为echarts对象加载数据 
                    myChart1.setOption(option1);


                    myChart2 = ec.init(document.getElementById('main-chart-pie'));
                    // 过渡---------------------
                    myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
                    // ajax callback
                    myChart2.hideLoading();

                     option2 = {
                        title : {
                            text: '消防大数据分析',
                            subtext: '',
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
                            name:'访问来源',
                            type:'pie',
                            radius : '55%',
                            center: ['50%', '60%'],
                            data:[
                            {value:335, name:'正常'},
                            {value:310, name:'异常'},
                           
                            ]
                        }
                        ]
                    };

                    // 为echarts对象加载数据 
                    myChart2.setOption(option2);



                }
                );


function doDrawDataChart() {
            var start = $('#querystarttime').datetimebox('getValue');	// get datebox value
            var end = $('#queryendtime').datetimebox('getValue');	// get datebox value
            var asset_nid = 13;
            var index = $("#queryIndexCC").combobox('getValue'); 
            var indexText = $("#queryIndexCC").combobox('getText'); 
           
            var curTab = $("#nav-tabs").tabs('getSelected');
            var selectedNode = $("#orgTree").tree('getSelected');
            if(selectedNode == null){
                $.messager.show({
                    title: '提示',
                    msg: "请至少选择一家企业进行查看"
                });
                return false; 
            }

            console.log(index);

            var s=Date.parse(start.replace(/-/g,"/"));
            var e= Date.parse(end.replace(/-/g,"/"));
            if((start!=="")&&(end !== "")){
                if(s>e){
                    $.messager.alert('错误', '开始日期必须早于结束日期');
                    return false;

                }
            }

            if (asset_nid == '' || index == '') {
                $.messager.show({// show error message
                    title: '请选择分析条目项',
                    msg: '请必须选择一个分析条目'
                });
            } else {
                  if(index <4) {  //折线图
                        $("#main-chart-line").show();
                        $("#main-chart-pie").hide();

                    myChart1.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
              

                   
                    $.post('/kpi/dataanalyse/<?php print $node->nid; ?>', {start: start, end: end, id: asset_nid, item: index}, function(result) {
                        if (result.errorMsg) {
                            myChart1.hideLoading();
                        $.messager.show({// show error message
                            title: '友情提示',
                            msg: result.errorMsg
                        });
                    } else {
                        if(!(result.p1 || result.p2)){  // 如果数据为空
                            myChart1.hideLoading();
                            $.messager.alert('友情提示', "未查询到任何数据");
                            return false; 
                        }
                        //获取Y粥最大值 
                        var maxYNumbers = Math.max.apply(Math, result.p1);
                        alert(indexText);
                        //*重新绘制图表
                        option2 = {
                            title: {
                                text: indexText+'数据统计分析',
                                subtext: indexText,
                                x:'center',

                            },
                            tooltip: {
                                trigger: 'axis'
                            },
                            legend: {
                                data: [indexText],
                                x: 'left'
                            },
                            toolbox: {
                                show: true,
                                feature: {
                                    mark: {show: true},
                                    dataView: {show: true, readOnly: false},
                                    restore: {show: true},
                                    saveAsImage: {show: true}
                                }
                            },
                            dataZoom: {
                                show: true,
                                realtime: true,
                                start: 10,
                                end: 20,
                                y: 480
                            },
                            grid:{
                              y2:125  
                          },
                          calculable: true,
                          xAxis: [
                          {
                            type:'category',
                            axisLabel:{'rotate':90},
                            boundaryGap: false,
                            data: result.created,
                        }
                        ],
                        yAxis: [
                        {
                            name: index,
                            position: 'left',
                            type: 'value',
                                    axisLine: {// 轴线
                                        show: true,
                                        lineStyle: {
                                            color: '#1a9a09',
                                            type: 'dashed',
                                            width: 1
                                        }
                                    },
                                    min: "0",
                                //    max:maxYNumbers*1.3,
                            },
                            ],
                            series: [
                            {
                                name: index,
                                type: 'line',
                                smooth:true,
                                itemStyle:{
                                   normal: {
                                            color:"#1a9a09",  //绿色
                                            lineStyle: {
                                            }
                                        }
                                    },
                                    data: result.p1,
                                    
                                    
                                }
                                
                                ],
                            };

                        // 为echarts对象加载数据 
                        myChart1.setOption(option2);
                        //重新绘制完成

                        myChart1.hideLoading();

                    }
                }, 'json');

}else{

    $("#main-chart-line").hide();
    $("#main-chart-pie").show();
     myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
              
    $.post('/kpi/dataanalyse/<?php print $node->nid; ?>', {start: start, end: end, id: asset_nid, index: index}, function(result) {
        if (result.errorMsg) {
                     myChart2.hideLoading();
                        $.messager.show({// show error message
                            title: '友情提示',
                            msg: result.errorMsg
                        });
                    } else {
                        if(!(result.p1 || result.p2)){  // 如果数据为空
                            myChart2.hideLoading();
                            $.messager.alert('友情提示', "未查询到任何数据");
                            return false; 
                        }
                        alert('ok pie');
                        //获取Y粥最大值 
                        var maxYNumbers = Math.max.apply(Math, result.p1);
                        
                        //*重新绘制图表
                        option2 = {
                            title : {
                                text: indexText,
                                subtext: indexText,
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
                                name:indexText,
                                type:'pie',
                                radius : '55%',
                                center: ['50%', '60%'],
                                data:[
                                {value:335, name:'正常'},
                                {value:310, name:'异常'},
                                
                                ]
                            }
                            ]
                        };


                        // 为echarts对象加载数据 
                        myChart2.setOption(option2);


                        //重新绘制完成

                        myChart2.hideLoading();

                    }
                }, 'json');

}

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