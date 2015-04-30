<?php

/**
 * @file
 * Theme settings .
 */

function md_foto_theme_settings_design(&$form, &$form_state) {
	$form['md_foto_settings']['design'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -4,
		'#prefix'  				=> '<div id="md-design" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #md-design -->',
	);
	
	$form['md_foto_settings']['design']['design_htmllist'] = array(
		'#markup' 				=> '<div class="md-listleft">
				<ul>
				  <li><a href="#ds-skin">Skin</a></li>
					<li><a href="#ds-background">Background</a></li>
					<li><a href="#ds-photos">Photo Overlay</a></li>
				</ul>
			</div><div class="md-listcontent">',
		'#weight' 				=> -15,
	);
	$form['md_foto_settings']['design']['design_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);

  /* 1.	Skin
	--------------------------------------------------------------------------*/
  $form['md_foto_settings']['design']['design_skin'] = array(
    '#type' 					=> 'fieldset',
    '#weight' 				=> -5,
    '#prefix'  				=> '<div id="ds-skin" class="md-tabcontent clearfix">',
    '#suffix'        => '</div><!-- / #ds-skin -->',
  );

  $form['md_foto_settings']['design']['design_skin']['skins'] = array(
    '#type'          => 'select',
    '#title'         => t('Choose skin'),
    '#default_value' => theme_get_setting('skins'),
    '#options'       => array(
      '0'     => t('Dark (default)'),
      'light'     => t('Light'),
    ),
  );

	/* 2.	Background
	--------------------------------------------------------------------------*/
	$form['md_foto_settings']['design']['design_background'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="ds-background" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #ds-background -->',
	);
	
		// Background settings
		$form['md_foto_settings']['design']['design_background']['bg_color'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Background-color'),
      '#default_value' => theme_get_setting('bg_color'),
      '#prefix' => '<div class="form-font-color">',
      '#suffix' => '</div>',
      '#attributes' 		=> array(
        'class' => array(
          'form-colorpicker',
        ),
      ),
	    );
		
		$form['md_foto_settings']['design']['design_background']['choose_bg'] = array(
            '#type'          => 'select',
            '#title'         => t('Choose background'),
            '#description'   => t('Choose background or choose "Custom" to upload your custom background'),
            '#default_value' => theme_get_setting('choose_bg'),
            '#options'       => array(
                                    '0'     => t('Default'),
                                    '2'     => t('Custom Image'),
                                ),
        );
		
		$bg_path = theme_get_setting('bg_path');
		// If $bg_path is a public:// URI, display the path relative to the files directory
		if (file_uri_scheme($bg_path) == 'public') {
			$bg_path = file_uri_target($bg_path);
		}
	   
	  $form['md_foto_settings']['design']['design_background']['bg_path'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Path to custom background'),
	    '#default_value' =>  $bg_path,
			'#prefix' => '<div id="design-bg-custom" class="clearfix">',
	  );
	
	  $form['md_foto_settings']['design']['design_background']['bg_upload'] = array(
	    '#type' => 'file',
	  );
		
		$form['md_foto_settings']['design']['design_background']['bg_repeat'] = array(
	    '#type'          => 'select',
	    '#title'         => t('Background repeat'),
	    '#default_value' => theme_get_setting('bg_repeat'),
	    '#options'       => array(
	                          'inherit'   => t('Inherit'),
	                          'repeat'    => t('Repeat'),
														'repeat-x'  => t('Repeat X'),
														'repeat-y'  => t('Repeat Y'),
														'no-repeat' => t('No repeat'),
	                        ),
	  );
		
		$form['md_foto_settings']['design']['design_background']['bg_position'] = array(
	    '#type'          => 'select',
	    '#title'         => t('Background position'),
	    '#default_value' => theme_get_setting('bg_position'),
	    '#options'       => array(
	                          'left top'   => t('Left Top'),
														'left center'   => t('Left Center'),
	                          'left bottom'    => t('Left Bottom'),
														'center center'  => t('Center Center'),
														'center top'  => t('Center Top'),
														'center bottom'  => t('Center Bottom'),
														'right top'  => t('Right Top'),
														'right center'  => t('Right Center'),
														'right bottom'  => t('Right Bottom'),
	                        ),
	  );
		
		$form['md_foto_settings']['design']['design_background']['bg_attachment'] = array(
	    '#type'          => 'select',
	    '#title'         => t('Background Attachment'),
	    '#default_value' => theme_get_setting('bg_attachment'),
	    '#options'       => array(
	                          'scroll'   => t('Scroll'),
														'fixed'   => t('Fixed'),
	                        ),
			'#suffix' => '</div>',
	  );

  /* 3.	Photo Overlay
  --------------------------------------------------------------------------*/
  $form['md_foto_settings']['design']['design_photos'] = array(
    '#type' 					=> 'fieldset',
    '#weight' 				=> -5,
    '#prefix'  				=> '<div id="ds-photos" class="md-tabcontent clearfix">',
    '#suffix'        => '</div><!-- / #ds-photos -->',
  );

    $form['md_foto_settings']['design']['design_photos']['overlay_color'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Overlay color'),
      '#default_value' => theme_get_setting('overlay_color'),
      '#prefix' => '<div class="form-font-color">',
      '#suffix' => '</div>',
      '#attributes' 		=> array(
        'class' => array(
          'form-colorpicker',
        ),
      ),
    );

    $form['md_foto_settings']['design']['design_photos']['overlay_transparent'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Overlay transparent'),
      '#description'   => t('Number, value from 1 to 100'),
      '#default_value' => theme_get_setting('overlay_transparent'),
    );
}