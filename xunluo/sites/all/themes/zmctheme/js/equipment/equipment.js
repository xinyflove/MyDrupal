

$(function(){
	//云设备管理
	$("#ChectList li a").click(function(){
		$("#ChectList li").find("a").removeClass("active");	
		$(this).addClass("active");
	});
	
	$('#DeviceDatatree').datagrid({
		url:'cloud_data.json',
		fit:true,
		fitColumns:true,
		nowrap:true,
		striped:true,
		checkOnSelect: true,
		selectOnCheck: false,
		singleSelect: true,
		autoRowHeight: false,
		pagination: true,
		pageSize1:10,
		view: detailview,
    	detailFormatter: function(rowIndex, rowData){
        	return '<table class="subtable"><tr>' +
                '<td rowspan=2 style="border:0"><img src="../images/equipment/demo.png" style="height:50px;"></td>' +
                '<td style="border:0">' +
                '<p>Attribute: ' + rowData.attr1 + '</p>' +
                '<p>Status: ' + rowData.status + '</p>' +
                '</td>' +
                '</tr></table>';
    	},
		rowStyler: function(index,row){
			if (index%2 == 0){
				return 'background-color:#fafafa;';
			}
		},
		onDblClickRow :function(rowIndex,rowData){
			$("#Myform .easyui-textbox").textbox({
				disabled:true
			});
			$("#Myform .easyui-combobox").combo({
				disabled: true
			});
			$("#dlg-buttons a.easyui-linkbutton").addClass("play_none");
			$("#dlg-buttons a.edit_btn").css("display","inline-block");
			$('#DetailDialog').dialog('open');
		}
	}).datagrid('clientPaging');
	
	$("#Domain").combotree({
		url: 'tree_data1.json',
		method:'get',
		multiple:true,
		onlyLeafCheck:true,
		onCheck: function(node,checked){
			if(node.checked){
				
			}
		},
		onSelect: function (node){
			
		}
	});
	
	//末端设备管理
	$('#TerminalDeviceDatatree').datagrid({
		data:getTminalData(),
		fit:true,
		fitColumns:true,
		nowrap:true,
		striped:true,
		singleSelect:true,
		autoRowHeight:false,
		pagination:true,
		pageSize1:10,
		rowStyler: function(index,row){
			if (index%2 == 0){
				return 'background-color:#fafafa;';
			}
		},
		onClickCell: function(rowIndex, field, value){
			$(this).val()
			if(value == "数据点管理" && field == "datapoints"){
				$('#MgrDataDialog').dialog('open');
			}else {
				$('#MgrDataDialog').dialog('close');
			}
		},
		onDblClickRow: function(rowIndex,rowData){
			$("#Myform01 .easyui-textbox").textbox({
				disabled:true
			});
			$("#Myform01 .easyui-combobox").combo({
				disabled: true
			});
			$("#dlg-buttons a.easyui-linkbutton").addClass("play_none");
			$("#dlg-buttons a.edit_btn").css("display","inline-block");
			$('#DetailDialog').dialog({
				closed: false
			});
		}
	}).datagrid('clientPaging');
	
	$('#EditData').datagrid({
		data:getDatePints(),
		fitColumns:true,
		nowrap:true,
		singleSelect:true,
		autoRowHeight:false,
		pagination:true,
		pageSize1:10,
		rowStyler: function(index,row){
			if (index%2 == 0){
				return 'background-color:#fafafa;';
			}
		},
		onClickCell: function(index,field,value){
			if(value == "数据模型"){
				$('#DataModelDialog').dialog('open');
			} else if(value == "订阅管理"){
				
			}
		}
	}).datagrid('clientPaging');
	
	//连接模式
	$("#LinkMode").combo({
		onChange: function(newValue, oldValue){
			if(newValue == "com") {
				$(".comcleck").removeClass("play_none");
				$(".ipcleck").addClass("play_none");
			}else if(newValue == "IP") {
				$(".ipcleck").removeClass("play_none");
				$(".comcleck").addClass("play_none");
				$(".window-shadow").css({height: 276});
			}
		}
	});
	
});
(function($){
	function pagerFilter(data){
		if ($.isArray(data)){	// is array
			data = {
				total: data.length,
				rows: data
			}
		}
		var dg = $(this);
		var state = dg.data('datagrid');
		var opts = dg.datagrid('options');
		if (!state.allRows){
			state.allRows = (data.rows);
		}
		var start = (opts.pageNumber-1)*parseInt(opts.pageSize);
		var end = start + parseInt(opts.pageSize);
		data.rows = $.extend(true,[],state.allRows.slice(start, end));
		return data;
	}

	var loadDataMethod = $.fn.datagrid.methods.loadData;
	$.extend($.fn.datagrid.methods, {
		clientPaging: function(jq){
			return jq.each(function(){
				var dg = $(this);
				var state = dg.data('datagrid');
				var opts = state.options;
				opts.loadFilter = pagerFilter;
				var onBeforeLoad = opts.onBeforeLoad;
				opts.onBeforeLoad = function(param){
					state.allRows = null;
					return onBeforeLoad.call(this, param);
				}
				dg.datagrid('getPager').pagination({
					onSelectPage:function(pageNum, pageSize){
						opts.pageNumber = pageNum;
						opts.pageSize = pageSize;
						$(this).pagination('refresh',{
							pageNumber:pageNum,
							pageSize:pageSize
						});
						dg.datagrid('loadData',state.allRows);
					}
				});
				$(this).datagrid('loadData', state.data);
				if (opts.url){
					$(this).datagrid('reload');
				}
			});
		},
		loadData: function(jq, data){
			jq.each(function(){
				$(this).data('datagrid').allRows = null;
			});
			return loadDataMethod.call($.fn.datagrid.methods, jq, data);
		},
		getAllRows: function(jq){
			return jq.data('datagrid').allRows;
		}
	})
})(jQuery);

