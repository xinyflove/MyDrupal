<section id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h4<?php print $title_attributes; ?>><?php print $title; ?></h4>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php print $content ?>
  
</section> <!-- /.block -->
