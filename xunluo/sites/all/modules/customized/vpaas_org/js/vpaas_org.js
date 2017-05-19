var url; 
(function($){
$(document).ready(function() {
            
//start of logic
    $('#orgTree').tree({
        url:'/org/tree',
        lines:true,
        onClick: function(node){
            var menuUrl = $("#Nav").data('curUrl');
			arrMenuUrl = menuUrl.split("/");
			numUrl = arrMenuUrl.length;

            if(menuUrl.indexOf('kpi/rank') != -1)
            {
                // 综合排名
                if(node.attributes.type==='corp')
                {
                    $.messager.show({
                        title: '提示',
                        msg: "综合排名只能在区域或者行业类型上查询"
                    });
                }
                else
                {
                    $('#mainContent').panel('refresh', menuUrl+'/'+node.id);
                }
                
                return false;
            }

            if(menuUrl.indexOf('kpi/static') != -1)
            {
                // 数据统计
                if(node.attributes.type!=='corp')
                {
                    $.messager.show({
                        title: '提示',
                        msg: "请至少选择一家企业进行查看"
                    });
                    
                }
                else
                {
                    $('#mainContent').panel('refresh', 'kpi/data');
                }
                return false;
            }
			
			if(numUrl == 2 || menuUrl.indexOf('map') != -1)
			{
				var isMap = 1;
			}
			else
			{
				var isMap = 0;
			}
            
            if(node.attributes.type==='corp'){
                //var menuUrl = $("#Nav a.active").attr('href');
                
                if(menuUrl.indexOf('kpi') == -1){ //不是KPI页面
					// 如果点击是企业 显示企业消防信息
					if(menuUrl.indexOf('map') > 0 || menuUrl.indexOf('list') > 0) menuUrl = '/homepage';
                    var url = menuUrl+'/'+node.attributes.type+'/'+node.attributes.nid;
                    
                    $('#mainContent').panel('refresh',url,{
                        'type':2,
                    });

                }else{  //KPI分析
                    var subMenuUrl = $("#kpi-mainContent ul.submenu li a.active").attr('url');
                    var url = subMenuUrl  +'/'+node.attributes.type+'/'+node.attributes.nid;
                    $('#mainContent').panel('refresh',url,{
                        'type':2,
                    });
                }                
                return false;
    
            }
            else if (node.attributes && (node.attributes.type == 'city' || node.attributes.type == 'district')) {
                if($("#Nav ul.sf-menu li ul li a").attr('active') == null )
                { 
                    if(isMap)
                    {
                        changeHomeageBmap(node.id,node.attributes.lnglat);
                    }
                    else
                    {
						nodeStr = node.id;
						nodeArr = nodeStr.split("-");
						nodeNum = nodeArr.length;
						
                        $('#mainContent').panel('refresh', menuUrl+'/'+nodeArr[0]+'/'+nodeArr[nodeNum-1]);
                        //console.log('log1', menuUrl+'/'+nodeArr[0]+'/'+nodeArr[nodeNum-1]);
                    }
                    
                }
                else if ($("#Nav ul.sf-menu li ul li a.active").attr('url').indexOf('homepage') >= 0) 
                {
                    if(isMap)
                    {
                        changeHomeageBmap(node.id,node.attributes.lnglat);
                    }
                    else
                    {
                        //console.log('log2', menuUrl+node.id);
                    }
                    
                };  
                // var url = "/homepage/" + node.attributes.type + "/" + node.attributes.nid;
                // $('#mainContent').panel('refresh',url,{
                //     'type':2,
                // });                                  
            };
          
	},
        onDblClick:function(node){
                    if(node.attributes && (node.attributes.type == 'district' || node.attributes.type == 'btype' )) {
 
                    $('#kpi-mainContent').panel('refresh',node.attributes.url,{
                        'type':2,
                    });
                }
           },
        onContextMenu: function(e,node){
                    e.preventDefault();
                    $(this).tree('select',node.target);
                   if(node.attributes && (node.attributes.type == 'btype' )) {

                        $('#mm').menu('show',{
                            left: e.pageX,
                            top: e.pageY
                        });
                    }
                   if(node.attributes && (node.attributes.type == 'corp' )) {

                        $('#mmcorp').menu('show',{
                            left: e.pageX,
                            top: e.pageY
                        });
                    }


        }
                
                
    });

    $('#checkedOrgTree').tree({
        url:'/org/tree',
        lines:true,
        checkbox:true,
        cascadeCheck:false,
        onClick: function(node){
         
        },
        onBeforeCheck:function(node, checked){
            var nodes = $('#checkedOrgTree').tree('getChecked');
            if(nodes.length > 1){
                
                for(var i=0; i<nodes.length; i++){
                    if(nodes[i].attributes.type.indexOf(node.attributes.type) == -1){
                        $.messager.show({
                            title: '提示',
                            msg: "只能选择同等单位进行比较"
                        });

                        return false;
                    } 
                }
            }

            if(nodes.length > 4){
                $.messager.show({
                        title: '提示',
                        msg: "最多选择4家对比单位"
                    });
                return false; 

            }

        },
        onCheck:function(node){
            

        }
    });


   /* $('#recentTree').tree({
        url:'/org/recenttree',
        lines:true,
        onClick: function(node){
            if(node.attributes.type==='corp'){
                
                var url = $("#Nav a.active").attr('href')+'/'+node.attributes.nid;
                $('#mainContent').panel('refresh',url,{
                    'type':2,
                });
                return false;
    
            }
	}
    });
    */
     //    $('#search_input').fastLiveFilter('#orgTree');

//end of logic
});
})(jQuery);


