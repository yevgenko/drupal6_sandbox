<?php
// $Id: template.inc,v 3.1.0.12 2009/06/07 00:00:00 hass Exp $

/**
 * "Yet Another Multicolumn Layout" for Drupal
 *
 * (en) Central template for global theme functions
 * (de) Zentrales Template für globale Theme-Funktionen
 *
 * @copyright       Copyright 2006-2009, Alexander Hass
 * @license         http://www.yaml-fuer-drupal.de/en/terms-of-use
 * @link            http://www.yaml-for-drupal.com
 * @package         yaml-for-drupal
 * @version         6.x-3.1.0.12
 * @lastmodified    2009-06-07
 */

/**
 * !!! Enable ONLY in development mode !!!
 *
 * This function will avoid caching issues when adding or removing theme
 * functions and templates. Editing existing functions and templates does
 * not require a registry rebuild.
 *
 * See http://drupal.org/node/173880#theme-registry for more information.
 */
//drupal_rebuild_theme_registry();

/**
 * This snippet will add module styles if module is installed and active.
 * TODO: Add CSS only if page requires the file.
 */
function _yaml_add_css_modules($base_theme_directory = '') {

  // Add module styles if modules exists.
  // The unique module directory name should be used as CSS filename.
  // If you'd like to fully replace a module stylesheet you can simply
  // drop a file with the same name used in the module to the theme.
  // The below code only overrides specific parts of module styles. 
  if (module_exists('devel')) {
    drupal_add_css($base_theme_directory .'/css/modules/yaml-devel.css', 'theme');
  }
  if (module_exists('menu_block_split')) {
    drupal_add_css($base_theme_directory .'/css/modules/yaml-menu_block_split.css', 'theme');
  }
  if (module_exists('project') && arg(0) == 'project') {
    drupal_add_css($base_theme_directory .'/css/modules/yaml-project.css', 'theme');
  }
  if (module_exists('service_links')) {
    drupal_add_css($base_theme_directory .'/css/modules/yaml-service_links.css', 'theme');
  }
  if (module_exists('site_map') && arg(0) == 'sitemap') {
    drupal_add_css($base_theme_directory .'/css/modules/yaml-site_map.css', 'theme');
  }
  if (module_exists('vertical_tabs')) {
    drupal_add_css($base_theme_directory .'/css/modules/yaml-vertical_tabs.css', 'theme');
  }

  // Add non Drupal.org modules here.
  // To avoid naming conflicts an underscore should be added as prefix
  // to CSS filenames of modules not contributed on drupal.org.
  // if (foo == bar) {
  //   drupal_add_css($base_theme_directory .'/css/modules/_example.css', 'theme');
  // }

}

/**
 * Add backlinks required by license to footer.
 *
 * This back linking maybe only removed, if you possess
 * a YAML Framework and YAML for Drupal license.
 *
 * For more information read the "YAML" and "YAML for Drupal" license, please.
 *
 * Licenses:
 * YAML - http://www.yaml.de
 * YAML for Drupal - http://www.yaml-for-drupal.com
 */
function phptemplate_footer($output = '', $delimiter = ' | ', $leftcab = '', $rightcab = '') {

  $footer_items = array();

  // If you don't like the validation links, simply uncheck on theme settings page.
  if (theme_get_setting('yaml_display_link_validation_xhtml') !== 0) {
    $footer_items[] = t('<a href="http://validator.w3.org/check/referer" title="Validate XHTML">XHTML</a>');
  }

  if (theme_get_setting('yaml_display_link_validation_css') !== 0) {
    $footer_items[] = t('<a href="http://jigsaw.w3.org/css-validator/check/referer" title="Validate CSS">CSS</a>');
  }

  /**
   * GERMAN:
   * Diese Rückverlinkung darf nur entfernt werden,
   * wenn Sie eine YAML-Framework Lizenz besitzen.
   * :: Lizenzbedingungen: http://www.yaml.de
   *
   * ENGLISH:
   * This back linking maybe only removed,
   * if you possess a YAML Framework license.
   * :: License conditions: http://www.yaml.de
   */
  if (theme_get_setting('yaml_display_link_license_yaml') !== 0) {
    $footer_items[] = t('Layout based on <a href="http://www.yaml.de/">YAML</a>');
  }

  /**
   * GERMAN:
   * Diese Rückverlinkung darf nur entfernt werden,
   * wenn Sie eine YAML für Drupal Lizenz besitzen.
   * :: Lizenzbedingungen: http://www.yaml-fuer-drupal.de
   *
   * ENGLISH:
   * This back linking maybe only removed,
   * if you have possess a YAML for Drupal license.
   * :: License conditions: http://www.yaml-for-drupal.com
   */
  if (theme_get_setting('yaml_display_link_license_yamlfd') !== 0) {
    $footer_items[] = t('<a href="http://www.yaml-fuer-drupal.de/" title="YAML for Drupal Theme">YAML for Drupal</a> Theme');
  }

  // Build footer and links if exists
  $footer_links_output = '';
  if (!empty($footer_items)) {
    $footer_links_output = implode($delimiter, $footer_items);
  }

  $footer_output = '';
  if (!empty($output) && !empty($footer_links_output)) {
    $footer_output = $output .'<br />'. $leftcab . $footer_links_output . $rightcab;
  }
  elseif (empty($output) && !empty($footer_links_output)) {
    $footer_output = $leftcab . $footer_links_output . $rightcab;
  }
  else {
    $footer_output = $output;
  }

  // Return footer
  return $footer_output;
}

