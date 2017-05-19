
<!-- see http://echarts.baidu.com/doc/example/line6.html -->
<div id="data-chart-safeindex" style="height:500px"></div>
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
                    'echarts/chart/line' // 使用柱状图就加载bar模块，按需加载
                ],
                function(ec) {
                    // 基于准备好的dom，初始化echarts图表
                    myChart2 = ec.init(document.getElementById('data-chart-safeindex'));
                    // 过渡---------------------
                    myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
                    // ajax callback
                    myChart2.hideLoading();

                    option = {
                        title: {
                            text: '消防巡检分析',
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
                    myChart2.setOption(option);
                }
        );


        function doDrawDataChart() {
            var start = $('#start2').datebox('getValue');	// get datebox value
            var end = $('#end2').datebox('getValue');	// get datebox value
            var asset_nid = $("#seltree2").combo('getValue');
            var asset_text = $("#seltree2").combo('getText');
            var line1_pid = $("#linefilter").combo('getValue');
            var line1_text = $("#linefilter").combo('getText');
             var s=Date.parse(start.replace(/-/g,"/"));
                var e= Date.parse(end.replace(/-/g,"/"));
                if((start!=="")&&(end !== "")){
                    if(s>e){
                        $.messager.alert('错误', '开始日期必须早于结束日期');
                                    return false;

                    }
                }
       
            if (asset_nid == '' || line1_pid == '') {
                $.messager.show({// show error message
                    title: '请选择分析条目项',
                    msg: '请必须选择一个设备，选择需要分析的条目'
                });
            } else {
                myChart2.showLoading({
                    text: '正在努力的读取数据中...', //loading话术
                });

                $.post('/data-kpi/analyse/energy/filter', {start: start, end: end, id: asset_nid, line1: line1_pid}, function(result) {
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
                        //获取Y粥最大值 
                        var maxYNumbers = Math.max.apply(Math, result.p1);
                        
                        //*重新绘制图表
                        option = {
                            title: {
                                text: line1_text+'数据统计分析',
                                subtext: asset_text,
                                x:'center',

                            },
                            tooltip: {
                                trigger: 'axis'
                            },
                            legend: {
                                data: [line1_text],
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
                                    name: line1_text,
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
                                    name: line1_text,
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
                        myChart2.setOption(option);


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