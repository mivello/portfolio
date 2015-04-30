<?php
/**
 * Add body classes if certain regions have content.
 */
function md_foto_preprocess_html(&$vars) {
  drupal_add_css('http://http://fonts.googleapis.com/css?family=Lato:400,300,700', 'external');
  // Add conditional stylesheets for IE
  drupal_add_css(drupal_get_path('theme', 'md_foto') . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));

	drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/script.js');
	
	// remove no-sidebars class
	if ($index = array_search('no-sidebars', $vars['classes_array'])) {
    unset($vars['classes_array'][$index]);
  }
	
	if (empty($vars['page']['sidebar']) && empty($vars['page']['sidebar_col1']) && empty($vars['page']['sidebar_col2'])  && empty($vars['page']['sidebar_bottom'])) {
    $vars['classes_array'][] = 'no-sidebars';
  }

	// Sidebar position
	switch (theme_get_setting('sidebar_position')) {
		case 1:
			$vars['classes_array'][] = 'sidebar-left';
			break;
	}

	// Custom Background
	$css = "";
  $bg_path = theme_get_setting('bg_path');
  $css = "body {";
  if ($bg_path) {
    if (file_uri_scheme($bg_path) == 'public') {
      $css .= "background-image:url(". file_create_url($bg_path) .");\n";
    } else if ((file_uri_scheme($bg_path) == 'http') || (file_uri_scheme($bg_path) == 'https')) {
      $css .= "background-image:url(". $bg_path .");\n";
    } else {
      $css .= "background-image:url(". file_create_url(file_build_uri($bg_path)) .");\n";
    }
    if (theme_get_setting('bg_repeat')) {$css .= "background-repeat:". theme_get_setting('bg_repeat').";\n";}
    if (theme_get_setting('bg_attachment')) {$css .= "background-attachment:". theme_get_setting('bg_attachment').";\n";}
    if (theme_get_setting('bg_position')) {$css .= "background-position:". theme_get_setting('bg_position') .";\n";}
  }
  if (theme_get_setting('bg_color')) {
    $css .= "background-color:#".theme_get_setting('bg_color').";\n";
    if (!$bg_path) { $css .= "background-image: none;\n"; }
  }

  $css .= "}";

	
	/* Design
	---------------------------------------------------------------------------------------- */
  // Skin
  if (theme_get_setting('skins') != '0') {
    drupal_add_css(drupal_get_path('theme', 'md_foto') . '/css/'.theme_get_setting('skins').'.css', array('group' => CSS_THEME));
  }

	// Overlay
  if (theme_get_setting('overlay_color')) {
    $css .= ".photo-overlay {background-color: #" . theme_get_setting('overlay_color') . ";";
    if (theme_get_setting('overlay_transparent')) {
      $transparent = (float) theme_get_setting('overlay_transparent');
      $css .= 'opacity: ' . $transparent/100 . ';
      -ms-filter:"progid:DXImageTransform.Microsoft.Alpha(Opacity=' . $transparent . ')";
      filter: alpha(opacity=' . $transparent . ');';
    }
    $css .= "}";
  }

   $vars['theme_setting_css'] = $css;

	// Custom Web clip
	$webclip_path = theme_get_setting('webclip_path');
	$wc_href = "";
	if ($webclip_path) {
		if (file_uri_scheme($webclip_path) == 'public') {
			$wc_href = file_create_url($webclip_path);
		} else {
			$wc_href = file_create_url(file_build_uri($webclip_path));
		}
		
		$wc_rel = "apple-touch-icon";
	  if (theme_get_setting('webclip_precomp')) { // no output if $url_precomp = ''
	    $wc_rel = "apple-touch-icon-precomposed";
	  }
		$wc = array(
			'#tag' => 'link',
			'#attributes' => array(
				'href' => $wc_href,
				'rel' => $wc_rel,
				'type' => file_get_mimetype($wc_href),
			),
		);
		drupal_add_html_head($wc, 'webclip');
	}
	
	// Enable Responsive
	if (theme_get_setting('responsive')) {
    drupal_add_css(drupal_get_path('theme', 'md_foto') . '/css/media-queries.css', array('group' => CSS_THEME));
    drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/selectnav.min.js');
		$menuid = 'main-menu-links';
		if (!empty($vars['page']['superfish'])) {
			$menuid = 'superfish-1';
		}
		$selecnav = '(function ($) {
			$(function(){
				selectnav(\''.$menuid.'\', {
					label: \''.t('--- Table of content ---').'\',//first select field
					nested: true,
					indent: \'-\'
			 });		
				});
		})(jQuery);';
		drupal_add_js($selecnav, 'inline');
		$vp = array(
          '#type' => 'html_tag',
          '#tag' => 'meta',
          '#attributes' => array(
            'name' =>  'viewport',
            'content' =>  'width=100%, initial-scale=1, maximum-scale=1, minimum-scale=1, user-scalable=no'
          )
        );
        drupal_add_html_head($vp, 'viewport');
	}
	
	/* Enable custom font
	---------------------------------------------------------------------------------------- */
	// Google web fonts
	if (theme_get_setting('googlewebfonts')) {
		$googlewebfonts = theme_get_setting('googlewebfonts');
		drupal_add_css($googlewebfonts, 'external');
	}
	
	/* Text/typography
	---------------------------------------------------------------------------------------- */
	$vars['typography'] = '';
	// common text
	if (theme_get_setting('text_font') || theme_get_setting('ts_font_color')) {
		$vars['typography']   = "body {";
		if (theme_get_setting('text_font')) {
		  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('text_font'));
		}
		
		if (theme_get_setting('ts_font_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('ts_font_color').';';
		}
		$vars['typography']   .= "}\n";
	}
    /////
    $text_font_arr = explode("|", theme_get_setting('text_font'));
    if ($text_font_arr[0] != '0') {
        //$vars['typography']   .= '#forum, ul.quicktabs-tabs, #nav ul.sf-menu li li,.ui-widget {font-family: '.$text_font_arr[4].';}';
    }
    /////
	// Text selection
	if (theme_get_setting('tss_bgcolor') || theme_get_setting('tss_tcolor')) {
        $tss_bgcolor = '';
        $tss_tcolor = '';
		if (theme_get_setting('tss_bgcolor')) {
		  $tss_bgcolor   = 'background: #'.theme_get_setting('tss_bgcolor').';';
		}
		if (theme_get_setting('tss_tcolor')) {
		  $tss_tcolor   = 'color: #'.theme_get_setting('tss_tcolor').';';
		}
		$vars['typography']   .= "::-moz-selection {".$tss_bgcolor.$tss_tcolor."text-shadow: none;}\n";
		$vars['typography']   .= "::selection {".$tss_bgcolor.$tss_tcolor."text-shadow: none;}\n";
	}
	// link regular
	if (theme_get_setting('l_regular_color') || theme_get_setting('l_regular_st') || theme_get_setting('l_regular__hl') || theme_get_setting('l_regular_ts')) {
		$vars['typography']   .= "a:link, .node-content a {";
		if (theme_get_setting('l_regular_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('l_regular_color').';';
		}
		if (theme_get_setting('l_regular__hl')) {
		  $vars['typography']   .= 'background-color: #'.theme_get_setting('l_regular__hlc').';';
		}
		$l_text_style = theme_get_setting('l_regular_ts'); 
		if ($l_text_style['bold']) {
		  $vars['typography']   .= 'font-weight: '.$l_text_style['bold'].';';
		}
		if ($l_text_style['italic']) {
		  $vars['typography']   .= 'font-style: '.$l_text_style['italic'].';';
		}
		if ($l_text_style['underline']) {
		  $vars['typography']   .= 'text-decoration: '.$l_text_style['underline'].';';
		}
		$vars['typography']   .= "}\n";
	}
	// link rollover
	if (theme_get_setting('l_rollover_color') || theme_get_setting('l_rollover_st') || theme_get_setting('l_rollover__hl') || theme_get_setting('l_rollover_ts')) {
		$vars['typography']   .= "a:hover, .node-content a:hover {";
		if (theme_get_setting('l_rollover_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('l_rollover_color').';';
		}
		if (theme_get_setting('l_rollover__hl')) {
		  $vars['typography']   .= 'background-color: #'.theme_get_setting('l_rollover__hlc').';';
		}
		$l_text_style = theme_get_setting('l_rollover_ts'); 
		if ($l_text_style['bold']) {
		  $vars['typography']   .= 'font-weight: '.$l_text_style['bold'].';';
		}
		if ($l_text_style['italic']) {
		  $vars['typography']   .= 'font-style: '.$l_text_style['italic'].';';
		}
		if ($l_text_style['underline']) {
		  $vars['typography']   .= 'text-decoration: '.$l_text_style['underline'].';';
		}
		$vars['typography']   .= "}\n";
	}
	
	// link visited
	if (theme_get_setting('l_visited_color') || theme_get_setting('l_visited_st') || theme_get_setting('l_visited__hl') || theme_get_setting('l_visited_ts')) {
		$vars['typography']   .= "a:visited, .node-content a:visited {";
		if (theme_get_setting('l_visited_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('l_visited_color').';';
		}
		if (theme_get_setting('l_visited__hl')) {
		  $vars['typography']   .= 'background-color: #'.theme_get_setting('l_visited__hlc').';';
		}
		$l_text_style = theme_get_setting('l_visited_ts'); 
		if ($l_text_style['bold']) {
		  $vars['typography']   .= 'font-weight: '.$l_text_style['bold'].';';
		}
		if ($l_text_style['italic']) {
		  $vars['typography']   .= 'font-style: '.$l_text_style['italic'].';';
		}
		if ($l_text_style['underline']) {
		  $vars['typography']   .= 'text-decoration: '.$l_text_style['underline'].';';
		}
		$vars['typography']   .= "}\n";
	}
	
	// link on
	if (theme_get_setting('l_on_color') || theme_get_setting('l_on_st') || theme_get_setting('l_on__hl') || theme_get_setting('l_on_ts')) {
		$vars['typography']   .= "a:focus, a:active, .node-content a:focus, .node-content a:active {";
		if (theme_get_setting('l_on_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('l_on_color').';';
		}
		if (theme_get_setting('l_on__hl')) {
		  $vars['typography']   .= 'background-color: #'.theme_get_setting('l_on__hlc').';';
		}
		$l_text_style = theme_get_setting('l_on_ts'); 
		if ($l_text_style['bold']) {
		  $vars['typography']   .= 'font-weight: '.$l_text_style['bold'].';';
		}
		if ($l_text_style['italic']) {
		  $vars['typography']   .= 'font-style: '.$l_text_style['italic'].';';
		}
		if ($l_text_style['underline']) {
		  $vars['typography']   .= 'text-decoration: '.$l_text_style['underline'].';';
		}
		$vars['typography']   .= "}\n";
	}
	
	
	// navigation
	if (theme_get_setting('typo_nav_style') || theme_get_setting('nav_color')) {
		$vars['typography']   .= "#nav {";
		if (theme_get_setting('text_font')) {
		  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('typo_nav_style'));
		}
		
		if (theme_get_setting('nav_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('nav_color').';';
		}
		$vars['typography']   .= "}\n";
		
		if (theme_get_setting('nav_color')) {
		  $vars['typography']   .= 'ul#main-menu-links li a, #nav ul.sf-menu li a {color: #'.theme_get_setting('nav_color').';}';
		}
		if (theme_get_setting('nav_hover_color')) {
		  $vars['typography']   .= '#nav ul.sf-menu li > a:hover,#nav ul.sf-menu li.sfHover > a, ul#main-menu-links li:hover a {color: #'.theme_get_setting('nav_hover_color').';}'."\n";
		}
		if (theme_get_setting('nav_active_color')) {
		  $vars['typography']   .= '#nav ul.sf-menu li > a:hover, #nav ul.sf-menu li.sfHover > a, #nav ul.sf-menu li a.active,ul#main-menu-links li.active a {color: #'.theme_get_setting('nav_active_color').';}'."\n";
		}
	}
	
	
	// Page title
	if (theme_get_setting('typo_pagetitle_style') || theme_get_setting('pagetitle_color')) {
		$vars['typography']   .= "h1#page-title {";
		if (theme_get_setting('typo_pagetitle_style')) {
		  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('typo_pagetitle_style'));
		}
		
		if (theme_get_setting('pagetitle_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('pagetitle_color').';';
		}
		$vars['typography']   .= "}\n";
	}
	
	// Node title
	if (theme_get_setting('typo_nodetitle_style') || theme_get_setting('nodetitle_color')) {
		$vars['typography']   .= "#content .node h2 {";
		if (theme_get_setting('typo_nodetitle_style')) {
		  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('typo_nodetitle_style'));
		}
		
		if (theme_get_setting('nodetitle_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('nodetitle_color').';';
		}
		$vars['typography']   .= "}\n";
		
		if (theme_get_setting('nodetitle_color')) {
		  $vars['typography']   .= '.node h2 a {color: #'.theme_get_setting('nodetitle_color').';}'."\n";
		}
		
		if (theme_get_setting('nodetitle_hover_color')) {
		  $vars['typography']   .= '.node h2 a:hover {color: #'.theme_get_setting('nodetitle_hover_color').';}'."\n";
		}
	}
	
	if (theme_get_setting('nodetitle_enable') == 1) {
		foreach (node_type_get_types() as $type => $name) {
			if (theme_get_setting('typo_n'.$type.'title_style') || theme_get_setting('n'.$type.'title_color')) {
				$vars['typography']   .= "#content .node-$type h2 {";
				if (theme_get_setting('typo_n'.$type.'title_style')) {
				  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('typo_n'.$type.'title_style'));
				}
				
				if (theme_get_setting('n'.$type.'title_color')) {
				  $vars['typography']   .= 'color: #'.theme_get_setting('n'.$type.'title_color').';';
				}
				$vars['typography']   .= "}\n";
				
				if (theme_get_setting('n'.$type.'title_color')) {
				  $vars['typography']   .= '.article-type-'.$type.' h2 a {color: #'.theme_get_setting('n'.$type.'title_color').';}'."\n";
				}
				
				if (theme_get_setting('n'.$type.'title_hover_color')) {
				  $vars['typography']   .= '.article-type-'.$type.' h2 a:hover {color: #'.theme_get_setting('n'.$type.'title_hover_color').';}'."\n";
				}
			}
		}
	}
	
	// Block title
	if (theme_get_setting('typo_blocktitle_style') || theme_get_setting('blocktitle_color')) {
		$vars['typography']   .= ".block h3.block-title {";
		if (theme_get_setting('typo_blocktitle_style')) {
		  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('typo_blocktitle_style'));
		}
		
		if (theme_get_setting('blocktitle_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('blocktitle_color').';';
		}
		$vars['typography']   .= "}\n";
	}
	
	// Bottom block title
	if (theme_get_setting('typo_bblocktitle_style') || theme_get_setting('bblocktitle_color')) {
		$vars['typography']   .= "#bottom .block h3.block-title {";
		if (theme_get_setting('typo_bblocktitle_style')) {
		  $vars['typography']   .= md_foto_font_to_css(theme_get_setting('typo_bblocktitle_style'));
		}
		
		if (theme_get_setting('bblocktitle_color')) {
		  $vars['typography']   .= 'color: #'.theme_get_setting('bblocktitle_color').';';
		}
		$vars['typography']   .= "}\n";
	}
	
	/* Get theme settings
	---------------------------------------------------------------------------------------- */
	
	$vars['header_code']   = theme_get_setting('header_code');
	$vars['footer_code']   = theme_get_setting('footer_code');
	if (theme_get_setting('custom_css')) {
		$vars['custom_css']  = theme_get_setting('custom_css');
	}
	
	drupal_add_css(path_to_theme() . '/css/ie7.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
}

function md_foto_font_to_css($font) {
	$font_arr = explode("|", $font);
	$css = "";
		if ($font_arr[0] != '0') {
		$css = 'font-family: '.$font_arr[4].';';
		if ($font_arr[2]) {
			$css .= 'font-size: '.$font_arr[2].$font_arr[3].';';
		}
		$css .= md_foto_expand_font_weight($font_arr[1]);
	}
	return $css;
}

function md_foto_expand_font_weight($fw) {
				switch($fw) {
					case 'n1':
						$fontExpand = "font-style: normal; font-weight: 100;";
				  	break;
					case 'i1':
						$fontExpand = "font-style: italic; font-weight: 100;";
						break;
					case 'n2':
						$fontExpand = "font-style: normal; font-weight: 200;";
				  	break;
					case 'i2':
						$fontExpand = "font-style: italic; font-weight: 200;";
						break;
					case 'n3':
						$fontExpand = "font-style: normal; font-weight: 300;";
				  	break;
					case 'i3':
						$fontExpand = "font-style: italic; font-weight: 300;";
						break;
					case 'n4':
						$fontExpand = "font-style: normal; font-weight: normal;";
				  	break;
					case 'i4':
						$fontExpand = "font-style: italic; font-weight: normal";
						break;
					case 'n5':
						$fontExpand = "font-style: normal; font-weight: 500;";
				  	break;
					case 'i5':
						$fontExpand = "font-style: italic; font-weight: 500;";
						break;
					case 'n6':
						$fontExpand = "font-style: normal; font-weight: 600;";
				  	break;
					case 'i6':
						$fontExpand = "font-style: italic; font-weight: 600;";
						break;
					case 'n7':
						$fontExpand = "font-style: normal; font-weight: bold;";
				  	break;
					case 'i7':
						$fontExpand = "font-style: italic; font-weight: bold;";
						break;
					case 'n8':
						$fontExpand = "font-style: normal; font-weight: 800;";
				  	break;
					case 'i8':
						$fontExpand = "font-style: italic; font-weight: 800;";
						break;
					case 'n9':
						$fontExpand = "font-style: normal; font-weight: 800;";
				  	break;
					case 'i9':
						$fontExpand = "font-style: italic; font-weight: 800;";
						break;
					default:
						$fontExpand = "";
				}
				
				return $fontExpand;
			}

/**
 * Override or insert vars into the page template for HTML output.
 */
function md_foto_process_html(&$vars) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
	
	$classes = explode(' ', $vars['classes']);
  if ($node = menu_get_object()) {
    $node_type_class = drupal_html_class('node-type-' . $node->type);
    if (in_array($node_type_class, $classes)) {
      theme_get_setting('extra_page_classes') == 0 ? '' : $classes = str_replace($node_type_class, '', $classes);
      $classes = str_replace('node-type-', 'page-type-', $classes);
    }
  }
  $vars['classes'] = trim(implode(' ', $classes));
}



/**
 * Override or insert vars into the page template.
 */
function md_foto_process_page(&$vars) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $vars['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $vars['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($vars['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $vars['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($vars['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $vars['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
  // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($vars['title_suffix']['add_or_remove_shortcut']) && $vars['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $vars['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $vars['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $vars['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }

  $vars['show_title'] = TRUE;
  if (!empty($vars['node']) && $vars['node']->type == 'photos') {
    $vars['show_title'] = FALSE;
  }
	
	$vars['themepath'] = base_path().drupal_get_path('theme', 'md_foto');
}

/**
 * Implements hook_preprocess_page().
 */
function md_foto_preprocess_page(&$vars) {

}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function md_foto_preprocess_maintenance_page(&$vars) {
  if (!$vars['db_is_active']) {
    unset($vars['site_name']);
  }
  drupal_add_css(drupal_get_path('theme', 'md_foto') . '/css/maintenance-page.css');
}

/**
 * Override or insert vars into the maintenance page template.
 */
function md_foto_process_maintenance_page(&$vars) {
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $vars['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $vars['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($vars['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $vars['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($vars['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $vars['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
}

/**
 * Override or insert vars into the node template.
 */
function md_foto_preprocess_node(&$vars) {
	if (theme_get_setting('extra_article_classes')) {
    if (module_exists('translation')) {
      if ($vars['node']->language) {
        global $language;
        $vars['classes_array'][] = 'article-lang-'. $vars['node']->language;
      }
    }
  }

  $vars['classes_array'][] = $vars['zebra'];

  $vars['submitted'] = t('Published by !username on !datetime', array('!username' => $vars['name'], '!datetime' => $vars['date']));
	
  if ($vars['view_mode'] == 'full' && node_is_page($vars['node'])) {
    $vars['classes_array'][] = 'node-full';
  }
	
	if ($vars['view_mode'] == 'teaser') {
    $vars['classes_array'][] = "node-".$vars['node']->type."-teaser";
  }
	

	$vars['nodeurl'] = url("node/".$vars['node']->nid, array('absolute' => TRUE));
	
	$node_content_type = (theme_get_setting('node_enable') == 1) ? $vars['node']->type : 'default';
	
	$vars['node_share_position'] = theme_get_setting('node_share_position_'. $node_content_type);
	
  $vars['facebook_display'] = theme_get_setting('node_share_facebook_'. $node_content_type);
	if (theme_get_setting('node_share_facebook_'. $node_content_type)){
		$vars['facebook_layout'] = theme_get_setting('node_share_facebook_layout_'. $node_content_type);
		$vars['facebook_display_font'] = theme_get_setting('node_share_facebook_font_'. $node_content_type);
		$vars['facebook_display_color'] = theme_get_setting('node_share_facebook_color_'. $node_content_type);
	}
	
	$vars['twitter_display'] = theme_get_setting('node_share_twitter_'. $node_content_type);
	if (theme_get_setting('node_share_twitter_'. $node_content_type)){
		$vars['twitter_display_style'] = theme_get_setting('node_share_twitter_style_'. $node_content_type);
		$vars['twitter_display_lang'] = theme_get_setting('node_share_twitter_lang_'. $node_content_type);
	}
	
	$vars['gplus_display'] = theme_get_setting('node_share_gplus_'. $node_content_type);
	if (theme_get_setting('node_share_gplus_'. $node_content_type)){
		drupal_add_js('https://apis.google.com/js/plusone.js', 'external');
		$vars['gplus_display_size'] = theme_get_setting('node_share_gplus_size_'. $node_content_type);
		$vars['gplus_annotation'] = theme_get_setting('node_share_gplus_annotation_'. $node_content_type);
	}
	
	$vars['pinterest_display'] = theme_get_setting('node_share_pinterest_'. $node_content_type);
	if (theme_get_setting('node_share_pinterest_'. $node_content_type)){
		drupal_add_js('http://assets.pinterest.com/js/pinit.js', 'external');
		$vars['pinterest_layout'] = theme_get_setting('node_share_pinterest_layout_'. $node_content_type);
		$vars['pinterest_media'] = '';
		if (theme_get_setting('node_share_pinterest_image_'. $node_content_type)) {
			$pinterest_image_field = 'field_'.theme_get_setting('node_share_pinterest_image_'. $node_content_type);
			$pinterest_image = $vars['node']->$pinterest_image_field;
			if (isset($pinterest_image) && !empty($pinterest_image['und'][0]['filename'])) {
				$vars['pinterest_media'] = file_create_url(file_build_uri($pinterest_image['und'][0]['filename']));
			}
		}
	}
	
	$vars['stumble_display'] = theme_get_setting('node_share_stumble_'. $node_content_type);
	if (theme_get_setting('node_share_stumble_'. $node_content_type)){
		$vars['stumble_display_style'] = theme_get_setting('node_share_stumble_style_'. $node_content_type);
	}
	
}

// template_preprocess_comment
function md_foto_preprocess_comment(&$vars) {
  if (theme_get_setting('extra_comment_classes')) {
    $vars['classes_array'][] = $vars['zebra'];
  }
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';
  $uri = entity_uri('comment', $vars['comment']);
  $uri['options'] += array('attributes' => array('rel' => 'bookmark'));
  $vars['title'] = l($vars['comment']->subject, $uri['path'], $uri['options']);
  $vars['permalink'] = l(t('Permalink'), $uri['path'], $uri['options']);
  $vars['created'] = '<span class="date-time permalink">' . l($vars['created'], $uri['path'], $uri['options']) . '</span>';
  $vars['datetime'] = format_date($vars['comment']->created, 'custom', 'c');
  $vars['unpublished'] = '';
  if ($vars['status'] == 'comment-unpublished') {
    $vars['unpublished'] = '<div class="unpublished">' . t('Unpublished') . '</div>';
  }
}
// template_process_comment
function md_foto_process_comment(&$vars) {
  $classes = explode(' ', $vars['classes']);
  if (in_array('comment-by-anonymous', $classes)) {
    theme_get_setting('extra_comment_classes') ? '' : $classes = str_replace('comment-by-anonymous', '', $classes);
  }
  if (in_array('comment-by-node-author', $classes)) {
    $classes = str_replace('comment-by-node-author', 'comment-by-article-author', $classes);
    theme_get_setting('extra_comment_classes') ? '' : $classes = str_replace('comment-by-article-author', '', $classes);
  }
  if (in_array('comment-by-viewer', $classes)) {
    theme_get_setting('extra_comment_classes') ? '' : $classes = str_replace('comment-by-viewer', '', $classes);
  }
  if (in_array('comment-new', $classes)) {
    theme_get_setting('extra_comment_classes') ? '' : $classes = str_replace('comment-new', '', $classes);
  }
  $vars['classes'] = trim(implode(' ', $classes));
}

/**
 * Override or insert vars into the block template.
 */
function md_foto_preprocess_block(&$vars) {
	if (theme_get_setting('extra_block_classes')) {
    $vars['classes_array'][] = 'block-' . $vars['block_zebra'];
  }
  if (theme_get_setting('extra_block_classes')) {
    $vars['classes_array'][] = 'block-count-'. $vars['id'];
  }
  if (theme_get_setting('extra_block_classes')) {
    $vars['classes_array'][] = drupal_html_class('block-region-' . $vars['block']->region);
  }
  // In the header region visually hide block titles.
  if ($vars['block']->region == 'header') {
    $vars['title_attributes_array']['class'][] = 'element-invisible';
  }
	$vars['header'] = NULL;
}



// Modify search results based on theme settings.
function md_foto_preprocess_search_result(&$vars) {
  $result = $vars['result'];
  $vars['url'] = check_url($result['link']);
  $vars['title'] = check_plain($result['title']);
  $vars['snippet'] = '';
  if (!empty($result['snippet']) && theme_get_setting('search_snippet')) {
    $vars['snippet'] = $result['snippet'];
  }
  $info = array();
  if (!empty($result['type']) && theme_get_setting('search_info_type')) {
    $info['type'] = check_plain($result['type']);
  }
  if (!empty($result['user']) && theme_get_setting('search_info_user')) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date']) && theme_get_setting('search_info_date')) {
    $info['date'] = format_date($result['date'], 'small');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    if (!empty($result['extra'][0]) && theme_get_setting('search_info_comment')) {
      $info['comment'] = $result['extra'][0];
    }
    if (!empty($result['extra'][1]) && theme_get_setting('search_info_upload')) {
      $info['upload'] = $result['extra'][1];
    }
  }
  $vars['info_split'] = $info;
  $vars['info'] = implode(' - ', $info);
  $vars['info_separator'] = filter_xss(theme_get_setting('search_info_separator'));
}