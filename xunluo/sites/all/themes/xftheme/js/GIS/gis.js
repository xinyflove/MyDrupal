(function($){

	  		
})(jQuery);

//Show history track
function doUploadDiagram(map, pts, myIcon) {
    	alert('popup fileupload box');
        return false;
}

function addMarker(map, point, index, icon) {  
     /*   var myIcon = new BMap.Icon(icon, new BMap.Size(23, 25), {
            offset: new BMap.Size(10, 25)

        });
      */
        var makerName = "marker" + index;
     /*   makerName = new BMap.Marker(point, {
            icon: myIcon
        });
*/
        var makerName = new BMap.Marker(point);  // 创建标注
	
        map.addOverlay(makerName);
        makerName.addEventListener("click", function() {
           $("#gisPopDlg").dialog({
          // 	href:'http://www.xfyun.net',
           	onClose:function(){

           	}
           }).dialog('setTitle','设备1').dialog('open');

        });

}
