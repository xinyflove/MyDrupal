
<div class="easyui-layout" data-options="fit:true">
    <div data-options="region:'west',border: false" style="width: 40%;">
        <div class="easyui-layout" data-options="fit:true">
            <div data-options="region:'center',border: false" style="padding-bottom:0px;">
                <div class="block_full block_full_bg01">
                    <h2 class="admin_ttl01"><span class="bg01">消防安全评估</span></h2>
                    <div id="data-chart-safeindex" style="height:260px;"></div>
                    <div class="admin_point">
                    <!--	<p class="point_p">扣分项</p>
                        <p class="point_p">日常巡检率80%=80分</p>
                        <p class="point_p">水系统合格率95%=95分</p>  -->
                    </div>
                </div>
            </div>
        </div>
    </div>
    
    <!--west end-->
    <div data-options="region:'center',border: false" style="width: 40%; padding: 0 15px;">
        <div class="easyui-layout" data-options="fit:true">
            <div data-options="region:'north',border: false" style="height:30%; padding-bottom:5px;">
                <div class="block_full block_full_bg04" style="width:31%; float:left;">
                    <h2 class="admin_ttl01"><span class="bg06">巡检率</span></h2>
                    <div class="admin_text_box03"><?php echo $dev['irate'];?></div>
                </div>
                <div class="block_full block_full_bg05" style="width:31%; float:left; margin-left:15px;">
                    <h2 class="admin_ttl01"><span>维保率</span></h2>
                    <div class="admin_text_box03"><?php echo $dev['mrate'];?></div>
                </div>
                <div class="block_full block_full_bg07" style="width:31%; float:left; margin-left:15px;">
                    <h2 class="admin_ttl01"><span class="bg07">报警</span></h2>
                    <div class="admin_text_box04"><span class="ft60"><?php echo $dev['alarm'];?></span>条</div>
                </div>
            </div>
            <div class="blocl_center" data-options="region:'center',border: false">
                <div class=" block_center_left" style="width:49%; float:left;" >
                    <div class="block_full block_full_bg03" >
                        <h2 class="admin_ttl01"><span class="bg05">水系统</span></h2>
                        <div class="admin_text_box01 pb10">
                            <?php if(isset($dev['waterpress'][2])): ?>
                            <p class="admin_text_set01">消火栓压力： (<span><?php print $dev['waterpress'][2][0]['threshold'];?></span>Mpa)</p>
                            <p class="admin_text_set02"><?php print $dev['waterpress'][2][0]['location'];?>：<?php print $dev['waterpress'][2][0]['name'];?> — <span><?php print $dev['waterpress'][2][0]['value'];?></span>Mpa</p>
                            <?php if(isset($dev['waterpress'][2][1])): ?>
                            <p class="admin_text_set02"><?php print $dev['waterpress'][2][1]['location'];?>：<?php print $dev['waterpress'][2][1]['name'];?> — <span><?php print $dev['waterpress'][2][1]['value'];?></span>Mpa</p>
                            <?php endif; ?>
                            <?php endif; ?>
                        </div>
                        <div class="admin_text_box02">
                            <?php if(isset($dev['waterpress'][1])): ?>
                            <p class="admin_text_set01">喷淋末端压力： (<span><?php print $dev['waterpress'][1][0]['threshold'];?></span>Mpa)</p>
                            <p class="admin_text_set02"><?php print $dev['waterpress'][1][0]['location'];?>：<?php print $dev['waterpress'][1][0]['name'];?> — <span><?php print $dev['waterpress'][1][0]['value'];?></span>Mpa</p>
                            <?php if(isset($dev['waterpress'][1][1])): ?>
                            <p class="admin_text_set02"><?php print $dev['waterpress'][1][1]['location'];?>：<?php print $dev['waterpress'][1][1]['name'];?> — <span><?php print $dev['waterpress'][1][1]['value'];?></span>Mpa</p>
                            <?php endif; ?>
                            <?php endif; ?>
                        </div>
                        <div class="admin_text_box02">
                            <?php if(isset($dev['waterpress'][3])): ?>
                            <p class="admin_text_set01">高温水箱： (<span><?php print $dev['waterpress'][3][0]['threshold'];?></span>Mpa)</p>
                            <p class="admin_text_set02"><?php print $dev['waterpress'][3][0]['location'];?>：<?php print $dev['waterpress'][3][0]['name'];?> — <span><?php print $dev['waterpress'][3][0]['value'];?></span>米</p>
                            <?php if(isset($dev['waterpress'][3][1])): ?>
                            <p class="admin_text_set02"><?php print $dev['waterpress'][3][1]['location'];?>：<?php print $dev['waterpress'][3][1]['name'];?> — <span><?php print $dev['waterpress'][3][1]['value'];?></span>米</p>
                            <?php endif; ?>
                            <?php endif; ?>
                        </div>
                    </div>
                </div>
                <!-- video -->
                <div class=" block_center_right" style="width:49%; float:right;" >
                    <div class="block_full block_full_bg02" style="height:50%;">
                        <div class="admin_ttl01"><span class="bg02">视频监控</span></div><br />
                        <!--<div class="admin_time">
                            <p class="admin_date">
                                <?php list($date,$time)= explode(' ',$dev['frielane']->alarmtime); print $date; ?>
                            </p>
                            <p class="admin_date_time">
                                <?php list($date,$time)= explode(' ',$dev['frielane']->alarmtime); print $time; ?>
                            </p>
                        </div>-->
                        <div class="admin_video"><img width="300" height="222" src="<?php $imgs = explode('|', $dev['controlroom']->imgurl); print $imgs[0] ; ?>" alt="" /></div><br />
                        <div class="admin_ttl01"><span class="bg02">中控室监控</span></div><br />
                        <!--<div class="admin_time">
                            <p class="admin_date">
                                <?php list($date,$time)= explode(' ',$dev['frielane']->alarmtime); print $date; ?>
                            </p>
                            <p class="admin_date_time">
                                <?php list($date,$time)= explode(' ',$dev['frielane']->alarmtime); print $time; ?>
                            </p>
                        </div>-->
                        <div class="admin_video"><img width="300" height="222" src="<?php $imgs = explode('|', $dev['frielane']->imgurl); print $imgs[0] ; ?>" alt="" /></div><br />
                        <div class="admin_ttl01"><span class="bg02">消防通道</span></div><br />
                    </div>
                    
                </div>
                <!-- video end --> 
                
                <!--easyui-layout end--> 
            </div>
        </div>
    </div>
    <!--easyui-layout end--> 
    <div class="admin_tab" data-options="region:'south',border: false">
    	<table class="tab">
        	<tr>
            	<td>二维码张贴数量</td>
                <td><?php print $dev['qrcode_number']; ?>张</td>
                <td>消火栓压力监控点</td>
                <td><?php print $dev['xhs_number']; ?>个</td>
                <td>喷淋压力监控点</td>
                <td><?php print $dev['plmd_number']; ?>个</td>
            </tr>
            <tr>
            	<td>水箱水位监控点</td>
                <td>0</td>
                <td>视频监控点</td>
                <td>2个</td>
                <td></td>
                <td></td>
            </tr>
        </table>
    </div>
