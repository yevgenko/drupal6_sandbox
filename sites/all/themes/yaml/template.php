<?php
// $Id: template.php,v 3.1.0.12 2009/06/07 00:00:00 hass Exp $

/**
 * "Yet Another Multicolumn Layout" for Drupal
 *
 * (en) Central template for theme specific functions
 * (de) Zentrales Template für theme spezifische Funktionen
 *
 * @copyright       Copyright 2006-2009, Alexander Hass
 * @license         http://www.yaml-fuer-drupal.de/en/terms-of-use
 * @link            http://www.yaml-for-drupal.com
 * @package         yaml-for-drupal
 * @version         6.x-3.1.0.12
 * @lastmodified    2009-06-07
 */

/**
 * Include the central template.inc with global theme functions
 */
include_once(realpath(dirname(__FILE__) .'/template.inc'));

/**
 * Alter some Drupal variables required by Theme.
 */
function yaml_preprocess_page(&$vars) {
  global $user, $theme;

  // Install default theme settings. Need to run first of all.
  $yaml_theme_settings_install_function = '_'. $theme .'_theme_settings_install';
  if (function_exists($yaml_theme_settings_install_function)) {
    $yaml_theme_settings_install_function($theme);
  }

  // Load the XML prolog for standard compliant browsers if caching is inactive.
  // The function page_set_cache() does not cache pages if $user->uid has a value.
  // Additional the XML prolog can only added to YAML for Drupal if a user is
  // logged into Drupal (caching inactive) or caching is globaly disabled on the site.
  if ((_browser_xml_prolog_compliant() && $user->uid) || (_browser_xml_prolog_compliant() && !(variable_get('cache', 0)))) {
    $vars['xml_prolog'] = '<?xml version="1.0" encoding="utf-8"?>' . "\n";
  }

  // Add gfxborder to the page layout.
  if (theme_get_setting('yaml_layout_page_gfxborder')) {
    $vars['border_top'] = '<div id="border-top"><div id="edge-tl"> </div><div id="edge-tr"> </div></div>' . "\n";
    $vars['border_bottom'] = '<div id="border-bottom"><div id="edge-bl"> </div><div id="edge-br"> </div></div>' . "\n";
  }

  // Dynamic sidebar switching.
  // Limit code execution to "base theme". Code inside the below switch statement
  // is only executed for the specific theme or subtheme.
  switch ($theme) {
    case 'yaml':
    case 'yaml_3col_standard':
      if ($vars['layout'] == 'none') {
        $vars['body_classes'] = $vars['body_classes'] .' hideboth';
      }
      elseif ($vars['layout'] == 'left') {
        $vars['body_classes'] = $vars['body_classes'] .' hidecol2';
      }
      elseif ($vars['layout'] == 'right') {
        $vars['body_classes'] = $vars['body_classes'] .' hidecol1';
      }
      break;

    case 'yaml_2col_13':
    case 'yaml_2col_31':
      if ($vars['layout'] == 'none') {
        $vars['body_classes'] = $vars['body_classes'] .' hideboth';
      }
      break;
  }

  // Add YAML Theme styles.
  $yaml_css_function = '_'. $theme .'_add_css';
  if (function_exists($yaml_css_function)) {
    $vars['css'] = $yaml_css_function($vars);
  }
  $yaml_styles_function = '_'. $theme .'_add_styles';
  if (function_exists($yaml_styles_function)) {
    $vars['styles'] = $yaml_styles_function($vars);
  }
}

/**
 * Alter some Drupal variables required by maintenance theme.
 */
function phptemplate_preprocess_maintenance_page(&$vars) {
  // Dynamic sidebar switching. Turn off sidebars in maintenance mode.
  $vars['body_classes'] = $vars['body_classes'] .' hideboth';

  $vars['css'] = _yaml_add_css($vars);
  $vars['styles'] = _yaml_add_styles($vars);
}

/**
 * Implementation of hook_theme().
 */
function yaml_theme() {
  return array(
    'links_secondary' => array(
      'arguments' => array(
        'links' => NULL,
        'attributes' => array('class' => 'links'),
        'settings' => array(
          'delimiter' => ' | ',
          'leftcab' => NULL,
          'rightcab' => NULL,
        )
      ),
      'template' => 'links-secondary',
    ),
  );
}

/**
 * Theme CSS files
 *
 * Workaround for CSS aggregate and compress feature in Drupal 6.x
 */
