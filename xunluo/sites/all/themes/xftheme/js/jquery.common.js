/* -------------------------------------------------------------------
	* 共通関数実行
	* init
 ------------------------------------------------------------------- */
var $=jQuery; 
$(function(){
	 $("#Nav").data("curUrl","/homepage");

	var winW = $(window).width();
	var winH = $(window).height();
	$(".main .fullimg img").width(winW - 431);	
	$(".main .fullimg img") .height(winH - 60);
	$(".viewTactics").width(winW);
	$(".viewTactics") .height(winH -86);
	$(window).resize(function(){
		winW = $(window).width();
		winH = $(window).height();
		$(".main .fullimg img").width(winW - 431);		
		$(".main .fullimg img") .height(winH - 60);
		$(".viewTactics").width(winW);
		$(".viewTactics") .height(winH -86);
	});
	
	
	
	dataBlockOver();
	imageOver();
	
	//nav下拉菜单的active样式
	$(".sf-menu").children("li").children("a").click(function(){
		$(".sf-menu").children("li").children("a").removeClass("active");
		$(this).addClass("active");
	});
	$(".sf-menu").children("li").children("ul").children("li").children("a").click(function(){
		$(".sf-menu").children("li").children("a").removeClass("active");
		$(".sf-menu").children("ul").children("li a").removeClass("active");
		$(this).addClass("active");
		$(this).parent("li").parent("ul").siblings("a").addClass("active");
		/*$(this).parent("li").parent("ul").parent("ul.sf-menu").children("li").children("a").addClass("active");*/
		
		$(this).parent("li").parent("ul").animate({
			opacity: 0
		},300);
	});
})

 
function dataBlockOver(){
	
	$(".data-block").mouseover(function(){
		var color = $(this).attr('color');
		$(this).addClass('bg-'+color);
	})
	.mouseleave(function(){
		var color = $(this).attr('color');
		$(this).removeClass('bg-'+color);
	});


}

