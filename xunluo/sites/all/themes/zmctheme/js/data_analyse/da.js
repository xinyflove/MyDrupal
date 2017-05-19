/*handle data anlyse javascripts*/

$(function(){
	$("#equipmentTree").tree({
		onSelect:function(node){
			console.log(node);
			$("#device-name").html(node.text);
			$("#daOrgType").val();
			$("#daDevID").val(node.id);
				
		}
	});
	$("#main-table").hide(); //隐藏列表模式
	
});

function computeOtherFields(rec){
			
			switch(parseInt(rec.value)){
				case 1:  //当查询指标为“告警”时候， “指标类型”未 “全部”，预警， 告警，故障，已闭环， “查询项”为 全部，温度告警。
					var data = [
						{ 
							value: '-1',
							label: '全部'
						},
						{ 
							value: '1',
							label: '预警'
						},
						{ 
							value: '2',
							label: '告警'
						},	
						{ 
							value: '3',
							label: '故障'
						},
						{ 
							value: '4',
							label: '已闭环'
						}
					];
					$("#indexTypeCC").combobox('loadData',data);
					$(".queryItemTd").css('visibility','visible');
					var rec = {};   //更新下查询项
					rec.value = $("#indexTypeCC").combobox('getValue'); 
					computeQueryItemFields(rec);
				break;	

				case 2:  //当查询指标为“巡检”时候， “指标类型”为 “全部”，待巡检， 已巡检，已巡检 无“查询项”
				$(".queryItemTd").css('visibility','hidden');
				var data = [
						{ 
							value: '-1',
							label: '全部'
						},
						{ 
							value: '1',
							label: '待巡检'
						},
						{ 
							value: '2',
							label: '已巡检'
						},	
					];
					$("#indexTypeCC").combobox('loadData',data);	
					
					
				break;

				case 3: //当查询指标为“设备本身实时数据”时候， “指标类型”未 “全部”，状态量， 模拟量，“查询项” 为“温度” ，“压力”等，从数据模型获取
					 $(".queryItemTd").css('visibility','visible');
					 var data = [
					/*	{ 
							value: '-1',
							label: '全部'
						}, */
						{ 
							value: '1',
							label: '状态量'
						},
						{ 
							value: '2',
							label: '模拟量'
						},	
					];
					$("#indexTypeCC").combobox('loadData',data);	
					$("#indexTypeCC").combobox('setValue',2);
					var rec = {};   //更新下查询项
					rec.value = $("#indexTypeCC").combobox('getValue'); 
					computeQueryItemFields(rec);
					break ;

			}
			
			
}

function computeQueryItemFields(rec){
	
	var index = $("#queryIndexCC").combobox('getValue'); 
	var url = 'http://xfyun.net?index='+index+"&type="+rec.value;
	
	$("#queryItemCC").combobox('reload',url);
}

function da_query_submit(){
	$("#daQueryForm").form('submit',{
		url: 'http://xfyun.net',
		onSubmit:function(){
			//do some check 
			var devId = $("#daDevID").val();  
			console.log(devId);
			if( devId == 0){
				$.messager.alert('错误',"请先选择设备或者组织",'info');
				return false; 
			}


			//return false to prevent submit;
		},
		success:function(data){
			alert('data');
			
		}
	});
}

function da_export2file(){

}

function initDefaultChart(ec){
	var myChart = ec.init(document.getElementById('main-chart'));
            var   option = {
				    title : {
				        text: '统计结果',
				        subtext: '故障次数'
				    },
				    tooltip : {
				        trigger: 'axis'
				    },
				    legend: {
				        data:['告警','巡检','温度']
				    },
				    toolbox: {
				        show : true,
				        feature : {
				            mark : {show: true},
				            dataView : {show: true, readOnly: false},
				            magicType : {show: true, type: ['line', 'bar', 'stack', 'tiled']},
				            restore : {show: true},
				            saveAsImage : {show: true}
				        }
				    },
				    calculable : true,
				    xAxis : [
				        {
				            type : 'category',
				            boundaryGap : false,
				            data : ['周一','周二','周三','周四','周五','周六','周日']
				        }
				    ],
				    yAxis : [
				        {
				            type : 'value'
				        }
				    ],
				    series : [
				        {
				            name:'成交',
				            type:'line',
				            smooth:true,
				            itemStyle: {normal: {areaStyle: {type: 'default'}}},
				            data:[10, 12, 21, 54, 260, 830, 710]
				        },
				        {
				            name:'预购',
				            type:'line',
				            smooth:true,
				            itemStyle: {normal: {areaStyle: {type: 'default'}}},
				            data:[30, 182, 434, 791, 390, 30, 10]
				        },
				        {
				            name:'意向',
				            type:'line',
				            smooth:true,
				            itemStyle: {normal: {areaStyle: {type: 'default'}}},
				            data:[1320, 1132, 601, 234, 120, 90, 20]
				        }
				    ]
				};
            myChart.setOption(option);

}

function switchDrawChart(){
	$("#main-chart").show(); //显示曲线图
	$("#main-table").hide();
	$("#drawTableBtn").linkbutton('unselect');
}
function switchDrawTable(){
	$("#main-chart").hide(); //隐藏曲线图
	$("#main-table").show();
	$("#drawChartBtn").linkbutton('unselect');
}
