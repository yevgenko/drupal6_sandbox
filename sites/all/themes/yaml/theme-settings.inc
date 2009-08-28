<?php
// $Id: theme-settings.inc,v 3.1.0.12 2009/06/07 00:00:00 hass Exp $

/**
 * "Yet Another Multicolumn Layout" for Drupal
 *
 * (en) Integration of Theme specific settings
 * (de) Integration von Theme spezifischen Einstellungen
 *
 * @copyright       Copyright 2006-2009, Alexander Hass
 * @license         http://www.yaml-fuer-drupal.de/en/terms-of-use
 * @link            http://www.yaml-for-drupal.com
 * @package         yaml-for-drupal
 * @version         6.x-3.1.0.12
 * @lastmodified    2009-06-07
 */

/**
 * Allow configuration of theme settings, currently not available for PHP templates.
 * This feature becomes a core feature in Drupal 6.x for phptemplate based themes.
 *
 * Currently you must install Theme Settings API 5.x module for this functionality.
 * Look at http://drupal.org/project/themesettingsapi for the download.
 * 
 * @param $saved_settings
 *   Array with all saved theme settings.
 * @param $defaults
 *   Array with default theme settings for the layout.
 * @param $column_order
 *   The order of layout columns. If the value is blank
 *   there are no inputs shown.
 */