//图片悬停设置
function imageOver() {
 
	$("img.rollover").each(function() {
 
		//读取旧的图像文件名，获取新的文件名称
		var image = this.src;
		var extension = image.substr(image.lastIndexOf("."), image.length-1);
		var image_over = image.replace(extension, "_on"+extension);
 
		//读取图像文件名称
		new Image().src = image_over;
 
		//鼠标悬停时图片的src设置
		$(this).hover(
			function(){this.src = image_over},
			function(){this.src = image}
		);
	});
}
// 页眉下拉列表
$(function(){


	$(".sf-menu li ul").children("li").click(function(){
		$(this).parent().fadeOut("fast");
	});


/*下拉菜单 */
	/*$(".sf-menu li").hover(function(){
		$(".sf-menu li ul").stop().css("z-index","10000").fadeOut();
		$(this).children('ul').stop().css("z-index","1000000").animate({
			opacity: 1
		},300).fadeIn();
		window.clearTimeout(window.timer_nav);
	},function(){	
		window.timer_nav = window.setTimeout(function(){
			$(this).children('ul').stop().css("z-index","10000").fadeOut();
		},500);
	});

	$(".sf-menu li ul").hover(function(){
		$(this).stop().css("display","block").animate({
			opacity: 1
		},300).fadeIn();
		window.clearTimeout(window.timer_nav);
	},function(){
		$(this).fadeOut();
	});*/

	//下拉菜单 
	$(".sf-menu").children("li").hover(function(){
		$(".sf-menu li ul").stop().css("z-index","10000").fadeOut();
		$(this).children('ul').stop().css("z-index","1000000").animate({
			opacity: 1
		},300).fadeIn();
		window.clearTimeout(window.timer_nav);
	},function(){	
		window.timer_nav = window.setTimeout(function(){
			$(".sf-menu").children("li").children('ul').stop().css("z-index","10000").fadeOut();
		},500);
	});

	$(".sf-menu li ul").hover(function(){
		$(this).stop().css("display","block").animate({
			opacity: 1
		},300).fadeIn();
		$(this).siblings("a").addClass("active");
		window.clearTimeout(window.timer_nav);
	},function(){
		$(this).fadeOut();
		$(this).siblings("a").removeClass("active");
	});






	/*用户信息*/
	$(".userInfo .info").hover(function(){
		$(".infomore").stop().css("z-index","1000000").animate({
			opacity: 1
		},300).fadeIn();
		$(".usermore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer);
	},function(){	
		window.timer = window.setTimeout(function(){
			$(".infomore").stop().css("z-index","10000").fadeOut();
		},500);
	});
	$(".infomore").hover(function(){
		$(this).stop().css("display","block").animate({
			opacity: 1
		},300).fadeIn();
		$(".usermore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer);
	},function(){
		$(this).fadeOut();
	});
	
	
	$(".userInfo .user").hover(function(){
		//$(".usermore").stop().css("z-index","1000000").fadeIn();
		$(".usermore").stop().css("z-index","1000000").animate({
			opacity: 1
		},300).fadeIn();
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer2);
	},function(){		
		window.timer2 = window.setTimeout(function(){
			$(".usermore").stop().css("z-index","10000").fadeOut();
		},500);
	});
	$(".usermore").hover(function(){
		$(this).stop().css("display","block").animate({
			opacity: 1
		},300).fadeIn();
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer2);
	},function(){
		$(this).fadeOut();
	});


	$(".userInfo .skin").hover(function(){
		$(".skinmore").stop().css("z-index","1000000").animate({
			opacity: 1
		},300).fadeIn();
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".usermore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer3);
	},function(){		
		window.timer3 = window.setTimeout(function(){
			$(".skinmore").stop().css("z-index","10000").fadeOut();
		},500);
	});
	$(".skinmore").hover(function(){
		$(this).stop().css("display","block").animate({
			opacity: 1
		},300).fadeIn();
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".usermore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer3);
	},function(){
		$(this).fadeOut();
	});

	//换肤切换效果
	$(".skin01,.skin02").click(function(){
		$(".chosen").remove();
		$(this).append('<span class="chosen"></span>');
		$(".chosen").css("display","block");
	});


});
//页眉下拉列表弹框调用的函数
function submitForm(){
	$('#HeaderForm01').form('submit');
}
function clearForm(){
	$('#HeaderForm01').form('clear');
	$('#ResetUserInfo').dialog('close');
}

function submitPWForm(){
	$('#HeaderForm02').form('submit');
}
function clearPWForm(){
	$('#HeaderForm02').form('clear');
	$('#ResetPW').dialog('close');
}

function submitLogForm(){
	$('#HeaderForm03').form('submit');
}
function clearLogForm(){
	$('#HeaderForm03').form('clear');
	$('#SubmitLog').dialog('close');
}

//全局通用函数
function resetForm(formID){
	$("#"+formID).form('reset');
}

