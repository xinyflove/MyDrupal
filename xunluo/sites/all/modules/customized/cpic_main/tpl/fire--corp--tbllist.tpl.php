
<div class="easyui-layout" data-options="fit:true">
    <div id="FireAreacorpTabs" class="easyui-tabs" data-options="fit:true,plain:true,showHeader:false">
        <div title="企业列表">
            <div class="easyui-layout" data-options="fit:true">
                <div class="maintop" data-options="region:'north',border:false">
                    <!-- <div class="main_header">
                        <div class="main_title">企业列表</div>
                        <div class="main_edit">
                            <ul class="editlist">
                                <li class="search_this">
                                    <input type="text" class="easyui-searchbox" data-options="prompt:'请输入关键字搜索',searcher:doSearch" />
                                </li>
                            </ul>
                        </div>
                    </div> -->
                    <!--main_header end-->
                </div>
                <!--maintop end-->
                <div class="main_data" data-options="region:'center',border:false">
                    <table id="AreaCorpDg">
                    </table>
                </div>
                <!--main_data end-->
            </div>
            <!--easyui-layout end-->
        </div>
        <div title="xxx企业列表">
            <div class="easyui-layout" data-options="fit:true">
                <div class="maintop" data-options="region:'north',border:false">
                    <div class="main_header">
                        <div class="main_title"><a href="javascript:void(0);" onclick="$('#FireAreacorpTabs').tabs({selected:0})">&lt;&lt;企业列表</a></div>
                        <div class="main_edit">
                            <ul class="editlist">
                                <li class="search_this">
                                    <input type="text" class="easyui-searchbox" data-options="prompt:'请输入关键字搜索',searcher:doSearch" />
                                </li>
                            </ul>
                        </div>
                    </div>
                    <!--main_header end-->
                </div>
                <!--maintop end-->
                <div class="main_data" data-options="region:'center',border:false">
                    <table id="AreaCorpBusinessDg">
                    </table>

                </div>
                <!--main_data end-->                            
            </div>
            <!--easyui-layout end-->
        </div>
    </div>
    <!--easyui-tabs end-->
</div>


<script type="text/javascript">
$(function(){
    // 消防巡检
    $('#AreaCorpDg').datagrid({
        data:[<?php print $dev;?>],
        columns:[<?php print $columns;?>], 
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
        pageSize:20,
        rowStyler: function(index,row){
            if (index%2 == 0){
                return 'background-color:#fafafa;';
            }
        },
        onClickCell: function(index, field, value) {
            
            $("#FireAreacorpTabs").tabs({

                selected: 1
            });
           $('#AreaCorpBusinessDg').datagrid({
                url:'/homepage/list/ajax/view/'+index+'/'+field,
                columns:[[  
                    {field:'nid',title:'NID',hidden:true},  
                    {field:'businesstype',title:'类型',width:50},    
                    {field:'title',title:'企业名称',width:70},    
                    {field:'belongsCustomer',title:'消防负责人',width:50},
                    {field:'belongsDealers',title:'电话',width:70},
                    {field:'address',title:'地址',width:70},
                    {field:'district',title:'行政区域',width:50}   
                ]],
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
                pageSize:20,
                rowStyler: function(index,row){
                    if (index%2 == 0){
                        return 'background-color:#fafafa;';
                    }
                },
                onClickRow: function(index, row){
                    $("#AreaCorpBusinessDg").datagrid('selectRow',index); // 选中当前行    
                    var row = $("#AreaCorpBusinessDg").datagrid('getSelected'); // 获得当前行的值;  

                    var url = "/homepage/" + row.nid;
                    $('#mainContent').panel('refresh',url,{
                      'type':2,
                    });        
                   
                }
            }); 

        },

    });
    
 
});

    
</script>