function _yaml_add_css($vars = array()) {

  $base_theme_directory = $vars['directory'];

  // Add core and layout specific styles
  drupal_add_css($base_theme_directory .'/yaml/core/base.css', 'theme');
  drupal_add_css($base_theme_directory .'/css/screen/basemod.css', 'theme');
  drupal_add_css($base_theme_directory .'/css/screen/basemod_dynamic_layout_switching.css', 'theme');
  drupal_add_css($base_theme_directory .'/css/screen/basemod_drupal.css', 'theme');

  if (theme_get_setting('yaml_layout_page_gfxborder')) {
    drupal_add_css($base_theme_directory .'/css/screen/basemod_gfxborder.css', 'theme');
  }

  // Add horizontal navigations
  $yaml_nav_primary = theme_get_setting('yaml_nav_primary');
  if ($yaml_nav_primary == 1) {
    drupal_add_css($base_theme_directory .'/css/navigation/nav_shinybuttons.css', 'theme');
  }
  else {
    drupal_add_css($base_theme_directory .'/css/navigation/nav_slidingdoor.css', 'theme');
  }

  // Add vertical navigations
  $yaml_nav_vertical = theme_get_setting('yaml_nav_vertical');
  if ($yaml_nav_vertical == 1) {
    // There are currently no additional navigations available, add here if you create your own.
  }
  else {
    drupal_add_css($base_theme_directory .'/css/navigation/nav_vlist_drupal.css', 'theme');
  }

  // Content CSS files
  drupal_add_css($base_theme_directory .'/css/screen/content.css', 'theme');

  // Add custom module styles
  _yaml_add_css_modules($base_theme_directory);

  // Add print CSS files
  drupal_add_css($base_theme_directory .'/yaml/core/print_base.css', 'theme');
  drupal_add_css($base_theme_directory .'/css/print/print_003.css', 'theme');
  drupal_add_css($base_theme_directory .'/css/print/print_drupal.css', 'theme');

  // Add debug CSS files
  if (theme_get_setting('yaml_debug') == 1) {
    drupal_add_css($base_theme_directory .'/yaml/debug/debug.css', 'theme', 'all', FALSE);
  }

  // Remove the style.css added as first array item and move it to the end
  // of the styles array. This allows to use themes style.css and keep
  // the required CSS cascading order intact for CSS overriding.
  $css = drupal_add_css();
  if (isset($css['all']['theme'][$vars['directory'] .'/style.css'])) {
    unset($css['all']['theme'][$vars['directory'] .'/style.css']);
    $css['all']['theme'][$vars['directory'] .'/style.css'] = TRUE;
  }
  if (isset($css['all']['theme'][$vars['directory'] .'/style-rtl.css'])) {
    unset($css['all']['theme'][$vars['directory'] .'/style-rtl.css']);
    $css['all']['theme'][$vars['directory'] .'/style-rtl.css'] = TRUE;
  }
  
  // Return CSS array
  return $css;
}

function _yaml_add_styles($vars = array()) {

  global $language;
  $base_theme_directory = $vars['directory'];
  $styles = drupal_get_css($vars['css']);

  // Page settings
  $styles .= _yaml_get_css_themesettings('132');

  // The styles array is complete, get the styled css and append the
  // IE Hacks. Additional this allows to dynamically add packed or other iehacks.
  $styles .= "<!--[if lte IE 7]>\n";
  $styles .= '<style type="text/css" media="all">' . "\n";
  $styles .= '@import "'. base_path() . $base_theme_directory .'/yaml/core/iehacks'. (variable_get('preprocess_css', FALSE) ? '.pack' : '') .'.css";' . "\n";
  if (defined('LANGUAGE_RTL') && $language->direction == LANGUAGE_RTL) {
    $styles .= '@import "'. base_path() . $base_theme_directory .'/yaml/core/iehacks-rtl'. (variable_get('preprocess_css', FALSE) ? '.pack' : '') .'.css";' . "\n";
  }
  $styles .= '@import "'. base_path() . $base_theme_directory .'/css/patches/patch_nav_vlist_drupal.css";' . "\n";
  $styles .= '@import "'. base_path() . $base_theme_directory .'/css/patches/patch_3col_standard.css";' . "\n";
  $styles .= '@import "'. base_path() . $base_theme_directory .'/css/patches/patch_drupal.css";' . "\n";

  // IE page settings.
  $styles_ie = _yaml_get_css_ie_themesettings('132');
  if (!empty($styles_ie)) {
    $styles .= $styles_ie . "\n";
  }
  $styles .= "</style>\n";
  $styles .= "<![endif]-->\n";

  // IE 6 settings and styles.
  $styles_ie6 = _yaml_get_css_ie6_themesettings('132', $base_theme_directory);
  if (!empty($styles_ie6)) {
    $styles .= "<!--[if lte IE 6]>\n";
    $styles .= '<style type="text/css" media="all">'. $styles_ie6 ."</style>\n";
    $styles .= "<![endif]-->\n";
  }

  // Return themed styles
  return $styles;
}

/**
 * There is currently no .install support available for themes and the
 * following is a workaround to initialize new theme settings.
 *
 * - 'yaml_layout_page_width' is a new setting in 6.x-3.0.6.9
 */
function _yaml_theme_settings_install($theme) {
  if ((is_null(theme_get_setting('yaml_layout_page_width')) || theme_get_setting('yaml_layout_page_width_col3') === 'auto')) {

    // Save default theme settings.
    $defaults = array(
      'yaml_nav_primary' => 0,
      'yaml_nav_vertical' => 0,
      'yaml_layout_page_width' => 'auto',
      'yaml_layout_page_width_min' => '740px',
      'yaml_layout_page_width_max' => '80em',
      'yaml_layout_page_width_col1' => '25%',
      'yaml_layout_page_width_col2' => 'auto',
      'yaml_layout_page_width_col3' => '25%',
      'yaml_layout_page_align' => 'center',
      'yaml_layout_page_gfxborder' => 0,
      'yaml_msie_hack_pngfix' => 1,
      'yaml_msie_hack_minmaxwidth' => 1,
      'yaml_debug' => 0,
      'yaml_display_link_validation_xhtml' => 0,
      'yaml_display_link_validation_css' => 0,
      'yaml_display_link_license_yaml' => 1,
      'yaml_display_link_license_yamlfd' => 1,
    );

    $merged_settings = array_merge($defaults, theme_get_settings($theme));

    // Upgrade 'yaml' from 6.x-3.0.4.8 to 6.x-3.0.6.9.
    if (theme_get_setting('yaml_layout_page_width_col3') == 'auto') {
      $merged_settings['yaml_layout_page_width_col2'] = 'auto';
      $merged_settings['yaml_layout_page_width_col3'] = '25%';
    }

    variable_set(
      str_replace('/', '_', 'theme_'. $theme .'_settings'),
      $merged_settings
    );

    // Force refresh of Drupal internals.
    theme_get_setting('', TRUE);
  }
}
