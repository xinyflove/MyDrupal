(function($) {
    Drupal.behaviors.onlinechat = {
        attach: function(context, settings) {
            //scripts start
        if('WebSocket' in window){
             console.log('开始创建连接，trying。。。');
             var jwt = Drupal.settings.onlinechat.jwt;
             var from = Drupal.settings.onlinechat.from;
             var to = Drupal.settings.onlinechat.to;

            var sock = new WebSocket("ws://121.42.173.144:10001/app");
                //    var socket = io.connect('http://121.42.173.144:10001');
             //       var sock = new SockJS('http://121.42.173.144:10001/app');
                    sock.onopen = function() {
                        $("span.chat-status").html('连接已经建立,可以发送消息给'+to);
                         var jsonObj2 = { j:jwt,u:from};
                         var jsonStr = JSON.stringify( jsonObj2 );

                         sock.send(jsonStr);
                        console.log("state 2 ="+sock.readyState);//查看websocket当前状态
                        var helloStr = '您好'+to;
                         var jsonObj1 = {fm:from, u:from,to:to,e:helloStr,atn:'s_t',j:jwt};
                         var jsonStr1 = JSON.stringify( jsonObj1 );

                         sock.send(jsonStr1);
                         $('#Interlocution').append('<div class="leftConment"><div class="talker"><img width="68" height="68" alt="" src="/sites/all/modules/customized/onlinechat/images/boy.png"></div><div class="speakContent"><div class="icon"></div><div class="contentBox">'+helloStr+'</div></div></div>');

                          //监听回车事件
                          $('input.inputMessage').bind('keyup', function(event) {
                            if (event.keyCode == "13") {
                                //回车发送
                                var sendText = $(this).val();
                                var jsonObj1 = {fm:from, u:from,to:to,e:sendText,atn:'s_t',j:jwt};
                                var jsonStr1 = JSON.stringify( jsonObj1 );
                                sock.send(jsonStr1);
                                $('#Interlocution').append('<div class="leftConment"><div class="talker"><img width="68" height="68" alt="" src="/sites/all/modules/customized/onlinechat/images/boy.png"></div><div class="speakContent"><div class="icon"></div><div class="contentBox">'+sendText+'</div></div></div>');
                                $("#InterlocutionWrap").scrollTop($("#Interlocution").height());
                         
                            }
                        });




                    };
                    sock.onmessage = function(e) {
                        console.log('message', e.data);
                        var jsonObj = JSON.parse(e.data)
                        for(i=0; i<jsonObj.length; i++){
                            if(jsonObj[i].s == 'm_i'){ //推送过来的消息
                                var msg = jsonObj[i].e;
                                $('#Interlocution').append('<div class="rightConment"><div class="talker"><img width="68" height="68" alt="" src="/sites/all/modules/customized/onlinechat/images/girl.jpg"/></div><div class="speakContent"><div class="icon"></div><div class="contentBox">'+msg+'</div></div></div>');
                                $("#InterlocutionWrap").scrollTop($("#Interlocution").height());
                            var notifyTime = Drupal.settings.onlinechat.notification_time;
                            if (notifyTime > 0) {
                              $.jGrowl(msg, {header: '广播通知', life:(notifyTime * 1000)});
                            }
                            else {
                              $.jGrowl(msg, {header: '广播通知', sticky:true});
                            }
                            }
                        }
                         if(jsonObj.c==2003){
                                                   updateCoversationStatus('用户信息身份不对');
                                                   return; 
                                                }
                        if(jsonObj.c==70001){
                            $("span.chat-status").html('发送失败，重新发送中....'+to);

                        }else if(jsonObj.c==70000){
                            $("span.chat-status").html('发送成功'+to);
                            
                        }else{
                             
    
                        }
                    };
                    sock.onclose = function() {
                        updateCoversationStatus('由于长时间不说话，服务器主动关闭');
                    };
                     sock.onerror = function (e) {
                        updateCoversationStatus('连接出现错误，重新连接');
                     }

        
            }else{
                    alert('本浏览器不支持WebSocket哦~');
            }
            //scripts end

        }
    }

function updateCoversationStatus(text){
        $("span.chat-status").html(text);
}

})(jQuery);