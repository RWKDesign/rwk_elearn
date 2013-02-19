<?php

/**
 *Implement javascript file 
 */
function acend_theme_preprocess_page(&$vars) {

	drupal_add_js(drupal_get_path('theme', 'acend_theme') . '/video_end.js');

	$vars['scripts'] = drupal_get_js();

}











?>