/**
 * We will detect if client is Internet Explorer. Then we are able to add
 * the XML prolog for XHTML Standard Compliance Mode for other browsers.
 *
 * Today IE is the only known software we need to workaround and therefor we
 * only detect IE browser and suppose all other browsers render correctly with
 * XML prolog.
 */
function _browser_xml_prolog_compliant() {
  $ua = $_SERVER['HTTP_USER_AGENT'];

  if (eregi('msie', $ua) && !eregi('opera', $ua)) {
    // This is not a Opera pose as IE
    $clientdata = explode(' ', stristr($ua, 'msie'));
    $client['version'] = $clientdata[1];

    if ($client['version'] >= 7) {
      // IE >= 7.0: http://blogs.msdn.com/ie/archive/2005/09/15/467901.aspx
      $xml_prolog_compliant = TRUE;
    }
    else {
      // IE <= 6.0
      $xml_prolog_compliant = FALSE;
    }
  }
  else {
    // all other browsers
    $xml_prolog_compliant = TRUE;
  }

  return $xml_prolog_compliant;
}


function _yaml_get_css_themesettings($column_order = '') {
  $styles = '';
  $yaml_layout_page_width_col1 = theme_get_setting('yaml_layout_page_width_col1');
  $yaml_layout_page_width_col3 = theme_get_setting('yaml_layout_page_width_col3');

  $settings = '';
  switch ($column_order) {
    case '132':
      // 3 column standard layout
      if ($yaml_layout_page_width_col1 != '25%' || $yaml_layout_page_width_col3 != '25%') {
        if (!empty($yaml_layout_page_width_col1)) {
          $settings .= '#col1 { width: '. $yaml_layout_page_width_col1 .' }';
        }
        if (!empty($yaml_layout_page_width_col3)) {
          $settings .= '#col2 { width: '. $yaml_layout_page_width_col3 .' }';
        }
        if (!empty($yaml_layout_page_width_col1) && !empty($yaml_layout_page_width_col3)) {
          $settings .= '#col3 { margin: 0 '. $yaml_layout_page_width_col3 .' 0 '. $yaml_layout_page_width_col1 .' }';
        }
      }
      break;

    case '13':
      // 2 column 12 layout
      if ($yaml_layout_page_width_col1 != '25%') {
        if (!empty($yaml_layout_page_width_col1)) {
          $settings .= '#col1 { width: '. $yaml_layout_page_width_col1 .' }';
        }
        if (!empty($yaml_layout_page_width_col1) && !empty($yaml_layout_page_width_col3)) {
          $settings .= '#col3 { width: '. $yaml_layout_page_width_col3 .'; margin: 0 0 0 '. $yaml_layout_page_width_col1 .' }';
        }
      }
      break;

    case '31':
      // 2 columns 31 layout
      if ($yaml_layout_page_width_col1 != '25%') {
        if (!empty($yaml_layout_page_width_col1)) {
          $settings .= '#col1 { width: '. $yaml_layout_page_width_col1 .' }';
        }
        if (!empty($yaml_layout_page_width_col1) && !empty($yaml_layout_page_width_col3)) {
          $settings .= '#col3 { width: '. $yaml_layout_page_width_col3 .'; margin: 0 '. $yaml_layout_page_width_col1 .' 0 0 }';
        }
      }
      break;
  }
  
  if (!empty($settings)) {
    $styles .= '<style type="text/css">'. $settings .'</style>' . "\n";
  }  
  
  // Page settings
  $yaml_layout_page_width_min = theme_get_setting('yaml_layout_page_width_min');
  $yaml_layout_page_width_max = theme_get_setting('yaml_layout_page_width_max');
  $yaml_layout_page_align = theme_get_setting('yaml_layout_page_align');
  switch ($yaml_layout_page_align) {
    case 'left':
      $styles .= '<style type="text/css">.page_margins { margin-right: auto; margin-left: 0; width: '.theme_get_setting('yaml_layout_page_width') .'; min-width: '. check_plain($yaml_layout_page_width_min) .'; max-width: '. check_plain($yaml_layout_page_width_max) .' }</style>' . "\n";
      break;

    case 'right':
      $styles .= '<style type="text/css">.page_margins { margin-left: auto; margin-right: 0; width: '.theme_get_setting('yaml_layout_page_width') .'; min-width: '. check_plain($yaml_layout_page_width_min) .'; max-width: '. check_plain($yaml_layout_page_width_max) .' }</style>' . "\n";
      break;

    case 'center':
      if ($yaml_layout_page_width_min != '740px' || $yaml_layout_page_width_max != '80em') {
        $styles .= '<style type="text/css">.page_margins { width: '.theme_get_setting('yaml_layout_page_width') .'; min-width: '. check_plain($yaml_layout_page_width_min) .'; max-width: '. check_plain($yaml_layout_page_width_max) .' }</style>' . "\n";
      }
      break;
  }
  return $styles;
}