function appendOrg(){
    var selectedNode = $("#orgTree").tree('getSelected');
    if(selectedNode == null || selectedNode.attributes.type != 'btype'){
           $.messager.show({
                            title: '提示',
                            msg: "只能在区下面某行业类型进行操作"
                        });

                        return false;
                    
    }
    ss = selectedNode.id.split("-");// 在每个逗号(,)处进行分解。
    $('#orgfm').form('clear');
    $("#orgDlg").dialog('open').dialog('setTitle', '添加企业');
     
    url = "/org/ajax/add/"+ss[3]+"/"+ ss[4];
                    
}

function saveCorp() {
        
        $('#orgfm').form('submit', {
            url: url,
            onSubmit: function() {
                return $(this).form('validate');
            },
            success: function(result) {
                var result = eval('(' + result + ')');
                if (result.errorMsg) {
                    $.messager.show({
                        title: 'Error',
                        msg: result.errorMsg
                    });
                } else {
                    $('#orgDlg').dialog('close'); // close the dialog
                    var selectedNode = $("#orgTree").tree('getSelected');
                    var pnode = $("#orgTree").tree('getParent',selectedNode); 
                    $("#orgTree").tree('reload', pnode);
                }
            }
        });
    }
    
function updateOrg(){
    var selectedNode = $("#orgTree").tree('getSelected');
    if(selectedNode == null || selectedNode.attributes.type != 'corp'){
           $.messager.show({
                            title: '提示',
                            msg: "只能修改某企业"
                        });

                        return false;
                    
    }
    var url = '/org/edit/'+selectedNode.id;
          $('#mainContent').panel('refresh',url,{
                        'type':2,
                    });

}

function removeOrg(){
       var selectedNode = $("#orgTree").tree('getSelected');
       var pnode = $("#orgTree").tree('getParent',selectedNode); 
       if(selectedNode == null || selectedNode.attributes.type != 'corp'){
            $.messager.show({
                            title: '提示',
                            msg: "只能删除企业"
                        });

                        return false;
          
    }
    var deleteUrl = "/org/ajax/delete/"+selectedNode.id;
    $.messager.confirm('Confirm', '你确定删除?', function(r) {
                if (r) {
                    $.post(deleteUrl, {id: selectedNode.id}, function(result) {
                       if (result.success) {
                            $("#orgTree").tree('reload', pnode);
                            
                        } else {
                            $.messager.show({// show error message
                                title: 'Error',
                                msg: result.errorMsg
                            });
                        }
                    }, 'json');
                }
            });
    
}
