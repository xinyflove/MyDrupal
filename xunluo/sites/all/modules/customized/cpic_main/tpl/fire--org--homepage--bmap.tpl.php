<script type="text/javascript" src='http://api.map.baidu.com/api?v=2.0&ak=<?php print $mapkey; ?>'></script>

<div>欢迎登陆管理界面！</div>

<div id="map-container" style="width:100%; height:600px" class="gis-map">这是地图显示的区域。。。</div>

<script type="text/javascript">



            //scripts start
            //set global icon
            var offIcon = new BMap.Icon("/sites/all/modules/customized/fire_main/images/green.png", new BMap.Size(32, 70), {//小车图片
                //offset: new BMap.Size(0, -5),    
                imageOffset: new BMap.Size(0, 0)
            });
            var map = new BMap.Map("map-container");
         //   map.setCurrentCity("济南");
            //    var point = new BMap.Point(120.420127,36.104052);
			var lnglat = "<?php print $lnglat; ?>";
            var loc = lnglat.split(',');
            var point = new BMap.Point(loc[0],loc[1]);

            map.centerAndZoom(point, 15);
            map.addControl(new BMap.NavigationControl());  //添加默认缩放平移控件
            map.enableScrollWheelZoom();

            $.post("/fire_main/bmap/ajax/getall/<?php print $id_str; ?>",
                    {
                    },
                    function(result) {
                        var points = result.data;
                        if(points != null)
                        {
                          var paths = points.length;    //获得有几个点
                          var opts = {
                            width : 300,     // 信息窗口宽度
                            height: 20,     // 信息窗口高度
                            title : '' , // 信息窗口标题
                          }
                          var newp = new BMap.Point(points[0].lng, points[0].lat);
                          map.panTo(newp);

                          //   var pts = new Array();
                          for (var i = 0; i < paths; i++) { //draw on each road
                              var pt = new BMap.Point(points[i].lng, points[i].lat);
                              var plantName = points[i].name;
                              var url='<a href="javascript:void(0)" onclick="mapGoto(' + points[i].nid +')">' + plantName + '</a>';
                              var marker = new BMap.Marker(pt,{icon:offIcon});  // 创建标注
                              map.addOverlay(marker);               // 将标注添加到地图中

                              addMouseoverHandler(url,marker);

                          }      
                        }

                        function addMouseoverHandler(content,marker){
                          marker.addEventListener("mouseover",function(e){
                            openInfo(content,e)}
                          );
                          // marker.addEventListener("mouseout", function(){          
                          //   map.closeInfoWindow(); //关闭信息窗口
                          // });                           
                        }
                        function openInfo(content,e){
                          var p = e.target;
                          var point = new BMap.Point(p.getPosition().lng, p.getPosition().lat);
                          var infoWindow = new BMap.InfoWindow(content,opts);  // 创建信息窗口对象 
                          map.openInfoWindow(infoWindow,point); //开启信息窗口
                        }
                    });
            
            //scripts end






function writeObj(obj){ 
	var description = ""; 
	for(var i in obj){   
		var property=obj[i];   
		description+=i+" = "+property+"\n";  
	}   
	alert(description); 
} 

</script>