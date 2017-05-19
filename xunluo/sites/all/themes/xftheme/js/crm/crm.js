$(function(){
	//系统管理	
	$('#crmDg').treegrid({
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

})(jQuery);


function formatAssetList(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupAssetListDlg();">设备列表</a>';
}

function formatAccountList(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupAccoutListDlg();">人员列表</a>' ;

}

function formatOperations(value,row){
	return '<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="popupCustomerDetailDlg();">查看</a>&nbsp' +
			'&nbsp<a id="btn" href="#" class="easyui-linkbutton" data-options="" onClick="delCustomerDlg();">删除</a>';

}

function popupAssetListDlg(){
	alert('formatAccountList'); 
}
function popupAccoutListDlg(){
	alert('formatAccountList'); 
}
function popupCustomerDetailDlg(){
	alert('formatAccountList'); 
}
function delCustomerDlg(){
	alert('formatAccountList'); 
}
