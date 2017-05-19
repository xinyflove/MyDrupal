<?php 
unset($form['links']);
?>
<div id="login_main">
		<div class="login_con">
			<div class="login_box">
				<div class="login_title">
					<div class="login_title_main">
						<h3>用户登录</h3>
					</div>
				</div>
				<div class="login_middle">
					<p><label for="username">用户名：</label><?php unset($form['name']['#description']); unset($form['name']['#title']); print drupal_render($form['name']); ?></p>
					<p><label for="password">密码：</label><?php unset($form['pass']['#title']); print drupal_render($form['pass']); ?></p>
				</div>
				<div class="login_footer">
					<?php $form['actions']['submit']['#value']="登录"; print drupal_render_children($form) ?>
				</div>
			</div>
		</div>
	</div>

		