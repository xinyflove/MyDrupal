
(function($){



})(jQuery);


//开机操作

function devicePowerOn(deviceId){
	$.messager.confirm('提示', '确定要进行开机操作么?', function(r){
		if (r){
			// exit action;

			$.messager.show({
				title:'系统提示',
				msg:'开机命令已经发出.',
				timeout:2000,
				showType:'slide'
			});

		}
});
}

//关机操作
function devicePowerOff(deviceId){
	$.messager.confirm('提示', '确定要进行关机操作么?', function(r){
		if (r){
			// exit action;

			$.messager.show({
				title:'系统提示',
				msg:'关机命令已经发出.',
				timeout:2000,
				showType:'slide'
			});
		}
	});
}

//更多操作

function openControlMoreDialog(deviceId){
	$('#deviceMoreControlDialog').dialog('open')
}

//具体的更多操纵方法，opId, 是操作的具体对应id，一般是对应到action
function deviceControlMoreOp(opId){
	$.messager.confirm('提示', '确定要进行此项操作么?', function(r){
		if (r){
			// exit action;

			$.messager.show({
				title:'系统提示',
				msg:'命令'+opId+'已经发出.',
				timeout:2000,
				showType:'slide'
			});
		}
	});
}

// 初始化仪表盘字段
function initDefaultChart(ec){
	for(var i=1; i<9; i++){

		var myChart = ec.init(document.getElementById('attr-chart-'+i));
            var   option = {
					    tooltip : {
					        formatter: "{a} <br/>{b} : {c}%"
					    },
					    toolbox: {
					        show : false,
					        feature : {
					            mark : {show: true},
					            restore : {show: true},
					            saveAsImage : {show: true}
					        }
					    },
					    series : [
					        {
					            name:'温度',
					            type:'gauge',
					            splitNumber: 10,       // 分割段数，默认为5
					            axisLine: {            // 坐标轴线
					                lineStyle: {       // 属性lineStyle控制线条样式
					                    color: [[0.2, '#228b22'],[0.8, '#48b'],[1, '#ff4500']], 
					                    width: 3
					                }
					            },
					            axisTick: {            // 坐标轴小标记
					                splitNumber: 10,   // 每份split细分多少段
					                length :10,        // 属性length控制线长
					                lineStyle: {       // 属性lineStyle控制线条样式
					                    color: 'auto'
					                }
					            },
					            axisLabel: {           // 坐标轴文本标签，详见axis.axisLabel
					                textStyle: {       // 其余属性默认使用全局文本样式，详见TEXTSTYLE
					                    color: 'auto'
					                }
					            },
					            splitLine: {           // 分隔线
					                show: true,        // 默认显示，属性show控制显示与否
					                length :15,         // 属性length控制线长
					                lineStyle: {       // 属性lineStyle（详见lineStyle）控制线条样式
					                    color: 'auto'
					                }
					            },
					            pointer : {
					                width : 5
					            },
					            title : {
					                show : true,
					                offsetCenter: [0, '-40%'],       // x, y，单位px
					                textStyle: {       // 其余属性默认使用全局文本样式，详见TEXTSTYLE
					                    fontWeight: 'bolder'
					                }
					            },
					            detail : {
					                formatter:'{value}%',
					                textStyle: {       // 其余属性默认使用全局文本样式，详见TEXTSTYLE
					                    color: 'auto',
					                    fontWeight: 'bolder'
					                }
					            },
					            data:[{value: 50, name: '完成率'}]
					        }
					    ]
					};
            myChart.setOption(option);

	}
}

function initDefaultChart01(ec){
	for(var i=1; i<5; i++){
			var myChart = ec.init(document.getElementById('attr-chart01-'+i));
            var   option = {
					    tooltip : {
					        formatter: "{a} <br/>{b} : {c}%"
					    },
					    toolbox: {
					        show : false,
					        feature : {
					            mark : {show: true},
					            restore : {show: true},
					            saveAsImage : {show: true}
					        }
					    },
					    series : [
					        {
					            name:'温度',
					            type:'gauge',
					            splitNumber: 10,       // 分割段数，默认为5
					            axisLine: {            // 坐标轴线
					                lineStyle: {       // 属性lineStyle控制线条样式
					                    color: [[0.2, '#228b22'],[0.8, '#48b'],[1, '#ff4500']], 
					                    width: 3
					                }
					            },
					            axisTick: {            // 坐标轴小标记
					                splitNumber: 10,   // 每份split细分多少段
					                length :10,        // 属性length控制线长
					                lineStyle: {       // 属性lineStyle控制线条样式
					                    color: 'auto'
					                }
					            },
					            axisLabel: {           // 坐标轴文本标签，详见axis.axisLabel
					                textStyle: {       // 其余属性默认使用全局文本样式，详见TEXTSTYLE
					                    color: 'auto'
					                }
					            },
					            splitLine: {           // 分隔线
					                show: true,        // 默认显示，属性show控制显示与否
					                length :15,         // 属性length控制线长
					                lineStyle: {       // 属性lineStyle（详见lineStyle）控制线条样式
					                    color: 'auto'
					                }
					            },
					            pointer : {
					                width : 5
					            },
					            title : {
					                show : true,
					                offsetCenter: [0, '-40%'],       // x, y，单位px
					                textStyle: {       // 其余属性默认使用全局文本样式，详见TEXTSTYLE
					                    fontWeight: 'bolder'
					                }
					            },
					            detail : {
					                formatter:'{value}%',
					                textStyle: {       // 其余属性默认使用全局文本样式，详见TEXTSTYLE
					                    color: 'auto',
					                    fontWeight: 'bolder'
					                }
					            },
					            data:[{value: 50, name: '压机电流'}]
					        }
					    ]
					};
            myChart.setOption(option);
	}
}
