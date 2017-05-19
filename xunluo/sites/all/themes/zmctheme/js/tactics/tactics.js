

$(function(){
	//策略管理	
	$('#TacticsDatatree').datagrid({
		url:'tactics_data.json',
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
			$('#Myform .easyui-numberspinner').spinner({
				disabled: true
			});
			$("#dlg-buttons a.save_btn").addClass("play_none");
			$("#dlg-buttons a.edit_btn, #dlg-buttons a.close_btn").css("display","inline-block");
			$('.viewTactics').show();
		}
	}).datagrid('clientPaging');
	
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


//  用户管理 单元格样式
function cellStyler(value,row,index){
	if (value == "重置密码"){
		return 'color:#3d85cc;cursor: pointer;';
	}
}


// 策略管理 删除
function del(){
	$.messager.defaults = { ok: "确认", cancel: "取消" ,width: 420 };
	var rows = $("#TacticsDatatree").datagrid('getSelections');
	var rows = $("#TacticsDatatree").datagrid('getChecked');
	if(rows == "null" || rows == "undifined" || rows == ""){
		$.messager.alert("提示", "请选择要删除的行", "error");
		return ;
	} else {
		$.messager.confirm('确认','确认删除?',function(row){
			if(rows.length > 1){
				for(var i=0; i<rows.length; i++){
					var row = rows[i];
					$("#TacticsDatatree").datagrid('deleteRow',row);
				}
			} else {
				$("#TacticsDatatree").datagrid('deleteRow',rows);
			}
		});
	}
}


//策略管理 新增
function add_new(){
	$("#dlg-buttons a.edit_btn").addClass("play_none");
	$("#dlg-buttons a.save_btn, #dlg-buttons a.close_btn").css("display","inline-block");
	$(".viewTactics").show();	
}
//策略管理 编辑（修改）保存
function saveTactics(){
	if ($('#Myform').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#TacticsDatatree').datagrid('reload');
			},
			error : function(result) {
				$.messager.show({
					title : result.status,
					msg : result.message
				});
			}
		});
		$(".viewTactics").hide();
	}
}




//
function closeview(){
	$(".viewTactics").hide();
}
