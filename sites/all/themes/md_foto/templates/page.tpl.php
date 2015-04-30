<div class="pagewrap">
  <div id="header" class="clearfix">
    <?php if ($logo): ?>
      <div id="logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
        <?php if ($site_slogan): ?>
          <span class="slogan<?php if ($hide_site_slogan) { print ' element-invisible'; } ?>">
            <?php print $site_slogan; ?>
          </span>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if ($site_name): ?>
      <div id="name-and-slogan"<?php if ($hide_site_name && $hide_site_slogan) { print ' class="element-invisible"'; } ?>>

        <?php if ($site_name): ?>
          <?php if ($title): ?>
            <div id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
              <strong>
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </strong>
            </div>
          <?php else: /* Use h1 when the content title is empty */ ?>
            <h1 id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <div id="site-slogan"<?php if ($hide_site_slogan) { print ' class="element-invisible"'; } ?>>
            <?php print $site_slogan; ?>
          </div>
        <?php endif; ?>

      </div> <!-- /#name-and-slogan -->
    <?php endif; ?>


    <?php if ($main_menu): ?>
      <div id="nav">
          <?php
            print theme('links__system_main_menu', array(
              'links' => $main_menu,
              'attributes' => array(
                'id' => 'main-menu-links',
                'class' => array('links', 'clearfix'),
              ),
              'heading' => array(
                'text' => t('Main menu'),
                'level' => 'h2',
                'class' => array('element-invisible'),
              ),
            )); ?>
      </div><!-- /#nav -->
    <?php endif; ?>
  </div><!-- /#header -->

  <div id="main-content"><div class="wrap clearfix">
  	<?php if ($messages): ?>
      <div id="messages">
        <?php print $messages; ?>
      </div> <!-- /#messages -->
    <?php endif; ?>
    
    <?php if ($page['content_top']): ?><div id="content-top"><?php print render($page['content_top']); ?></div><?php endif; ?>
	
    <div id="content"><div class="content-inner">
	    
	    <?php if ($breadcrumb): ?>
        <div id="breadcrumb"><?php print $breadcrumb; ?></div>
      <?php endif; ?>
      <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
      <?php print render($title_prefix); ?>
      <?php if ($show_title && $title): ?>
        <h1 class="title" id="page-title">
          <?php print $title; ?>
        </h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php if ($tabs): ?>
        <div class="tabs">
          <?php print render($tabs); ?>
        </div>
      <?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php if ($page['content_bottom']): ?><div id="content-bottom"><?php print render($page['content_bottom']); ?></div><?php endif; ?>
    </div></div><!-- /#content -->
    <?php if ($page['sidebar']): ?>
      <div id="sidebar" class="column sidebar">
        <?php if ($page['sidebar']): print render($page['sidebar']); endif; ?>
      </div> <!-- /#sidebar -->
    <?php endif; ?>
  </div>

  <div id="footer"><div class="wrap clearfix">
    <?php if ($page['footer']): ?>
      <div class="ft-block">
        <?php print render($page['footer']); ?>
      </div>
    <?php endif; ?>
    <div class="credits">Powered by <a href="http://drupal.org" target="_blank">Drupal</a>. Theme by <a href="http://megadrupal.com" target="_blank">MegaDrupal</a></div>
  </div> <!-- /#footer -->
  </div> <!-- /.pagewrap -->