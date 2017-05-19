
var editIndex = undefined;

var attrTaxonomy = [{
	tid:1,
	text: '模拟量'	
},{
	tid:2,
	text: '状态量'	
}

];

var params = [{
	id:1,
	text: '模拟量'	
},{
	id:2,
	text: '状态量'	
}

];

var registers = [{
	id:1,
	text: '模拟量'	
},{
	id:2,
	text: '状态量'	
}

];


$(function(){
	//系统管理	
	$('#SystemDatatree').datagrid({
		url:'appkey_data.json',
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
			$("#Myform .easyui-combotree").combotree({
				editable:false
			});
			$("#dlg-buttons a.easyui-linkbutton").addClass("play_none");
			$("#dlg-buttons a.edit_btn").css("display","inline-block");
			$('#DetailDialog').dialog('open');
		}
	}).datagrid('clientPaging');	

	//组织机构管理	
	$('#orgDg').treegrid({
		url:'tree_data1.json',
		fit:true,
		fitColumns:true,
		lines: true,
		idField: 'id',
	    treeField: 'name',
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
			
		}
	});	
	//权限管理	
	$('#roleDg').datagrid({
		url:'tree_data2.json',
		fit:true,
		fitColumns:true,
		lines: true,
		idField: 'id',
	    treeField: 'name',
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
			
		}
	});	
	$('#dlgPeopleDg').datagrid({
		url:'tree_data2.json',
		fit:true,
		fitColumns:true,
		lines: true,
		idField: 'id',
	    treeField: 'name',
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
			
		}
	});	
	//人员管理	
	$('#peopleDg').datagrid({
		url:'people.json',
		fit:true,
		fitColumns:true,
		lines: true,
		idField: 'id',
	    treeField: 'name',
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
			
		}
	});	

	//设备类型管理 assetTypeDg
	$('#assetTypeDg').datagrid({
			url:'appkey_data.json',
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
				
			}
		}).datagrid('clientPaging');	

	//扩展字段管理ExtFieldsDg
	$('#ExtFieldsDg').datagrid({
			url:'appkey_data.json',
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
				
			}
		}).datagrid('clientPaging');	
	

	//错误代码详细描述 erorCodesDg
	$('#erorCodesDg').datagrid({
			url:'appkey_data.json',
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
				
			}
		}).datagrid('clientPaging');	



	//数据模型管理 datamodelDg
	$('#datamodelDg').datagrid({
			url:'appkey_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
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
				
			}
		}).datagrid('clientPaging');

	//配置数据模型时候，字段列表 DmAttrsDg
	$('#DmAttrsDg').datagrid({
			url:'dmfields_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
			checkOnSelect: true,
			selectOnCheck: false,
			singleSelect: true,
			autoRowHeight: false,
			pagination: true,
			pageSize1:10,
			loadMsg:'正在加载数据...',
			rowStyler: function(index,row){
				if (index%2 == 0){
					return 'background-color:#fafafa;';
				}
			},
			onDblClickRow :function(rowIndex,rowData){
				
			}
		});
	
	//通知模板管理 notiTemplDg 

	$('#notiTemplDg').datagrid({
			url:'dmfields_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
			checkOnSelect: true,
			selectOnCheck: false,
			singleSelect: true,
			autoRowHeight: false,
			pagination: true,
			pageSize1:10,
			loadMsg:'正在加载数据...',
			rowStyler: function(index,row){
				if (index%2 == 0){
					return 'background-color:#fafafa;';
				}
			},
			onDblClickRow :function(rowIndex,rowData){
				
			}
		});
	
	//数据字典

	$('#dictDg').datagrid({
			url:'dmfields_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
			checkOnSelect: true,
			selectOnCheck: false,
			singleSelect: true,
			autoRowHeight: false,
			pagination: true,
			pageSize1:10,
			loadMsg:'正在加载数据...',
			rowStyler: function(index,row){
				if (index%2 == 0){
					return 'background-color:#fafafa;';
				}
			},
			onDblClickRow :function(rowIndex,rowData){
				
			}
		});
	/*数据字典的详细条目 DictItemsDg*/ 
	
	$('#DictItemsDg').datagrid({
			url:'dmfields_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
			checkOnSelect: true,
			selectOnCheck: false,
			singleSelect: true,
			autoRowHeight: false,
			pagination: true,
			pageSize1:10,
			loadMsg:'正在加载数据...',
			rowStyler: function(index,row){
				if (index%2 == 0){
					return 'background-color:#fafafa;';
				}
			},
			onDblClickRow :function(rowIndex,rowData){
				
			}
		});

	//分类管理
	
	$('#taxonomyDg').datagrid({
			url:'dmfields_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
			checkOnSelect: true,
			selectOnCheck: false,
			singleSelect: true,
			autoRowHeight: false,
			pagination: true,
			pageSize1:10,
			loadMsg:'正在加载数据...',
			rowStyler: function(index,row){
				if (index%2 == 0){
					return 'background-color:#fafafa;';
				}
			},
			onDblClickRow :function(rowIndex,rowData){
				
			}
		});
		
		/*分类管理的数据条目 taxonomy-tree*/
		    $('#taxonomy-tree').tree({
		    	url:'tree_data3.json',
		    	animate:true,
		    	lines:true,
		    	onContextMenu: function(e,node){
					e.preventDefault();
					$(this).tree('select',node.target);
					$('#txaonomyContextMenu').menu('show',{
					left: e.pageX,
					top: e.pageY
					});
					},
				onSelect: function (node){
					selectedTaxonomyItem(node);
				}


		    });


		 //  订阅管理 subscribersDg
		   $('#subscribersDg').datagrid({
			url:'dmfields_data.json',
			fit:true,
			fitColumns:true,
			nowrap:true,
			striped:true,
			idField: 'id',
			checkOnSelect: true,
			selectOnCheck: false,
			singleSelect: true,
			autoRowHeight: false,
			pagination: true,
			pageSize1:10,
			loadMsg:'正在加载数据...',
			rowStyler: function(index,row){
				if (index%2 == 0){
					return 'background-color:#fafafa;';
				}
			},
			onDblClickRow :function(rowIndex,rowData){
				
			}
		});
		 

		 //模块管理 
	 $('#modulesDg').treegrid({
		url:'tree_data1.json',
		fit:true,
		fitColumns:true,
		lines: true,
		idField: 'id',
	    treeField: 'name',
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


// 基础数据管理 删除
function del(){
	$.messager.defaults = { ok: "确认", cancel: "取消" ,width: 420 };
	var rows = $("#UserDatatree").datagrid('getSelections');
	
	if(rows == "null" || rows == "undifined" || rows == ""){
		$.messager.alert("提示", "请选择要删除的行", "error");
		return ;
	} else {
		$.messager.confirm('确认','确认删除?',function(row){
			if(rows.length > 1){
				for(var i=0; i<rows.length; i++){
					var row = rows[i];
					$("#UserDatatree").datagrid('deleteRow',row);
				}
			} else {
				$("#UserDatatree").datagrid('deleteRow',rows);
			}
		});
	}
}


//基础数据管理 新增保存
function add_appkey(){
	if ($('#Myform01').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform01').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#AppkeyDatatree').datagrid('reload');
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
//基础数据管理 编辑保存
function add_edit_appkey(){
	if ($('#Myform').form('validate')) {
		$.ajax({
			type: 'post',
			url: 'submit',
			cache: false,
			data: $('#Myform').serialize(),
			dataType: 'json',
			success: function(result) {
				$('#AppkeyDatatree').datagrid('reload');
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

//组织管理 

function formatOrgParams(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupOrgParamsDlg('+value+');">参数配置</a>' ;

}

function formatOrgOperations(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupOrgDetailDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delOrgDlg('+value+');">删除</a>';

}


function openAddOrgDlg(){
		var selectedRow = $("#orgDg").datagrid('getSelected');
		if(selectedRow == null){
		$.messager.alert('错误','请先选择要添加组织的父节点');
		return false;
		}
		$("#parent-org-name").html(selectedRow.name);
		$("#parent-org-id").val(selectedRow.id);
		$("tr.timestamp").hide();
		$("#orgDlg-buttons a.easyui-linkbutton").removeClass("play_none");
		$("#orgDlg-buttons a.edit_btn").hide();
		$('#editOrgDialog').dialog('open');

}
function batchDelOrgs(){

	var checkedRows = $("#orgDg").datagrid('getChecked');
	
	if(checkedRows.length < 1) {
		$.messager.alert('错误','请先勾选要删除的组织');
		return false;
	}
	var org_arrays = [];

	for(var i=0; i<checkedRows.length; i++){
		org_arrays.push(checkedRows[i].id);
	}

	var batchDelUrl = "http://www.baidu.com/batchDel";
	$.post(
		batchDelUrl, 
		{ ids: org_arrays.join(',') }, 
		function (text, status) { 
			alert(text); 

		});


}
function save_org(){
	var saveOrgUrl = "http://www.xfyun.net/saveorg"; //替换为真实的 

	$('#myOrgForm').form('submit', {
    url: saveOrgUrl,
    onSubmit: function(){
        var isValid = $(this).form('validate');
		if (!isValid){
		}
		return isValid;	// return false will stop the form submission
    },
    success:function(data){
    	$('#editOrgDialog').dialog('close');
		$.messager.show({
			title:'保存成功',
			msg:'添加组织成功.',
			timeout:3000,
			showType:'slide'
		});
    }
	});
}

function popupOrgDetailDlg(id){

	$("#orgDlg-buttons a.easyui-linkbutton").addClass("play_none");
	$("#orgDlg-buttons a.edit_btn").show();
	$("#myOrgForm .easyui-validatebox").textbox({
		disabled:true
	});
	$("#myOrgForm .easyui-textbox").textbox({
		disabled:true
	});

	$('#myOrgForm').form('load',{  //详细参考easyui form 
		name:'name2',
		desc:'mymail@gmail.com',
		porg_id:'subject2',
		weight:'5',
	});

    $('#editOrgDialog').dialog('open');


}

function delOrgDlg(idValue){
	var delUrl = "http://www.xxy.com/del/org";
	$.post(
		delUrl, 
		{ id: idValue }, 
		function (text, status) { 
			alert(text); 

		});

	$("#orgDg").datagrid("deleteRow", idValue);
}

function popupOrgParamsDlg(idValue){
		$("#org-id").val(idValue);
	    $('#cfgOrgParamDialog').dialog('open');

}

function save_orgParams(){

	var saveOrgParamUrl = "http://www.xfyun.net/saveorgParam"; //替换为真实的 

	$('#OrgParamForm').form('submit', {
    url: saveOrgParamUrl,
    onSubmit: function(){
        var isValid = $(this).form('validate');
		if (!isValid){
		}
		return isValid;	// return false will stop the form submission
    },
    success:function(data){
		$('#cfgOrgParamDialog').dialog('close');
		$.messager.show({
			title:'保存成功',
			msg:'修改参数成功.',
			timeout:3000,
			showType:'slide'
		});
    }
	});
}

//角色管理 

function formatRolePermission(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupViewPermsDlg('+value+');">查看权限</a>' ;

}

function formatRoleOperations(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupRoleDetailDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delRoleDlg('+value+');">删除</a>';

}


function openAddRoleDlg(){
		$("tr.timestamp").hide();
		$("#roleDlg-buttons a.easyui-linkbutton").removeClass("play_none");
		$("#roleDlg-buttons a.edit_btn").hide();
		$('#editRoleDialog').dialog('setTitle','添加').dialog('open');

}
function batchDelRoles(){

	var checkedRows = $("#roleDg").datagrid('getChecked');
	
	if(checkedRows.length < 1) {
		$.messager.alert('错误','请先勾选要删除的组织');
		return false;
	}
	var org_arrays = [];

	for(var i=0; i<checkedRows.length; i++){
		org_arrays.push(checkedRows[i].id);
	}

	var batchDelUrl = "http://www.baidu.com/batchDel";
	$.post(
		batchDelUrl, 
		{ ids: org_arrays.join(',') }, 
		function (text, status) { 
			alert(text); 

		});


}
function authPeople(){
		$('#viewPermissionDialog').dialog('setTitle','授权').dialog('open');
}
function popupViewPermsDlg(idValue){
		$("#role-id").val(idValue);
		$('#viewPermissionDialog').dialog('open');
}

function popupRoleDetailDlg(id){

	$("#roleDlg-buttons a.easyui-linkbutton").addClass("play_none");
	$("#roleDlg-buttons a.edit_btn").show();
	$("#myRoleForm .easyui-validatebox").textbox({
		disabled:true
	});
	$("#myRoleForm .easyui-textbox").textbox({
		disabled:true
	});

	$('#myRoleForm').form('load',{  //详细参考easyui form 
		name:'name2',
		desc:'mymail@gmail.com',
		porg_id:'subject2',
		weight:'5',
	});

    $('#editRoleDialog').dialog('setTitle','编辑').dialog('open');


}

function delRoleDlg(idValue){
	var delUrl = "http://www.xxy.com/del/org";
	$.post(
		delUrl, 
		{ id: idValue }, 
		function (text, status) { 
			alert(text); 

		});

	$("#orgDg").datagrid("deleteRow", idValue);
}

//人员管理 

function formatPeoplePermission(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupPeoplePermsDlg('+value+');">权限配置</a>' ;

}
function formatResetPassword(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupResetPasswdDlg('+value+');">重置密码</a>' ;

}


function formatPeopleOperations(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupPeopleDetailDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delPeopleDlg('+value+');">删除</a>';

}


function openAddPeopleDlg(){
		$("tr.timestamp").hide();
		$("#peopleDlg-buttons a.easyui-linkbutton").removeClass("play_none");
		$("#peopleDlg-buttons a.edit_btn").hide();
		$('#editPeopleDialog').dialog('setTitle','添加').dialog('open');

}
function batchDelPeoples(){
	var checkedRows = $("#peopleDg").datagrid('getChecked');
	
	if(checkedRows.length < 1) {
		$.messager.alert('错误','请先勾选要删除的账号');
		return false;
	}
	var people_arrays = [];

	for(var i=0; i<checkedRows.length; i++){
		people_arrays.push(checkedRows[i].id);
	}

	var batchDelUrl = "http://www.baidu.com/batchDel";
	$.post(
		batchDelUrl, 
		{ ids: people_arrays.join(',') }, 
		function (text, status) { 
			$("#peopleDg").datagrid('reload');

		});


}
function popupResetPasswdDlg(idValue){
		$('#viewPermissionDialog').dialog('setTitle','授权').dialog('open');
}
function popupPeoplePermsDlg(idValue){
		$("#role-id").val(idValue);
		$('#viewPermissionDialog').dialog('open');
}
function assignRole(){
	alert('assignrole');
}

function removeRole(){
	
}

function popupPeopleDetailDlg(id){

	$("#peopleDlg-buttons a.easyui-linkbutton").addClass("play_none");
	$("#peopleDlg-buttons a.edit_btn").show();
	$("#myPeopleForm .easyui-validatebox").textbox({
		disabled:true
	});
	$("#myPeopleForm .easyui-textbox").textbox({
		disabled:true
	});

	$('#myPeopleForm').form('load',{  //详细参考easyui form 
		login:'name2',
		fullname:'name2',
		email:'mymail@gmail.com',
		phone:'subject2',
		weight:'5',
	});

    $('#editPeopleDialog').dialog('setTitle','编辑').dialog('open');


}

function delPeopleDlg(idValue){
	var delUrl = "http://www.xxy.com/del/org";
	$.post(
		delUrl, 
		{ id: idValue }, 
		function (text, status) { 
			alert(text); 

		});

	$("#peopleDg").datagrid("deleteRow", idValue);
}
function save_people(){
	var savePeopleParamUrl = "http://www.xfyun.net/saveorgParam"; //替换为真实的 

	$('#myPeopleForm').form('submit', {
    url: savePeopleParamUrl,
    onSubmit: function(){
        var isValid = $(this).form('validate');
		if (!isValid){
		}
		return isValid;	// return false will stop the form submission
    },
    success:function(data){
		$('#editPeopleDialog').dialog('close');
		$.messager.show({
			title:'保存成功',
			msg:'添加成功.',
			timeout:3000,
			showType:'slide'
		});
    }
	});
}

//系统设置




/*************************************/
//设备类型管理
/*************************************/


function popupAddAssetTypeDlg(){
	
	$("#assettypedlg-buttons a.easyui-linkbutton").removeClass("play_none");
	$("#assettypedlg-buttons a.edit_btn").hide();

	
	$('#editAssetTypeDialog').dialog('setTitle','添加').dialog('open');
}

function batchDelAssetType(){

}

function exportAssetType(){

}

//错误代码处理 
function formatErrorCode(val, row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupErrorCodeDlg('+val+');">故障代码</a>&nbsp';
			
}

function popupErrorCodeDlg(val){

	$("#errorCodeDialog").dialog('open');

}

function endErrorCodeEditing(){
	if (editIndex == undefined){return true}
	if ($('#erorCodesDg').datagrid('validateRow', editIndex)){
	
	$('#erorCodesDg').datagrid('endEdit', editIndex);
	editIndex = undefined;
	return true;
	} else {
	return false;
	}
}



//点击+号增加一个新的错误代码
function insertNewErrorCode(){
	if (endErrorCodeEditing()){
		$('#erorCodesDg').datagrid('insertRow',{
			index: 0,	// index start with 0
			row: { 		
				id:0,
				errcode:'',
				errdesc:"",
			}
		});
		editIndex = 0;
		$('#erorCodesDg').datagrid('validateRow', editIndex)

		$('#erorCodesDg').datagrid('selectRow', editIndex)
		.datagrid('beginEdit', editIndex);
	}
}


function batchDelErrorCodes(){

}

function submitErrorCodeForm(){
	endErrorCodeEditing(); //结束编辑，这样才能保存到datagrid里
	alert('save error code to backend');
}

//扩展字段处理
function formatExtendedFields(val,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupExtendFieldsDlg('+val+');">扩展字段</a>&nbsp';
}
function popupExtendFieldsDlg(val){
	$("#extendFieldsDialog").dialog('open');
}



function endExtFieldEditing(){
	if (editIndex == undefined){return true}
	if ($('#ExtFieldsDg').datagrid('validateRow', editIndex)){
	
	$('#ExtFieldsDg').datagrid('endEdit', editIndex);
	editIndex = undefined;
	return true;
	} else {
	return false;
	}
}



//点击+号增加一个新的扩展字段
function insertNewExtField(){
	if (endExtFieldEditing()){
		$('#ExtFieldsDg').datagrid('insertRow',{
			index: 0,	// index start with 0
			row: { 		//这个地方如果需要赋值更多，那就把更多字段增加过来
				id:0,
				fieldtype:1,
				name:'',
				dropboxvalues:"",
				isrequired:1
			}
		});
		editIndex = 0;
		$('#ExtFieldsDg').datagrid('validateRow', editIndex)

		$('#ExtFieldsDg').datagrid('selectRow', editIndex)
		.datagrid('beginEdit', editIndex);
	}
}


//批量删除扩展字段
function batchDelExtFieldss(){

}

//保存所有数据
function submitExtendFieldsForm(){
	endExtFieldEditing();
	alert('save all data');

}
 
function changeDataModle(idValue){
	var url = 'http://www.baidu.com/get_data2.php?id='+idValue; //转换成真实的
    $('#protocolCbx').combobox('reload', url);

}

function enableEditAssetType(value){	
	$("#MyAssetTypeform .easyui-textbox").textbox({
		disabled:false
	});
	$("#MyAssetTypeform .easyui-combobox").combo({
		disabled:false
	});
	$("#assettypedlg-buttons a.easyui-linkbutton").removeClass("play_none");
	$("#assettypedlg-buttons a.edit_btn").hide();

	
}

function formatAssetTypeOperation(value){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupAssetTypeDetailDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delAssetType('+value+');">删除</a>';
			
}

//点击查看详细按钮
function popupAssetTypeDetailDlg(val){

}

function delAssetType(val){
	
}
//点击Save按钮处理 

function submitAssetTypeForm(){

		$('#editAssetTypeDialog').dialog('close');

}



/*************************************/
//数据模型管理
//DM --> Data Model
/*************************************/

function formatDataModelOperation(value){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupDMDetailDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delDM('+value+');">删除</a>';
			
}

function formatDataModel(value){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupDMAttrsList('+value+');">数据模型</a>&nbsp';
			
			
}

//新增数据模型
function popupAddDMDlg(){
	enableEditDM();
	$("#MyDMform tr.create-timestamp").hide();
	$('#DMDetailDialog').dialog('setTitle','添加').dialog('open');
}

//批量删除数据模型
function batchDelDMs(){
	$.messager.defaults = { ok: "确认", cancel: "取消" ,width: 420 };
	var rows = $("#datamodelDg").datagrid('getChecked');
	if(rows == "null" || rows == "undifined" || rows == ""){
		$.messager.alert("提示", "请选择要删除的行", "error");
		return ;
	} else {
		$.messager.confirm('确认','确认删除?',function(row){
			//别忘记应该到后台去提交删除
			if(rows.length > 1){
				for(var i=0; i<rows.length; i++){
					var row = rows[i];
					$("#datamodelDg").datagrid('deleteRow',row);
				}
			} else {
				$("#datamodelDg").datagrid('deleteRow',rows);
			}
		});
	}
}

//批量导出
function exportDms(){
	alert('export to file') ; 

}
//查看详细的数据模型
function popupDMDetailDlg(val){
	disableEditDM();
	$('#DMDetailDialog').dialog('setTitle','编辑').dialog('open');
}



function enableEditDM(){
	$("#MyDMform .easyui-textbox").textbox({
		disabled:false
	});
	$("#MyDMform .easyui-combobox").combo({
		disabled:false
	});
	$("#dmdlg-buttons #enableEditBtn").hide();
	$("#dmdlg-buttons #saveDataBtn, #dmdlg-buttons #closeDlgBtn").show();
}

function disableEditDM(){
	$("#MyDMform .easyui-textbox").textbox({
		disabled:true
	});
	$("#MyDMform .easyui-combobox").combo({
		disabled:true
	});
	$("#dmdlg-buttons #enableEditBtn").show();
	$("#dmdlg-buttons #saveDataBtn,#dmdlg-buttons #closeDlgBtn").hide();
}

function submitDmForm(){
	alert('使用标准easyui form进行提交');
}

//删除数据模型
function delDM(val){
	
	$.messager.defaults = { ok: "确认", cancel: "取消" ,width: 420 };
	$.messager.confirm('确认','确认删除?',function(row){
			//别忘记应该到后台去提交删除
			
		$("#datamodelDg").datagrid('deleteRow',val);
			
		});
	

}

//数据模型的详细字段配置弹出框
function popupDMAttrsList(value){

	$('#DMAttrsDialog').dialog('open');

}
//保存配置的数据模型
function submitDMAttrsList(){
	endDMAttrEditing();
	var allRows = $("#DmAttrsDg").datagrid('getRows');
	console.log(allRows);

}

function formatTaxonomy(val){
	return val;
}



function endDMAttrEditing(){
	if (editIndex == undefined){return true}
	if ($('#DmAttrsDg').datagrid('validateRow', editIndex)){
	
	$('#DmAttrsDg').datagrid('endEdit', editIndex);
	editIndex = undefined;
	return true;
	} else {
	return false;
	}
}


//点击+号，增加一个子新字段
function insertNewAttr(){
	if (endDMAttrEditing()){
		$('#DmAttrsDg').datagrid('insertRow',{
			index: 0,	// index start with 0
			row: { 		//这个地方如果需要赋值更多，那就把更多字段增加过来
				id:0,
				termid:1,
				paramid:1,
				name:'',
				regtype:1
			}
		});
		editIndex = 0;
		$('#DmAttrsDg').datagrid('validateRow', editIndex)

		$('#DmAttrsDg').datagrid('selectRow', editIndex)
		.datagrid('beginEdit', editIndex);
	}
}


/*************************************/
/*									 *
*									 *
*              通知模板				 *
*									 */									
/*************************************/

function openAddNotiTemplDlg(){
	$("#editNotiTemplBtn").hide();
	$("#saveNotiTemplBtn, #closeNotiTemplBtn").show();
	enableNotiTemplFormElements();

	$("#editNotiTemplDialog").dialog('setTitle','添加').dialog('open');
}

//批量删除模板
function batchDelNotiTempls(){  

}

function exportNotiTempls(){

}


function formatNotiTemplOperations(value, row){

	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupEditNotiTemplDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delNotiTemplDlg('+value+');">删除</a>';
}


function enableNotiTemplFormElements(){
	$("#myNotiTemplForm .easyui-textbox").textbox({disabled:false});
	$("#myNotiTemplForm .easyui-combobox").combo({disabled: false});
	
}
function disableNotiTemplFormElements(){
	$("#myNotiTemplForm .easyui-textbox").textbox({disabled:true});
	$("#myNotiTemplForm .easyui-combobox").combo({disabled: true});
	
}

//编辑存在的模板
function popupEditNotiTemplDlg(val){
	$("#editNotiTemplBtn").show();
	$("#saveNotiTemplBtn, #closeNotiTemplBtn").hide();
	
	disableNotiTemplFormElements();

	$("#editNotiTemplDialog").dialog('setTitle','编辑').dialog('open');
}

function delNotiTemplDlg(val){

}

//添加通知模板时候，选择通知人
function selectNotifyPerson(){
	alert('select peple');
}

//新增或者编辑之后，进行提交
function submitNotiTempl(){

	$("#editNotiTemplDialog").dialog('close');
}

//查看状态下，点击"编辑"按钮
function enableEditNotiTempl(){
	$("#editNotiTemplBtn").hide();
	$("#saveNotiTemplBtn, #closeNotiTemplBtn").show();
	enableNotiTemplFormElements();
	
}


/*************************************/
/*									 *
*									 *
*              数据字典				 *
*									 */									
/*************************************/

function openAddDictDlg(){
	$("#editDictBtn").hide();
	$("#saveDictBtn, #closeDictBtn").show();
	enableDictFormElements();

	$("#editDictDialog").dialog('setTitle','添加').dialog('open');
}

//批量删除模板
function batchDelDicts(){  

}

function exportDicts(){

}

function formatDictDetails(value, row){

	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupViewDictDetailDlg('+value+');">明细列表</a>&nbsp';
} 

function formatDictOperations(value, row){

	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupEditDictDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delDictDlg('+value+');">删除</a>';
}

function enableDictFormElements(){
	$("#myDictForm .easyui-textbox").textbox({disabled:false});
	$("#myDictForm .easyui-combobox").combo({disabled: false});
	
}
function disableDictFormElements(){
	$("#myDictForm .easyui-textbox").textbox({disabled:true});
	$("#myDictForm .easyui-combobox").combo({disabled: true});
	
}

//编辑存在的模板
function popupEditDictDlg(val){
	$("#editDictBtn").show();
	$("#saveDictBtn, #closeDictBtn").hide();
	
	disableDictFormElements();

	$("#editDictDialog").dialog('setTitle','编辑').dialog('open');
}

function popupViewDictDetailDlg(val){
	
	$("#viewDictDetailsDialog").dialog('open'); 
}
function delDictDlg(val){

}


//新增或者编辑之后，进行提交
function submitDict(){

	$("#editDictDialog").dialog('close');
}

//查看状态下，点击"编辑"按钮
function enableEditDict(){
	$("#editDictBtn").hide();
	$("#saveDictBtn, #closeDictBtn").show();
	enableDictFormElements();
	
}


function endDictItemEditing(){
	if (editIndex == undefined){return true}
	if ($('#DictItemsDg').datagrid('validateRow', editIndex)){
	
	$('#DictItemsDg').datagrid('endEdit', editIndex);
	editIndex = undefined;
	return true;
	} else {
	return false;
	}
}



//点击 + 号新增加一个条目
function insertNewDictItem(){
	if (endDictItemEditing()){
		$('#DictItemsDg').datagrid('insertRow',{
			index: 0,	// index start with 0
			row: { 		
				id:0,
				dictsn:'12',
				dictname:"",
			}
		});
		editIndex = 0;
		$('#DictItemsDg').datagrid('validateRow', editIndex)

		$('#DictItemsDg').datagrid('selectRow', editIndex)
		.datagrid('beginEdit', editIndex);
	}
}



//批量删除一个条目
function batchDelDictItems(){

}


/*************************************/
/*									 *
*									 *
*              分类管理				 *
*									 */									
/*************************************/
function openAddTaxonomyDlg(){
	$("#editTaxonomyBtn").hide();
	$("#saveTaxonomyBtn, #closeTaxonomyBtn").show();
	enableTaxonomyFormElements();

	$("#editTaxonomyDialog").dialog('setTitle','添加').dialog('open');
}

//批量删除模板
function batchDelTaxonomys(){  

}

function exportTaxonomys(){

}

function formatTaxonomyDetails(value, row){

	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupViewTaxonomyDetailDlg('+value+');">明细列表</a>&nbsp';
} 

function formatTaxonomyOperations(value, row){

	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupEditTaxonomyDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delTaxonomyDlg('+value+');">删除</a>';
}

function enableTaxonomyFormElements(){
	$("#myTaxonomyForm .easyui-textbox").textbox({disabled:false});
	$("#myTaxonomyForm .easyui-combobox").combo({disabled: false});
	
}
function disableTaxonomyFormElements(){
	$("#myTaxonomyForm .easyui-textbox").textbox({disabled:true});
	$("#myTaxonomyForm .easyui-combobox").combo({disabled: true});
	
}

//编辑存在的模板
function popupEditTaxonomyDlg(val){
	$("#newTaxonomyBtn, #editTaxonomyBtn").show();
	$("#saveTaxonomyBtn, #closeTaxonomyBtn").hide();
	
	disableTaxonomyFormElements();

	$("#editTaxonomyDialog").dialog('setTitle','编辑').dialog('open');
}

function popupViewTaxonomyDetailDlg(val){
	$("#newTaxonomyItemBtn, #editTaxonomyItemBtn").show();
	$("#saveTaxonomyItemBtn, #closeTaxonomyItemBtn").hide();
	
	$("#viewTaxonomyDetailsDialog").dialog('open'); 
}
function delTaxonomyDlg(val){

}



//新增或者编辑之后，进行提交
function submitTaxonomy(){

	$("#editTaxonomyDialog").dialog('close');
}

//查看状态下，点击"编辑"按钮
function enableEditTaxonomy(){
	$("#editTaxonomyBtn").hide();
	$("#saveTaxonomyBtn, #closeTaxonomyBtn").show();
	enableTaxonomyFormElements();
	
}

//新增一个节点
function AddNewTaxonomyTerm(){

}

//编辑一个节点
function EditTaxonomyTerm(){
	$("#newTaxonomyItemBtn, #editTaxonomyItemBtn").hide();
	$("#saveTaxonomyItemBtn, #closeTaxonomyItemBtn").show();
	
}

function expandAll(){
	$('#taxonomy-tree').tree('expandAll');
}

function colapsedAll(){
	$('#taxonomy-tree').tree('collapseAll');
}

function appendTerm(){
	 var t = $('#taxonomy-tree');
		var node = t.tree('getSelected');
		t.tree('append', {
		parent: (node?node.target:null),
		data: [{
		text: 'new item1'
		}],
		});

		//clear the form 

		$("#myTaxonomyForm").form("clear");
		$("#newTaxonomyItemBtn, #editTaxonomyItemBtn").hide();
		$("#saveTaxonomyItemBtn, #closeTaxonomyItemBtn").show();
	


}
function editTerm(){
	var t = $('#taxonomy-tree');
	var node = t.tree('getSelected');
	var pNode = $('#taxonomy-tree').tree('getParent', node.target);
	$("#parent-name").html(pNode.text);
	$("#parent-nodeid").val(pNode.id);

	//use easyui form load the data below. ...
	$('#myTaxonomyForm').form('load','get_data.php');	// load from URL


}
function removeTerm(){
	var node = $('#taxonomy-tree').tree('getSelected');
	$.messager.confirm('确认删除？', '这将会删除整个节点以及子节点', function(r){
	if (r){
		
		$('#taxonomy-tree').tree('remove', node.target);
	}
	});

	
}

function selectedTaxonomyItem(obj){
	
	var t = $('#taxonomy-tree');
	var pNode = $('#taxonomy-tree').tree('getParent', obj.target);
	$("#parent-name").html(pNode.text);
	$("#parent-nodeid").val(pNode.id);

	//use easyui form load the data below. ...
	$('#myTaxonomyForm').form('load','get_data.php');	// load from URL

/*	$('#ff').form('load',{
		name:'name2',
		email:'mymail@gmail.com',
		subject:'subject2',
		message:'message2',
		language:5
	});
*/

}

/*************************************/
/*									 *
*									 *
*              订阅管理				 *
*									 */									
/*************************************/

function formatSubscribersOperations(value, row){

	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupEditTaxonomyDlg('+value+');">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delTaxonomyDlg('+value+');">删除</a>';

}

function formatSubStatus(value, row){

	if(value == 0){
		return '<span class="red">禁用</span>';
	}

	if(value == 1){
		return '<span class="green">订阅</span>';
	}
	if(value == 2){
		return '<span class="blue">启用</span>';
	}


}

/*************************************/
/*									 *
*									 *
*              模块管理				 *
*									 */									
/*************************************/
