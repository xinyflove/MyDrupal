/* -------------------------------------------------------------------
	* 共通関数実行
	* init
 ------------------------------------------------------------------- */
var $=jQuery; 
$(function(){
	
	var winW = $(window).width();
	var winH = $(window).height();
	$(".main .fullimg img").width(winW - 431);	
	$(".main .fullimg img") .height(winH - 60);
		$("#whole .fullimg img").width(winW);	
	$("#whole .fullimg img") .height(winH);

	$(".viewTactics").width(winW);
	$(".viewTactics") .height(winH -86);
	$(window).resize(function(){
		winW = $(window).width();
		winH = $(window).height();
		$(".main .fullimg img").width(winW - 431);		
		$(".main .fullimg img") .height(winH - 60);
		$("#whole .fullimg img").width(winW);	
		$("#whole .fullimg img") .height(winH);
		$(".viewTactics").width(winW);
		$(".viewTactics") .height(winH -86);
	});
	
	
	
	dataBlockOver();
	imageOver();
        //start of logic
    $('#orgTree').tree({
        url:'/org/tree',
        lines:true,
        onClick: function(node){
            if(node.attributes.type==='m'){
                
                var url = $("#Nav a.active").attr('href')+'/'+node.attributes.type+'/'+node.attributes.devId;
                $('#mainContent').panel('refresh',url,{
                    'type':2
                });
                return false;
    
            }

            if(node.attributes.type==='c'){ //播放摄像头
               
               videoplayFrame.window.startPlay(node.attributes.devId);
                return false;
    
            }

	}
    });
    $('#recentTree').tree({
        url:'/org/recenttree',
        lines:true,
        onClick: function(node){
            if(node.attributes.type==='corp'){
                
                var url = $("#Nav a.active").attr('href')+'/'+node.attributes.nid;
                $('#mainContent').panel('refresh',url,{
                    'type':2
                });
                return false;
    
            }
	}
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
	$(".userInfo .info").hover(function(){
		$(".infomore").stop().css("z-index","1000000").fadeIn();
		$(".usermore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer);
	},function(){	
		window.timer = window.setTimeout(function(){
			$(".infomore").stop().css("z-index","10000").fadeOut();
		},500);
	});
	$(".infomore").hover(function(){
		$(this).stop().css("display","block");
		$(".usermore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer);
	},function(){
		$(this).fadeOut();
	});
	
	
	$(".userInfo .user").hover(function(){
		$(".usermore").stop().css("z-index","1000000").fadeIn();
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer2);
	},function(){		
		window.timer2 = window.setTimeout(function(){
			$(".usermore").stop().css("z-index","10000").fadeOut();
		},500);
	});
	$(".usermore").hover(function(){
		$(this).stop().css("display","block");
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".skinmore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer2);
	},function(){
		$(this).fadeOut();
	});


	$(".userInfo .skin").hover(function(){
		$(".skinmore").stop().css("z-index","1000000").fadeIn();
		$(".infomore").stop().css("z-index","10000").fadeOut();
		$(".usermore").stop().css("z-index","10000").fadeOut();
		window.clearTimeout(window.timer3);
	},function(){		
		window.timer3 = window.setTimeout(function(){
			$(".skinmore").stop().css("z-index","10000").fadeOut();
		},500);
	});
	$(".skinmore").hover(function(){
		$(this).stop().css("display","block");
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