function doSearch(value){
     alert('You input: ' + value);
}
/*上部导航点击事件*/
function refreshContent(obj)
{
    var url = $(obj).attr('url');
    var selectedNode = $("#orgTree").tree('getSelected');

    $("#Nav").data("curUrl",url);

    if(url.indexOf('kpi/compare') != -1)
    {
    	//KPI compare页面
        window.location.href= url;
        return false;
    }
    
    if(url.indexOf('kpi/rank') != -1)
    {
    	//KPI rank页面
	    if(selectedNode == null || selectedNode.attributes.type == 'corp')
	    {
	    	// 没有选中组织机构 或 选中企业    
	        $.messager.show({
                title: '提示',
                msg: "综合排名只能在区域或者行业类型上查询"
            });
	    }
	    else
	    {
	    	$('#mainContent').panel('refresh',url+'/'+selectedNode.id);
	    }
	    return false;
    }

    if(url.indexOf('kpi/static') != -1)
    {
    	//KPI 数据统计
	    if(selectedNode == null || selectedNode.attributes.type != 'corp')
	    {
	    	// 没有选中组织机构 或 选中企业    
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
    
    if((url.indexOf('homepage') == -1) && (selectedNode == null ||  selectedNode.attributes.type != 'corp'))
    {
    	// 链接不是含有homepage 并且 (没有选中组织机构 或 没有选择企业)
	    $.messager.show({
            title: '提示',
            msg: "请至少选择一家企业进行查看"
        });
        return false;
    }

    $("ul.sf-menu li ul li a").removeClass("active");
    $("ul.sf-menu li a").removeClass("active");
    $(obj).addClass('active');
	
    if ((url.indexOf('homepage') >= 0 ) && selectedNode == null) 
    {
		// 如果链接有homepage 且 没有选中组织机构
		if(url.indexOf('map') >= 0)
		{
			$('#mainContent').panel('refresh',url+'/province-62');
		}
    	else
		{
			$('#mainContent').panel('refresh',url+'/province/62');
		}
    }
    else
	{
		if(url.indexOf('map') >= 0)
		{
			if(selectedNode.attributes.type == 'corp')
			{
				//$('#mainContent').panel('refresh','/homepage/corp/'+selectedNode.id);
				// 待处理 选择企业时，点击地图
			}
			else
			{
				$('#mainContent').panel('refresh',url+'/'+selectedNode.id);
			}
		}
		else
		{
			$('#mainContent').panel('refresh',url+'/'+selectedNode.attributes.type+'/'+selectedNode.attributes.nid);
		}
    }    
    return false; 
}
 
function switchInspectPage(obj){
    var curTab = $("#nav-tabs").tabs('getSelected');


    var selectedNode = $("#orgTree").tree('getSelected');
    if(selectedNode == null){
        $.messager.show({
                        title: '提示',
                        msg: "请至少选择一家企业进行查看"
                    });
        return false; 
    }

    $("#inspect-mainContent ul.submenu li a").removeClass("active");
    $(obj).addClass('active');

    var url = $(obj).attr('url');
    $('#mainContent').panel('refresh',url+'/'+selectedNode.attributes.type+'/'+selectedNode.attributes.nid);
    return false;
}
    
    
function switchKPIDataPage(obj){
    var curTab = $("#nav-tabs").tabs('getSelected');
    var selectedNode = $("#orgTree").tree('getSelected');
    if(selectedNode == null){
        $.messager.show({
                        title: '提示',
                        msg: "请至少选择一家企业进行查看"
                    });
        return false; 
    }

    $("#kpi-mainContent ul.submenu li a").removeClass("active");
    $(obj).addClass('active');

    var url = $(obj).attr('url');
    $('#mainContent').panel('refresh',url+'/'+selectedNode.attributes.nid);
    return false;
}

function switchKPIComparePage(obj){
    var curTab = $("#nav-tabs").tabs('getSelected');
    var checkedNodes = $('#checkedOrgTree').tree('getChecked');
    var type = 'corp';
             
    if(checkedNodes == null){
        $.messager.show({
                        title: '提示',
                        msg: "请至少选择2至4家企业进行查看"
                    });
        return false; 
    }

    if(checkedNodes.length < 2 || checkedNodes.length >4 ){
		$.messager.show({
                        title: '提示',
                        msg: "请选择2至4家企业进行查看"
                    });
        return false; 
    }
    var checkNids= [];

    for(var i=0; i<checkedNodes.length; i++){
    	checkNids.push(checkedNodes[i].attributes.nid);
        type = checkedNodes[i].attributes.type;
    }

    $("#kpi-mainContent ul.submenu li a").removeClass("active");
    $(obj).addClass('active');

    var url = $(obj).attr('url');
    $('#mainContent').panel('refresh',url+'/'+type+'/'+checkNids.join('-'));
    return false;
}
        
