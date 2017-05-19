

$(function(){
	//巡检筛选
	$("#box a").click(function(){
        $("#box a").removeClass("active");  
        $(this).addClass("active");
    });
	//告警管理
	$("#ChectList a").click(function(){
        $("#ChectList a").removeClass("active");  
        $(this).addClass("active");
    });
	//系统管理	
	$('#assetDg').datagrid({
		url:'assets.json',
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

function batchDelAsset(){

}

function retrieveAllAssets(){
	$('#fetchDeviceProgBarDlg').dialog('open');
}

function calculateProgressBar(){
	 var value = $('#fetchProgBar').progressbar('getValue');
	 if (value < 100){
		value += Math.floor(Math.random() * 10);
		$('#fetchProgBar').progressbar('setValue', value);
		setTimeout(arguments.callee, 200);
	}
} 