</div>
<!--center end-->
<div data-options="region:'east',border: false" style="width: 20%;">
    <div class="easyui-layout" data-options="fit:true">
        <div data-options="region:'north',border: false" style="height:75%; padding-bottom:5px;">
            <div class="block_full block_full_bg06">
                <h2 class="admin_ttl01"><span class="bg03">水位监测</span></h2>
                <div class="admin_text_box01">
                    <?php if(isset($dev['waterpress'][3])): ?>
                    <p class="admin_text_set01">水池 —
                    <p class="admin_text_set02"><?php print $dev['waterpress'][3][0]['value'];?></p>
                    <?php else: ?>
                    <p class="admin_text_set01">暂无数据</p>
                    <?php endif;  ?>
                    <?php if(isset($dev['waterpress'][4])): ?>
                    <p class="admin_text_set01">水箱—
                    <p class="admin_text_set02"><?php print $dev['waterpress'][4][0]['value'];?></p>
                    <?php else: ?>
                    <p class="admin_text_set01">暂无数据</p>
                    <?php endif;  ?>
                </div>
            </div>
        </div>
        <div data-options="region:'center',border: false"> </div>
    </div>
</div>
<!--east end-->
</div>
<!--easyui-layout end--> 
<script src="<?php print $epath; ?>build/dist/echarts.js"></script> 
<script type="text/javascript">
        var myChart2;
        
var radius = [40, 55];


        // 路径配置
        require.config({
            paths: {
                echarts: '<?php print $epath; ?>/build/dist'
            }
        });
        // 使用
        require(
                [
                    'echarts',
                    'echarts/chart/pie' // 使用柱状图就加载bar模块，按需加载
                ],
                function(ec) {
                    // 基于准备好的dom，初始化echarts图表
                    myChart2 = ec.init(document.getElementById('data-chart-safeindex'));
                    // 过渡---------------------
                    myChart2.showLoading({
                        text: '正在努力的读取数据中...', //loading话术
                    });
                    // ajax callback
                    myChart2.hideLoading();
                    option = {
  
                            toolbox: {
                              show : false,
                              feature : {
                                  dataView : {show: true, readOnly: false},
                                  magicType : {
                                      show: true, 
                                      type: ['pie', 'funnel'],
                                      option: {
                                          funnel: {
                                              width: '20%',
                                              height: '30%',
                                              itemStyle : {
                                                  normal : {
                                                      label : {
                                                          formatter : function (params){
                                                              return 'other\n' + params.value + '%\n'
                                                          },
                                                          textStyle: {
                                                              baseline : 'middle'
                                                          }
                                                      }
                                                  },
                                              } 
                                          }
                                      }
                                  },
                                  restore : {show: true},
                                  saveAsImage : {show: true}
                              }
                          },
                          series : [
                              {
                                  type : 'pie',
                                  center : ['50%', '50%'],
                                  radius : [75, 95],
                                  x: '0%', // for funnel
                                  itemStyle : {
                                        normal : {
                                            label : {
                                                formatter : function (){
                                                    return  '<?php print $dev['saferate']; ?>分'
                                                },
                                                textStyle: {
                                                    fontSize: 26

                                                }
                                            }
                                        },
                                    },
                                  data : [
                                      {name:'other', value:(100-<?php print $dev['saferate']; ?>), 
                                      itemStyle : 
                                          {
                                            normal : {
                                                label : {
                                                    show : true,
                                                    position : 'center',
                                                    textStyle: {
                                                      baseline : 'top',
                                                      fontSize: 26
                                                   }
                                                },
                                                labelLine : {
                                                    show : false
                                                }
                                            },
                                            emphasis: {
                                                color: 'rgba(0,0,0,0)'
                                            }
                                        }
                                        },
                                      {name:'消防评估', value:<?php print $dev['saferate']; ?>,
                                      itemStyle : {
                                        normal : {
                                            label : {
                                                show : true,
                                                position : 'center',
                                                formatter : '{b}',
                                                textStyle: {
                                                    baseline : 'bottom'
                                                }
                                            },
                                            labelLine : {
                                                show : false
                                            }
                                        }
                                    }
                                    }
                                  ]
                              },


                          ]
                      };


                    // 为echarts对象加载数据 
                    myChart2.setOption(option);
                }
        );
</script> 