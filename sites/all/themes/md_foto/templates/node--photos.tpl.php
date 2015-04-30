<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php
	// TEASER
	if (!$page):
	?>
  		<h2<?php print $title_attributes; ?> class="photo-title">
        <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
      </h2>
      <div class="photo-overlay"></div>
      <div class="photo-image">
            <?php
            hide($content['links']);
            print render($content);
            ?>
      </div>

  <?php 
	// FULL NODE
	else: ?>
    <div class="photos-left">
      <?php print render($content['field_photos']);?>
    </div>
    <div class="photos-right">
      <h1 id="page-title" class="title"><?php print $title; ?></h1>

      <?php if ($display_submitted): ?>
        <div class="meta submitted">
          <?php print $user_picture; ?>
          <?php print $submitted; ?>
        </div>
      <?php endif; ?>

      <?php
        if (($node_share_position == 1) && ($facebook_display || $twitter_display || $gplus_display || $pinterest_display || $stumble_display)):
          require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/node.meta_share.inc';
        endif;
      ?>

      <div class="node-content clearfix"<?php print $content_attributes; ?>>
        <?php
          // We hide the comments and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);
          hide($content['field_image']);
          hide($content['field_photos']);
          print render($content);
        ?>
      </div>

      <?php
        // Remove the "Add new comment" link on the teaser page or if the comment
        // form is being displayed on the same page.
        if ($teaser || !empty($content['comments']['comment_form'])) {
          unset($content['links']['comment']['#links']['comment-add']);
        }
        // Only display the wrapper div if there are links.
        $links = render($content['links']);
        if ($links):
      ?>
        <div class="link-wrapper clearfix">
          <?php print $links; ?>
        </div>
      <?php endif; ?>

      <?php
        if (($node_share_position == 2) && ($facebook_display || $twitter_display || $gplus_display || $pinterest_display || $stumble_display)):
          require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/node.meta_share.inc';
        endif;
      ?>

      <?php print render($content['comments']); ?>
    </div>
	<?php endif; ?>
</div>