function getData(){
	var rows = [];
	for(var i=1; i<=800; i++){
		var amount = Math.floor(Math.random()*1000);
		var price = Math.floor(Math.random()*1000);
		rows.push({
			name: 'Inv No '+i,
			serialNum: $.fn.datebox.defaults.formatter(new Date()),
			type: 'Name '+i,
			domain: amount,
			typeIdentifier: price,
			userIdentifier: amount*price,
			site: 'Note '+i,
			IPaddr: "xxxxx",
			status: "xxxxx"
		});
	}
	return rows;
}

function getTminalData(){
	var rows = [];
	for(var i=1; i<=800; i++){
		rows.push({
			name: '机器设备',
			deviceNum: $.fn.datebox.defaults.formatter(new Date()),
			type: 'xxx',
			firm: 'xxx',
			belongs_cloud: 'xxx',
			belongs_domain: 'xxx',
			status: '正常',
			datapoints: "数据点管理"
		});
	}
	return rows;
}

function getDatePints(){
	var rows = [];
	for(var i=1; i<=50; i++){
		rows.push({
			name: '机器设备',
			way: $.fn.datebox.defaults.formatter(new Date()),
			model: '数据模型',
			subscription: '订阅管理'
		});
	}
	return rows;
}

// 末端设备管理 单元格样式
function cellStyler(value,row,index){
	if (value == "数据点管理"){
		return 'color:#3d85cc;cursor: pointer;';
	} else if(value == "数据模型") {
		return 'color:#3d85cc;cursor: pointer;';
	} else if(value == "订阅管理") {
		return 'color:#3d85cc;cursor: pointer;';
	}
}


// 云终端管理
function del(){
	$.messager.defaults = { ok: "确认", cancel: "取消" ,width: 420 };
	var rows = $("#DeviceDatatree").datagrid('getSelections');
	
	if(rows == "null" || rows == "undifined" || rows == ""){
		$.messager.alert("提示", "请选择要删除的行", "error");
		return ;
	} else {
		$.messager.confirm('确认','确认删除?',function(row){
			if(rows.length > 1){
				for(var i=0; i<rows.length; i++){
					var row = rows[i];
					$("#DeviceDatatree").datagrid('deleteRow',row);
				}
			} else {
				$("#DeviceDatatree").datagrid('deleteRow',rows);
			}
		});
	}
}

// 末端设备管理
function delTerminal(){
	$.messager.defaults = { ok: "确认", cancel: "取消" ,width: 420 };
	var rows = $("#TerminalDeviceDatatree").datagrid('getSelections');
	
	if(rows == "null" || rows == "undifined" || rows == ""){
		$.messager.alert("提示", "请选择要删除的行", "error");
		return ;
	} else {
		$.messager.confirm('确认','确认删除?',function(row){
			if(rows.length > 1){
				for(var i=0; i<rows.length; i++){
					var row = rows[i];
					$("#TerminalDeviceDatatree").datagrid('deleteRow',row);
				}
			} else {
				$("#TerminalDeviceDatatree").datagrid('deleteRow',rows);
			}
		});
	}
}



function edit(){
	if ($('#Myform01').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform01').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#TerminalDeviceDatatree').datagrid('reload')
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#DetailDialog').dialog('close');
	}
}
function add_device(){
	if ($('#Myform02').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform02').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#TerminalDeviceDatatree').datagrid('reload');
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#AddDialog').dialog('close');
	}
}
function add_datapoint(){
	if ($('#Myform03').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform03').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#TerminalDeviceDatatree').datagrid('reload')
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#MgrDataDialog').dialog('close');
	}
}
function add_datamgr(){
	if ($('#Myform04').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform04').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#EditData').datagrid('reload')
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#DataModelDialog').dialog('close');
	}
}


//添加云终端
function add(){
	if ($('#Myform01').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform01').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#DeviceDatatree').datagrid('reload');
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#AddDialog').dialog('close');
	}
}
//添加云终端编辑保存
function add_edit(){
	if ($('#Myform01').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform01').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#DeviceDatatree').datagrid('reload');
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#DetailDialog').dialog('close');
	}
}


//升级/备份/恢复
function add_upgrade(){	
	if ($('#myform').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#myform').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#DetailDialog').dialog('close');
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$('#DetailDialog').dialog('close');
	}
}
