(function($){



})(jQuery);


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
        /*
// 初始化仪表盘字段
function initDefaultChart(ec){
//	for(var i=1; i<2; i++){

           var myChart1 = ec.init(document.getElementById('attr-chart-1'));
           var  option1 = {
                    tooltip: {
                    },
                    toolbox: {
                        show: false,
                        feature: {
                            mark: {show: true},
                            restore: {show: true},
                            saveAsImage: {show: true}
                        }
                    },
                    series: [
                        {
                            name: '压机电流(A)',
                            type: 'gauge',
                            min: 0,
                            max: 100,
                            splitNumber: 10,
                            detail: {
                                textStyle: {// 其余属性默认使用全局文本样式，详见TEXTSTYLE
                                    fontWeight: 'bolder'
                                }
                            },
                            data: [{value: 0, name: '电流(A)'}],
                            axisLine: {// 坐标轴线
                                lineStyle: {// 属性lineStyle控制线条样式
                                    color: [[0.2, '#228b22'], [0.8, '#48b'], [1, '#ff4500']],
                                    width: 4
                                }
                            },
                            axisTick: {// 坐标轴小标记
                                length: 5, // 属性length控制线长
                                lineStyle: {// 属性lineStyle控制线条样式
                                    color: 'auto'
                                }
                            },
                            splitLine: {// 分隔线
                                length: 7, // 属性length控制线长
                                lineStyle: {// 属性lineStyle（详见lineStyle）控制线条样式
                                    color: 'auto'
                                }
                            },
                            axisLabel: {// 坐标轴文本标签，详见axis.axisLabel
                                textStyle: {// 其余属性默认使用全局文本样式，详见TEXTSTYLE
                                    color: 'auto'
                                }
                            },
                        }
                    ]
                };


                    
            myChart1.setOption(option1);


}
*/