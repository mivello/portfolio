<?php

/**
 * @file
 * Theme settings general.
 */

function md_foto_theme_settings_generalsettings(&$form, &$form_state) {
	
	$form['favicon']['#collapsible'] = FALSE;
	
	$form['md_foto_settings']['general'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="md-general-settings" class="md-tabcontent clearfix">',
		'#suffix'        	=> '</div><!-- / #md-general-settings -->',
	);
	
	$form['md_foto_settings']['general']['general_htmllist'] = array(
		'#markup' 				=> '<div class="md-listleft">
				<ul>
					<li><a href="#general-settings">Settings</a></li>
					<li><a href="#favicon-webclip">Logo, Favicon &amp; Webclip</a></li>
					<li><a href="#custom-font">Custom Font</a></li>
				</ul>
			</div><div class="md-listcontent">',
		'#weight' 				=> -15,
	);
	$form['md_foto_settings']['general']['general_htmllistclose'] = array(
		'#markup' 				=> '</div><!-- /.md-listleft -->',
		'#weight' 				=> 15,
	);
	
	
	/* 1.	General Settings
	--------------------------------------------------------------------------*/
	$form['md_foto_settings']['general']['general_settings'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="general-settings" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #general-settings -->',
	);
	
		$form['md_foto_settings']['general']['general_settings']['css3_textarea'] = array(
			'#type' => 'checkbox',
			'#title' =>  t('Use the "resize" CSS3 property'),
			'#description'   => t('Check this if you wish to replace Drupal\'s textarea by resize CSS3 property'),
			'#default_value' => theme_get_setting('css3_textarea'),
		);
		
		$form['md_foto_settings']['general']['general_settings']['responsive'] = array(
			'#type' => 'checkbox',
			'#title' =>  t('Enable responsive'),
			'#default_value' => theme_get_setting('responsive'),
		);
		
		//Breadcrumb settings
		$form['md_foto_settings']['general']['general_settings']['breadcrumb_settings'] = array(
			'#type'          => 'fieldset',
			'#title'         => t('Breadcrumb settings'),
		);
		$form['md_foto_settings']['general']['general_settings']['breadcrumb_settings']['breadcrumb_display'] = array(
			'#type'          => 'select',
			'#title'         => t('Display breadcrumb'),
			'#default_value' => theme_get_setting('breadcrumb_display'),
			'#options'       => array(
														'yes'   => t('Yes'),
														'admin' => t('Only in admin section'),
														'no'    => t('No'),
													),
		);
		$form['md_foto_settings']['general']['general_settings']['breadcrumb_settings']['breadcrumb_separator'] = array(
			'#type'          => 'textfield',
			'#title'         => t('Breadcrumb separator'),
			'#description'   => t('Text only. Don\'t forget to include spaces.'),
			'#default_value' => theme_get_setting('breadcrumb_separator'),
			'#size'          => 5,
			'#maxlength'     => 10,
			'#prefix'        => '<div id="div-breadcrumb-collapse">', // jquery hook to show/hide optional widgets
		);
		$form['md_foto_settings']['general']['general_settings']['breadcrumb_settings']['breadcrumb_home'] = array(
			'#type'          => 'checkbox',
			'#title'         => t('Show home page link in breadcrumb'),
			'#default_value' => theme_get_setting('breadcrumb_home'),
		);
		$form['md_foto_settings']['general']['general_settings']['breadcrumb_settings']['breadcrumb_trailing'] = array(
			'#type'          => 'checkbox',
			'#title'         => t('Append a separator to the end of the breadcrumb'),
			'#default_value' => theme_get_setting('breadcrumb_trailing'),
			'#description'   => t('Useful when the breadcrumb is placed just before the title.'),
		);
		$form['md_foto_settings']['general']['general_settings']['breadcrumb_settings']['breadcrumb_title'] = array(
			'#type'          => 'checkbox',
			'#title'         => t('Append the content title to the end of the breadcrumb'),
			'#default_value' => theme_get_setting('breadcrumb_title'),
			'#description'   => t('Useful when the breadcrumb is not placed just before the title.'),
			'#suffix'        => '</div>', // #div-breadcrumb-collapse
		);
		
		// Search Settings
		if (module_exists('search')) {
			$form['md_foto_settings']['general']['general_settings']['search_container'] = array(
				'#type' => 'fieldset',
				'#title' => t('Search results'),
				'#description' => t('What additional information should be displayed on your search results page?'),
			);
			$form['md_foto_settings']['general']['general_settings']['search_container']['search_results']['search_snippet'] = array(
				'#type' => 'checkbox',
				'#title' => t('Display text snippet'),
				'#default_value' => theme_get_setting('search_snippet'),
			);
			$form['md_foto_settings']['general']['general_settings']['search_container']['search_results']['search_info_type'] = array(
				'#type' => 'checkbox',
				'#title' => t('Display content type'),
				'#default_value' => theme_get_setting('search_info_type'),
			);
			$form['md_foto_settings']['general']['general_settings']['search_container']['search_results']['search_info_user'] = array(
				'#type' => 'checkbox',
				'#title' => t('Display author name'),
				'#default_value' => theme_get_setting('search_info_user'),
			);
			$form['md_foto_settings']['general']['general_settings']['search_container']['search_results']['search_info_date'] = array(
				'#type' => 'checkbox',
				'#title' => t('Display posted date'),
				'#default_value' => theme_get_setting('search_info_date'),
			);
			$form['md_foto_settings']['general']['general_settings']['search_container']['search_results']['search_info_comment'] = array(
				'#type' => 'checkbox',
				'#title' => t('Display comment count'),
				'#default_value' => theme_get_setting('search_info_comment'),
			);
			$form['md_foto_settings']['general']['general_settings']['search_container']['search_results']['search_info_upload'] = array(
				'#type' => 'checkbox',
				'#title' => t('Display attachment count'),
				'#default_value' => theme_get_setting('search_info_upload'),
			);
		}
	
	/* 2.	Logo, Favicon & Webclip
	--------------------------------------------------------------------------*/
	$form['md_foto_settings']['general']['favicon_webclip'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="favicon-webclip" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #favicon-webclip -->',
	);
	
		$webclip_path = theme_get_setting('webclip_path');
		if (file_uri_scheme($webclip_path) == 'public') {
			$webclip_path = file_uri_target($webclip_path);
		}
		 
		$form['md_foto_settings']['general']['favicon_webclip']['webclip_path'] = array(
			'#type' 					=> 'textfield',
			'#title'					=> t('Path to custom Webclip'),
			'#description'   	=> t('A webclip is the icon that appears on a user\'s iPhone, iPad or Android device if they save your website to their home screen.<br />Upload an image at least <em>114x114px</em>'),
			'#default_value' 	=>  $webclip_path,
			'#prefix'					=> '<h3>Web Clip Settings</h3>',
		);
		
		$form['md_foto_settings']['general']['favicon_webclip']['webclip_upload'] = array(
			'#type' => 'file',
		);
		
		$form['md_foto_settings']['general']['favicon_webclip']['webclip_precomp'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('Use the default precomposed iOS touch icon.'),
	    '#default_value' => theme_get_setting('default_touch_icon_precomp'),
	    '#tree' => FALSE,
	    '#description' => t('Using a &apos;precomposed&apos; touch icon allows more control over the icon&apos;s appearance. iOS devices do not apply any special effects to these icons.'),
	  );
	
	

	/* 4.	Custom font
	--------------------------------------------------------------------------*/
	$form['md_foto_settings']['general']['custom_font'] = array(
		'#type' 					=> 'fieldset',
		'#weight' 				=> -5,
		'#prefix'  				=> '<div id="custom-font" class="md-tabcontent clearfix">',
		'#suffix'        => '</div><!-- / #custom-font -->',
	);

		$form['md_foto_settings']['general']['custom_font']['googlewebfonts'] = array(
			'#type' 					=> 'textarea',
			'#title'         => t('@import'),
			'#resizable' => FALSE,
			'#rows' => 1,
			'#description' => t("For example: &lt;link href='<strong>http://fonts.googleapis.com/css?family=Roboto+Condensed</strong>' rel='stylesheet' type='text/css'&gt"),
			'#default_value' 	=>  theme_get_setting('googlewebfonts'),
			'#prefix'					=> '<h3>Google Web Fonts</h3>
		<ul class="steps">
			<li>Go to <a href="http://www.google.com/webfonts" target="_blank">www.google.com/webfonts</a>, choose your fonts and add to collection</li>
			<li>Click &quot;Use&quot; in the bottom bar after choose fonts</li>
			<li>Find &quot;Add this code to your website&quot;, copy from <strong>http://</strong> to the nearest <strong>\'</strong> and paste it below to activate.</li>
			<li>After add code, press "Save Configuration" button to make font visible from Text/Typography tab</li>
		</ul>',
		);

		
	/* Hidden input
	--------------------------------------------------------------------------*/
	$form['md_foto_settings']['general']['savedcolor1'] = array(
		'#type'         	=> 'hidden',
		'#default_value' 	=> theme_get_setting('savedcolor1'),
		'#attributes' => array(
				'id' => 'savedcolor1',
			),
	);

}