function _yaml_get_css_ie_themesettings($column_order = '') {
  $styles_ie = '';
  $yaml_layout_page_width_col1 = theme_get_setting('yaml_layout_page_width_col1');
  $yaml_layout_page_width_col3 = theme_get_setting('yaml_layout_page_width_col3');

  // Calculate hacked values for IE.
  $yaml_layout_page_width_col1_ie = '24%';
  if (preg_match('/^(\d{1,5}[.,]?\d{1,3}?)(px|em|%)$/i', $yaml_layout_page_width_col1)) {
    $yaml_layout_page_width_col1_ie = preg_replace('/^(\d{1,5}[.,]?\d{1,3}?)(px|em|%)$/ei', "''. (('$2' == 'px') ? ($1 - 3) : ($1 - 1)) .'$2'", $yaml_layout_page_width_col1);
  }
  $yaml_layout_page_width_col3_ie = '24%';
  if (preg_match('/^(\d{1,5}[.,]?\d{1,3}?)(px|em|%)$/i', $yaml_layout_page_width_col3)) {
    $yaml_layout_page_width_col3_ie = preg_replace('/^(\d{1,5}[.,]?\d{1,3}?)(px|em|%)$/ei', "''. (('$2' == 'px') ? ($1 - 3) : ($1 - 1)) .'$2'", $yaml_layout_page_width_col3);
  }

  switch ($column_order) {
    case '132':
      if ($yaml_layout_page_width_col1 != '25%' || $yaml_layout_page_width_col3 != '25%') {
        $styles_ie .= '* html #col3 { margin-left: '. $yaml_layout_page_width_col1_ie .'; margin-right: '. $yaml_layout_page_width_col3_ie .' }';
      }
      break;

    case '13':
      if ($yaml_layout_page_width_col1 != '25%') {
        $styles_ie .= '* html #col3 { margin-left: '. $yaml_layout_page_width_col1_ie .'; }';
      }
      break;

    case '31':
      if ($yaml_layout_page_width_col1 != '25%') {
        $styles_ie .= '* html #col3 { margin-right: '. $yaml_layout_page_width_col1_ie .'; }';
      }
      break;
  }
  
  return $styles_ie;
}

function _yaml_get_css_ie6_themesettings($column_order = '', $base_theme_directory = '') {
  $styles_ie6 = '';

  // Add some IE6 CSS hacks.
  if (theme_get_setting('yaml_msie_hack_pngfix') == 1) {
    $styles_ie6 .= 'img, .pngtrans { behavior: url('. base_path() . $base_theme_directory .'/images/pngfix/iepngfix.htc); }';
  }

  // See http://www.yaml.de/en/documentation/practice/minimum-maximum-widths.html
  if (theme_get_setting('yaml_layout_page_width') == 'auto') {
    if (theme_get_setting('yaml_msie_hack_minmaxwidth') == 1) {
      // Simulate min-/max-width for IE <=6.
      // TODO: (83/75) = (rounded YAMLfD font-size/YAML font-size).
      $styles_ie6 .= '* html .page_margins { width: '. theme_get_setting('yaml_layout_page_width_max') .'; width: expression((document.documentElement && document.documentElement.clientHeight) ? (document.documentElement.clientWidth < '. preg_replace('/[\D]+/', '', theme_get_setting('yaml_layout_page_width_min')) .') ? "'. theme_get_setting('yaml_layout_page_width_min') .'" : (( document.documentElement.clientWidth > ('. preg_replace('/[\D]+/', '', theme_get_setting('yaml_layout_page_width_max')) * round((83/75), 2) .' * parseInt(document.documentElement.currentStyle.fontSize))) ? "'. theme_get_setting('yaml_layout_page_width_max') .'" : "auto") : (document.body.clientWidth < '. preg_replace('/[\D]+/', '', theme_get_setting('yaml_layout_page_width_min')) .') ? "'. theme_get_setting('yaml_layout_page_width_min') .'" : (( document.body.clientWidth > ('. preg_replace('/[\D]+/', '', theme_get_setting('yaml_layout_page_width_max')) * round((83/75), 2) .' * parseInt(document.body.currentStyle.fontSize))) ? "'. theme_get_setting('yaml_layout_page_width_max') .'" : "auto"));}';
    }
    else {
      // IE <=6 does not support min-/max-width what results hereby in the configured fixed max-width.
      $styles_ie6 .= '* html .page_margins { width: '. theme_get_setting('yaml_layout_page_width_max') .' }';
    }
  }
  return $styles_ie6;
}