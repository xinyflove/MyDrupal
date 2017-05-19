<div class="clearfix" style="padding: 25px 0 10px;">
	<!-- <div style="margin-left:5%; float:left;">

        <span style="margin-right:5px;">查询指标</span>

        <select id="queryIndexCC" class="easyui-combobox" name="queryIndex" style="width:260px;" data-options="

            valueField : 'value',

            textField: 'label',

            onSelect:function(rec){

                

            }">

            <option value="1">周期内水系统排名</option>

            <option value="2">周期内二维码巡检排名</option>

            <option value="3">周期内视频告警排名</option>


          </select>

    </div> -->

    <!-- <div style="margin-left:4%; float:left; vertical-align:middle">

        <span style="margin-right:5px">起止时间</span>

        <input class="easyui-datebox" id="querystarttime" name="querystart" data-options="required:true" value="3/4/2015" style="width:150px">

        <span>--------</span>

        <input class="easyui-datebox" id="queryendtime" name="queryend" data-options="required:true" value="3/4/2015" style="width:150px">

    </div> -->
</div>

<div style="padding:5px 40px;text-align:right;">
	<a href="javascript:void(0);" class="easyui-linkbutton" data-options="width:80" onclick="goAreaPage('<?php print $dis_uri ?>');">返回</a>
	<!-- <a id="queryBtn" href="javascript:void(0);" class="easyui-linkbutton" data-options="width:80" onclick="doDrawDataChart()">查询</a>
    <a id="resetBtn" href="javascript:void(0);" class="easyui-linkbutton" data-options="width:80" onclick="resetForm('daQueryForm')">重置</a> -->
</div>
	
