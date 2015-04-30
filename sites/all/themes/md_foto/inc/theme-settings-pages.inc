<?php

/**
 * @file
 * Theme settings .
 */

function md_foto_theme_settings_pages(&$form, &$form_state) {
	$form['md_foto_settings']['pages'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -2,
		'#prefix'  				=> '<div id="md-pages" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #md-pages -->',
	);
	
	$form['md_foto_settings']['pages']['pages_htmllist'] = array(
		'#markup' 				=> '<div class="md-listleft">
				<ul>
					<li><a href="#p-layout">Layout settings</a></li>
				</ul>
			</div><div class="md-listcontent">',
		'#weight' 				=> -15,
	);
	$form['md_foto_settings']['pages']['pages_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);
	
	/* 1.	Layout settings
	--------------------------------------------------------------------------*/
	$form['md_foto_settings']['pages']['page_layout'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="p-layout" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #p-blog -->',
	);

  	
  	$form['md_foto_settings']['pages']['page_layout']['sidebar_position'] = array(
      '#type'          => 'select',
      '#title'         => t('Sidebar position'),
      '#default_value' => theme_get_setting('sidebar_position'),
      '#options'       => array(
                            '1'   => t('Left'),
                            '2' 	=> t('Right'),
                          ),
  	);
}