function _yaml_get_themesettings_form($saved_settings, $defaults, $column_order = '') {

  // Merge the variables and their default values.
  $variables = array_merge($defaults, $saved_settings);

  // Build some jQuery stuff to make layout configuration more user friendly.
$yaml_builder_js = '$(document).ready(function(){
  $(window).load(function() {
    update_builder_fields($("#edit-yaml-layout-page-width"));
  })
  $("#edit-yaml-layout-page-width").keyup(function() {
    update_builder_fields($("#edit-yaml-layout-page-width"));
  })

  function update_builder_fields(field) {
    switch (field.val()) {
      case "auto":
        $("#edit-yaml-layout-page-width-min").removeAttr("readonly");
        $("#edit-yaml-layout-page-width-min").removeClass("disabled");
        $("#edit-yaml-layout-page-width-min").val('. drupal_to_js($variables['yaml_layout_page_width_min']) .');
        $("#edit-yaml-layout-page-width-max").removeAttr("readonly");
        $("#edit-yaml-layout-page-width-max").removeClass("disabled");
        $("#edit-yaml-layout-page-width-max").val('. drupal_to_js($variables['yaml_layout_page_width_max']) .');
        break;

      default:
        $("#edit-yaml-layout-page-width-min").val("inherit");
        $("#edit-yaml-layout-page-width-min").attr("readonly", "readonly");
        $("#edit-yaml-layout-page-width-min").addClass("disabled");
        $("#edit-yaml-layout-page-width-max").val("none");
        $("#edit-yaml-layout-page-width-max").attr("readonly", "readonly");
        $("#edit-yaml-layout-page-width-max").addClass("disabled");
    }
  }
});';
  drupal_add_js($yaml_builder_js, 'inline', 'header', FALSE, TRUE, FALSE);

  // Create the form using Form API
  $form['layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout'),
    '#collapsible' => true,
    '#collapsed' => false,
    '#description' => t('Leave the following defaults if you edit the basemod.ccs file directly. In this case there will be no extra inline settings added to the page by this configuration module.'),
    '#attributes' => array('id' => 'theme-settings-layout')
  );
  $form['layout']['yaml_layout_page_align'] = array(
    '#type' => 'select',
    '#title' => t('Page alignment'),
    '#default_value' => $variables['yaml_layout_page_align'],
    '#options' => array(
      'left' => t('left'),
      'center' => t('center'),
      'right' => t('right'),
    ),
    '#description' => t('Align the page to right, center or left. Default: "@default".', array('@default' => $defaults['yaml_layout_page_align'])),
  );
  $form['layout']['yaml_layout_page_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Page width'),
    '#default_value' => $variables['yaml_layout_page_width'],
    '#description' => t('Defines the fixed page width in <em>px</em> or <em>em</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width'])),
    '#required' => TRUE,
    '#size' => '10'
  );
  $form['layout']['yaml_layout_page_width_min'] = array(
    '#type' => 'textfield',
    '#title' => t('Page min-width'),
    '#default_value' => $variables['yaml_layout_page_width_min'],
    '#description' => t('Defines the minium page width in <em>px</em> or <em>em</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_min'])),
    '#required' => TRUE,
    '#size' => '10'
  );
  $form['layout']['yaml_layout_page_width_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Page max-width'),
    '#default_value' => $variables['yaml_layout_page_width_max'],
    '#description' => t('Defines the maximum page width in <em>px</em> or <em>em</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_max'])),
    '#required' => TRUE,
    '#size' => '10',
    '#suffix' => '<hr />'
  );

  switch ($column_order) {
    case '132':
      $form['layout']['yaml_layout_page_width_col1'] = array(
        '#type' => 'textfield',
        '#title' => t('Left sidebar'),
        '#default_value' => $variables['yaml_layout_page_width_col1'],
        '#description' => t('Defines the left column width in <em>px</em>, <em>em</em> or <em>%</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_col1'])),
        '#required' => TRUE,
        '#size' => '10'
      );
      $form['layout']['yaml_layout_page_width_col2'] = array(
        '#type' => 'textfield',
        '#title' => t('Content'),
        '#default_value' => $variables['yaml_layout_page_width_col2'],
        '#attributes' => array(
          'class' => 'disabled',
          'readonly' => 'readonly',
        ),
        '#size' => '10'
      );
      $form['layout']['yaml_layout_page_width_col3'] = array(
        '#type' => 'textfield',
        '#title' => t('Right sidebar'),
        '#default_value' => $variables['yaml_layout_page_width_col3'],
        '#description' => t('Defines the right column width in <em>px</em>, <em>em</em> or <em>%</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_col3'])),
        '#required' => TRUE,
        '#size' => '10',
        '#suffix' => '<hr />'
      );
      break;

    case '13':
      $form['layout']['yaml_layout_page_width_col1'] = array(
        '#type' => 'textfield',
        '#title' => t('Left sidebar'),
        '#default_value' => $variables['yaml_layout_page_width_col1'],
        '#description' => t('Defines the left column width in <em>px</em>, <em>em</em> or <em>%</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_col1'])),
        '#required' => TRUE,
        '#size' => '10'
      );
      $form['layout']['yaml_layout_page_width_col3'] = array(
        '#type' => 'textfield',
        '#title' => t('Content'),
        '#default_value' => $variables['yaml_layout_page_width_col3'],
        '#attributes' => array(
          'class' => 'disabled',
          'readonly' => 'readonly',
        ),
        '#size' => '10',
        '#suffix' => '<hr />'
      );
      break;

    case '31':
      $form['layout']['yaml_layout_page_width_col1'] = array(
        '#type' => 'textfield',
        '#title' => t('Right sidebar'),
        '#default_value' => $variables['yaml_layout_page_width_col1'],
        '#description' => t('Defines the right column width in <em>px</em>, <em>em</em> or <em>%</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_col1'])),
        '#required' => TRUE,
        '#size' => '10'
      );
      $form['layout']['yaml_layout_page_width_col3'] = array(
        '#type' => 'textfield',
        '#title' => t('Content'),
        '#default_value' => $variables['yaml_layout_page_width_col3'],
        '#description' => t('Defines the left column width in <em>px</em>, <em>em</em> or <em>%</em>. Default: "@default".', array('@default' => $defaults['yaml_layout_page_width_col3'])),
        '#attributes' => array(
          'class' => 'disabled',
          'readonly' => 'readonly',
        ),
        '#size' => '10',
        '#suffix' => '<hr />'
      );
      break;
  }

  $form['layout']['yaml_layout_page_gfxborder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Graphic layout borders'),
    '#default_value' => $variables['yaml_layout_page_gfxborder'],
    '#description' => t('Activates graphic borders around the page layout.'),
  );

  $form['navigation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation'),
    '#collapsible' => true,
    '#collapsed' => false,
  );
  $form['navigation']['yaml_nav_primary'] = array(
    '#type' => 'select',
    '#title' => t('Menu containing primary links'),
    '#default_value' => $variables['yaml_nav_primary'],
    '#options' => array(
      '0' => 'nav_slidingdoor.css',
      '1' => 'nav_shinybuttons.css',
    ),
  );
  $form['navigation']['yaml_nav_vertical'] = array(
    '#type' => 'select',
    '#title' => t('Menu containing navigation links'),
    '#default_value' => $variables['yaml_nav_vertical'],
    '#options' => array(
      '0' => 'nav_vlist.css',
    ),
  );

  // Some Internet Explorer Specials
  $form['msie'] = array(
    '#type' => 'fieldset',
    '#title' => t('Internet Explorer Special'),
    '#collapsible' => true,
    '#collapsed' => false,
  );
  $form['msie']['yaml_msie_hack_pngfix'] = array(
    '#type' => 'checkbox',
    '#title' => t('PNG transparency'),
    '#default_value' => $variables['yaml_msie_hack_pngfix'],
    '#description' => t('Activates PNG transparency fix for filenames ending with "_trans.png" or images with CSS class "_trans" specified.'),
  );
  $form['msie']['yaml_msie_hack_minmaxwidth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Simulate min-width / max-width'),
    '#default_value' => $variables['yaml_msie_hack_minmaxwidth'],
    '#description' => t('Simulate min-width / max-width for Internet Explorer by using JS-Expressions.'),
  );
  
  // Add miscellaneous settings
  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Miscellaneous'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  /*
  $form['misc']['yaml_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug mode'),
    '#default_value' => $variables['yaml_debug'],
    '#description' => t("Activates YAML debug mode. Don't use this setting in production mode."),
    '#suffix' => '<hr />',
  ); */

  $form['misc']['yaml_display_link_validation_xhtml'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display W3C XHTML validation link'),
    '#default_value' => $variables['yaml_display_link_validation_xhtml'],
    '#description' => t('Shows a W3C XHTML validation link in the footer of every page.'),
  );
  $form['misc']['yaml_display_link_validation_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display W3C CSS validation link'),
    '#default_value' => $variables['yaml_display_link_validation_css'],
    '#description' => t('Shows a W3C CSS validation link in the footer of every page.'),
    '#suffix' => '<hr />',
  );

  $form['misc']['yaml_display_link_license_yaml'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display YAML Framework link'),
    '#default_value' => $variables['yaml_display_link_license_yaml'],
    '#description' => t('This back linking maybe only removed, if you possess a YAML Framework license.'),
    '#prefix' => '<p>'. t('<strong>License and terms of use:</strong><br />The YAML Framework and YAML for Drupal are licensed under a <a href="@lic_cc">Creative Commons</a> license. For more information see the following licenses and terms of use.</p><p>YAML Framework - <a href="@lic_yaml">@lic_yaml</a><br />YAML for Drupal - <a href="@lic_yamlfd">@lic_yamlfd</a>', array('@lic_cc' => t('http://creativecommons.org/licenses/by-nc-sa/2.0/'), '@lic_yaml' => t('http://www.yaml.de/en/license/license-conditions.html'), '@lic_yamlfd' => t('http://www.yaml-fuer-drupal.de/en/terms-of-use'))) .'</p>',
  );
  $form['misc']['yaml_display_link_license_yamlfd'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display YAML for Drupal link'),
    '#default_value' => $variables['yaml_display_link_license_yamlfd'],
    '#description' => t('This back linking maybe only removed, if you have possess a YAML for Drupal license.'),
  );

  // Return the form.
  return $form;
}