<div style="padding:5px 10px;">
	<div id="water" style="display:none">
		<h3>水系统</h3>
		<table class="corpTable01">
			<tbody>
				<tr>
					<th>企业名称：</th>
					<td><?php print $corp_name  ?></td>
					<th>参考值：</th>
					<td><?php print $waterinfo['threshold']  ?></td>
				</tr>
				<tr>
					<th>设备总数：</th>
					<td colspan="3"><?php print $dev_total  ?></td>
				</tr>
				<tr>
					<th colspan="4">
						<p class="pb5">喷淋A1水压：</p>
						<table class="corpTable01">
							<tbody>
								<tr>
									<th>位置：</th>
									<td><?php print $waterinfo['waterpress'][1][0]['location'];  ?></td>
								</tr>
								<tr>
									<th>压力：</th>
									<td><?php print round($waterinfo['waterpress'][1][0]['value'], 2).$waterinfo['waterpress'][1][0]['unit'];   ?></td>
								</tr>
								<tr>
									<th>报警时间：</th>
									<td><?php print $waterinfo['alarmtime'][$waterinfo['waterpress'][1][0]['device_id']];  ?></td>
								</tr>
							</tbody>
						</table>
					</th>
				</tr>
				<tr>
					<th colspan="4">
						<p class="pb5">消火栓A1水压：</p>
						<table class="corpTable01">
							<tbody>
								<tr>
									<th>位置：</th>
									<td><?php print $waterinfo['waterpress'][2][0]['location'];  ?></td>
								</tr>
								<tr>
									<th>压力：</th>
									<td><?php print round($waterinfo['waterpress'][2][0]['value'], 2).$waterinfo['waterpress'][2][0]['unit'];   ?></td>
								</tr>
								<tr>
									<th>报警时间：</th>
									<td><?php print $waterinfo['alarmtime'][$waterinfo['waterpress'][2][0]['device_id']];  ?></td>
								</tr>
							</tbody>
						</table>
					</th>
				<tr>
				<tr>
					<th colspan="4">
						<p class="pb5">水箱：</p>
						<table class="corpTable01">
							<tbody>
								<tr>
									<th>位置：</th>
									<td><?php print $waterinfo['waterpress'][3][0]['location'];  ?></td>
								</tr>
								<tr>
									<th>压力：</th>
									<td><?php print round($waterinfo['waterpress'][3][0]['value'], 2).$waterinfo['waterpress'][3][0]['unit'];   ?></td>
								</tr>
								<tr>
									<th>报警时间：</th>
									<td><?php print $waterinfo['alarmtime'][$waterinfo['waterpress'][3][0]['device_id']];  ?></td>
								</tr>
							</tbody>
						</table>
					</th>
				<tr>
				<tr>
					<th colspan="4">
						<p class="pb5">水池：</p>
						<table class="corpTable01">
							<tbody>
								<tr>
									<th>位置：</th>
									<td><?php print $waterinfo['waterpress'][4][0]['location'];  ?></td>
								</tr>
								<tr>
									<th>压力：</th>
									<td><?php print round($waterinfo['waterpress'][4][0]['value'], 2).$waterinfo['waterpress'][4][0]['unit'];   ?></td>
								</tr>
								<tr>
									<th>报警时间：</th>
									<td><?php print $waterinfo['alarmtime'][$waterinfo['waterpress'][4][0]['device_id']];  ?></td>
								</tr>
							</tbody>
						</table>
					</th>
				<tr>
			</tbody>
		</table>
		
	</div>
	<div id="ewm" style="display:none">
		<h3>二维码巡检</h3><br /><br />
		<table class="corpTable01">
			<tbody>
				<tr>
					<th>企业名称：</th>
					<td><?php print $corp_name  ?></td>
					<th>设备数：</th>
					<td><?php print $dev_total  ?></td>
				</tr>
				<tr>
					<th>本月巡检数：</th>
					<td><?php print $currmonnum  ?></td>
					<th>合格率：</th>
					<td><?php print $percent  ?></td>
				</tr>
			</tbody>
		</table>
		<!-- 企业名称：<?php print $corp_name  ?><br /><br />
		设备数：<?php print $dev_total  ?><br /><br />
		本月巡检数：<?php print $currmonnum  ?><br /><br />
		合格率：<?php print $percent  ?><br /><br /> -->
		<table class="easyui-datagrid" id="ewm_tab" data-options="fitColumns: true, height: 200">   
		    <thead>   
		        <tr>   
		            <th data-options="field:'dev'">巡检设备</th>   
		            <th data-options="field:'instime'">巡检时间</th>   
		            <th data-options="field:'isok'">是否合格</th>   
		        </tr>   
		    </thead> 
		</table>  
	</div>
	<div id="alarm" style="display:none">
		<h3>报警</h3>
		<table class="corpTable01">
			<tbody>
				<tr>
					<th>企业名称：</th>
					<td><?php print $corp_name  ?></td>
					<th>报警次数：</th>
					<td><?php print $alarmnum  ?></td>
				</tr>
			</tbody>
		</table>
		<!-- 企业名称：<?php print $corp_name  ?><br /><br />
		报警次数：<?php print $alarmnum  ?><br /><br /> -->
		<table class="easyui-datagrid" id="alarm_tab" data-options="fitColumns: true, height: 200">   
		    <thead>   
		        <tr>   
		            <th data-options="field:'position'">位置</th>   
		            <th data-options="field:'alarmtime'">报警时间</th>   
		            <th data-options="field:'alarmcause'">报警原因</th>   
		        </tr>   
		    </thead> 
		</table>  
	</div>
</div>

		

<script>
$(function(){
	var pagetype = <?php print $pagetype; ?>;
	if(pagetype == 1) $("#water").show();
	if(pagetype == 2)
	{
		$("#ewm_tab").datagrid({
			data:[<?php print $inspection; ?>]
		});
		$("#ewm").show();
	}
	if(pagetype == 3)
	{
		$("#alarm_tab").datagrid({
			data:[<?php print $alarminfo; ?>]
		});
		$("#alarm").show();
	}
});

	function goAreaPage(uri)
	{
		$('#mainContent').panel('refresh','/kpi/rank/'+uri);
	}
</script>