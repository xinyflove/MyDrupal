<?php 
unset($form['links']);
print_r($form['name']); exit;
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
					<p><span><em>√</em></span><label class="auto">自动登录</label></p>
				</div>
				<div class="login_footer">
					<?php $form['actions']['submit']['#value']=""; print drupal_render_children($form) ?>
					<input type="reset" value="" class="cancel_btn">
				</div>
			</div>
		</div>
	</div>

	<h1><img src="<?php echo path_to_theme(); ?>/images/login/txt_01.gif" width="134" height="48" alt="机器云"></h1>
		<p class="info">请输入您的账号。</p>
		<p class="red_info">您输入的帐号或密码不正确，请重新输入。</p>
		<div class="user_name">
			<label><span class="icon"><img src="<?php echo path_to_theme(); ?>/images/login/icon_01.gif" width="32" height="32" alt=""></span>
			<?php unset($form['name']['#description']); unset($form['name']['#title']); print drupal_render($form['name']); ?>
			<span class="reset"><img src="<?php echo path_to_theme(); ?>/images/login/icon_03.png" width="18" height="18" alt="reset"></span>
		</div>
		<div class="pass_word">
			<label><span class="icon"><img src="<?php echo path_to_theme(); ?>/images/login/icon_02.gif" width="32" height="32" alt=""></span>
			<?php unset($form['pass']['#title']); print drupal_render($form['pass']); ?>
		</div>
		<div class="login_safe">
			<div class="auto_login"><label><input type="checkbox">自动登录</label></div>
			<div class="forget_pw"><a href="#">忘记密码</a></div>
		</div>
		<div class="submitBox"><?php $form['actions']['submit']['#value']=""; print drupal_render_children($form) ?></div>
