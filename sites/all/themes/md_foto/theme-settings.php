<?php
/**
 * @file
 * Theme setting callbacks for the MD foto theme.
 */

drupal_add_css(drupal_get_path('theme', 'md_foto') . '/css/theme-settings.css', array('group' => CSS_THEME));
drupal_add_css(drupal_get_path('theme', 'md_foto') . '/js/colorpicker/css/colorpicker.css');

drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/jquery.cookie.js');

drupal_add_library('system', 'ui.widget');
drupal_add_library('system', 'ui.mouse');
drupal_add_library('system', 'ui.slider');
drupal_add_library('system', 'ui.tabs');

drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/colorpicker/js/colorpicker.js');
drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/jquery.dropkick-1.0.0.js');
drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/jquery.mousewheel.min.js');
drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/jquery.jstepper.min.js');
drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/jquery.choosefont.js');
drupal_add_js('http://maps.google.com/maps/api/js?sensor=false', 'external');
drupal_add_js(drupal_get_path('theme', 'md_foto') . '/js/theme-settings.js');

	require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/theme-settings-general.inc';
	require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/theme-settings-design.inc';
	require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/theme-settings-text.inc';
	require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/theme-settings-pages.inc';
  require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/theme-settings-nodes.inc';
	require_once DRUPAL_ROOT . '/' . drupal_get_path('theme', 'md_foto') . '/inc/theme-settings-code.inc';

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function md_foto_form_system_theme_settings_alter(&$form, &$form_state) {

	
	$form['md_foto_settings']['html_header'] = array(
  	'#markup' => '
<div class="md-links">
<a href="http://megadrupal.com/project/md-foto" target="_blank">Project Page</a> -
<a href="http://support.megadrupal.com/docs/md-foto-documentation" target="_blank">Theme Documentation</a> -
<a href="http://support.megadrupal.com/forums/theme-support/md-foto" target="_blank">Support Forum</a>
</div>
<div class="md-wrap">
  <div id="md-tabs">
		<div class="md-tabs-head"><div class="md-tabs-headcontent">
      <ul class="clearfix">
        <li class="tab-item first clearfix" id="tab-general-settings"> <a class="tab-link" href="#md-general-settings">
          <span class="tab-text">General Settings</span>
          </a> </li>
        <li class="tab-item clearfix" id="tab-design"> <a class="tab-link" href="#md-design">
          <span class="tab-text">Design</span>
          </a> </li>
        <li class="tab-item clearfix" id="tab-text-typography"> <a class="tab-link" href="#md-text-typography">
          <span class="tab-text">Text/Typography</span>
          </a> </li>
        <li class="tab-item clearfix" id="tab-pages"> <a class="tab-link" href="#md-pages">
          <span class="tab-text">Pages</span>
          </a> </li>
        <li class="tab-item clearfix" id="tab-nodes"> <a class="tab-link" href="#md-nodes">
          <span class="tab-text">Node display</span>
          </a> </li>
        <li class="tab-item clearfix" id="tab-custom-code"> <a class="tab-link" href="#md-custom-code">
          <span class="tab-text">Custom code</span>
          </a> </li>
      </ul>
    </div></div><!-- /.md-tabs-head -->',
		'#weight' => -99,
	);
	
	
	md_foto_theme_settings_generalsettings($form, $form_state);
	
	$fontarray = array(
							'0'   => t('Default'),
							'1'   => t('Arial'),
							'2'   => t('Verdana'),
							'3'   => t('Trebuchet MS'),
							'4'   => t('Georgia'),
							'5'   => t('Times New Roman'),
							'6'   => t('Tahoma'),
                        );
	$fontvars = array(
			'0'	=> array(
           'CSS' 		=>	'',
					 'Weight'	=>	'n4',
      ),
      '1'	=> array(
           'CSS' 		=>	'Arial, sans-serif',
					 'Weight'	=>	'n4, n7, i4, i7',
      ),
			'2'	=> array(
           'CSS' 		=>	'Verdana, Geneva, sans-serif',
					 'Weight'	=>	'n4, n7, i4, i7',
      ),
			'3'	=> array(
           'CSS' 		=>	'Trebuchet MS, Tahoma, sans-serif',
					 'Weight'	=>	'n4, n7, i4, i7',
      ),
			'4'	=> array(
           'CSS' 		=>	'Georgia, serif',
					 'Weight'	=>	'n4, n7, i4, i7',
      ),
			'5'	=> array(
           'CSS' 		=>	'Times New Roman, serif',
					 'Weight'	=>	'n4, n7, i4, i7',
      ),
			'6'	=> array(
           'CSS' 		=>	'Tahoma, Geneva, Verdana, sans-serif',
					 'Weight'	=>	'n4, n7, i4, i7',
      ),
  );
	
	if (theme_get_setting('googlewebfonts')) {
		$googlewebfonts = theme_get_setting('googlewebfonts');
		drupal_add_css('http://' . $googlewebfonts, 'external');
		
		preg_match('/([^\?]+)(\?family=)?([^&\']+)/i',$googlewebfonts, $matches);
		$gfonts = explode("|", $matches[3]);

		for ($i = 0; $i < count($gfonts); $i++) {
			$gfontsdetail = explode(":", $gfonts[$i]);
			$gfontname = str_replace("+", " ", $gfontsdetail['0']);
			$fontarray[$gfontsdetail[0]] = $gfontname;
			if (array_key_exists('1', $gfontsdetail)) {
				$tmpft =  explode(",", $gfontsdetail['1']);
				$gfontweigth[$i] = "";
				for ($j = 0; $j < count($tmpft); $j++) {
					if (preg_match("/italic/i", $tmpft[$j])) {
					    $gfontstyle = "i";
					} else {
					    $gfontstyle = "n";
					}
					$tmpw = str_replace("italic", "",$tmpft[$j]);
					$seperator = ",";
					if ($j == (count($tmpft) - 1)) {
						$seperator = "";
					}
					if ($tmpw) {
					  $gfontweigth[$i] .= $gfontstyle.str_replace("00", "",$tmpw).$seperator;
					} else {
						$gfontweigth[$i] .= "n4".$seperator;
					}
				}
			} else {
				$gfontweigth[$i] = "n4";
			}
			$fontvars[$gfontsdetail['0']] = array(
				'CSS' 		=>	'"'.$gfontname.'"',
				'Weight'	=>	$gfontweigth[$i],
			);
		}
	}
	
	drupal_add_js(array('font_array' => $fontarray), 'setting');
	drupal_add_js(array('font_vars' => $fontvars), 'setting');

	md_foto_theme_settings_design($form, $form_state);
	md_foto_theme_settings_text($form, $form_state);
	md_foto_theme_settings_pages($form, $form_state);
  md_foto_theme_settings_nodes($form, $form_state);
	md_foto_theme_settings_code($form, $form_state);

	
	$form['md_foto_settings']['html_footer'] = array(
  	'#markup' => '
	</div><!-- /#md-tabs -->
</div><!-- /.md-wrap -->',
		'#weight' => 99,
	);
	
	$form['#submit'][]   = 'md_foto_settings_submit';
}

function md_foto_settings_submit($form, &$form_state) {
  $settings = array();
 
  // Check for a new uploaded file, and use that if available.
  if ($file = file_save_upload('bg_upload')) {
    $parts = pathinfo($file->filename);
    $destination = 'public://' . $parts['basename'];
    $file->status = FILE_STATUS_PERMANENT;
		if (file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
			$_POST['bg_path'] = $form_state['values']['bg_path'] = $destination;
		}
  }

} 