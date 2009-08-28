<?php
// $Id: fontsize.module, 6.x-1.0 2008/03/01 00:00:00 hass Exp $

/**
 * This module is for Drupal 6.x
 *
 * Author: Alexander Hass
 */

function fontsize_admin_settings_form(&$form_state) {

  $form['fontsize'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global settings'),
    '#collapsible' => true,
    '#collapsed' => false
  );
  $form['fontsize']['fontsize_min'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum font size'),
    '#default_value' => variable_get('fontsize_min', 62),
    '#size' => '5',
    '#field_suffix' => t('%'),
    '#description' => t('Minimum percentage the fontsize can be decreased.'),
    '#required' => true
  );
  $form['fontsize']['fontsize_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum font size'),
    '#default_value' => variable_get('fontsize_max', 142),
    '#size' => '5',
    '#field_suffix' => t('%'),
    '#description' => t('Maximum percentage the fontsize can be increased.'),
    '#required' => true
  );
  $form['fontsize']['fontsize_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Default font size'),
    '#default_value' => variable_get('fontsize_default', 83),
    '#size' => '5',
    '#field_suffix' => t('%'),
    '#description' => t('Recommendation: Round up the CSS value <em>body { font-size: 81.25%; }</em> to the next higher integer (e.g. 83) to circumvent a rounding bug in Opera.'),
    '#required' => true
  );
  $form['fontsize']['fontsize_increment'] = array(
    '#type' => 'textfield',
    '#title' => t('Increases/decreases step'),
    '#default_value' => variable_get('fontsize_increment', 10),
    '#size' => '5',
    '#field_suffix' => t('%'),
    '#description' => t('Percentage by which each click increases/decreases the font size.'),
    '#required' => true
  );

  $fontsizes = array(
    'fontsize_bigger' => t('increase'),
    'fontsize_reset' => t('reset'),
    'fontsize_smaller' => t('decrease')
  );

  // Build the form for detailed settings
  foreach ($fontsizes as $key => $value) {

    $fontsize_properties = variable_get($key, array());

    $form[$key] = array(
      '#type' => 'fieldset',
      '#title' => t('Properties for @name font size link', array('@name' => $value)),
      '#collapsible' => true,
      '#collapsed' => true,
      '#tree' => true
    );
    $form[$key]['beforeHTML'] = array(
      '#type' => 'textfield',
      '#title' => t('HTML to go before link'),
      '#default_value' => $fontsize_properties['beforeHTML'],
      '#description' => t('HTML to go before link')
    );
    $form[$key]['insideHTML'] = array(
      '#type' => 'textfield',
      '#title' => t('HTML to go inside anchor tag'),
      '#default_value' => $fontsize_properties['insideHTML'],
      '#description' => t('HTML to go inside anchor tag')
    );
    $form[$key]['afterHTML'] = array(
      '#type' => 'textfield',
      '#title' => t('HTML to go after link'),
      '#default_value' => $fontsize_properties['afterHTML'],
      '#description' => t('HTML to go after link')
    );
    $form[$key]['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Link title text'),
      '#default_value' => $fontsize_properties['title'],
      '#attributes' => array(
        'class' => 'disabled',
        'readonly' => 'readonly',
      ),
    );
    $form[$key]['id'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of ID field'),
      '#default_value' => $fontsize_properties['id'],
      '#description' => t('Name of ID field')
    );
    $form[$key]['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of NAME field'),
      '#default_value' => $fontsize_properties['name'],
      '#description' => t('Name of NAME field')
    );
    $form[$key]['class'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of CLASS field'),
      '#default_value' => $fontsize_properties['class'],
      '#description' => t('Name of CLASS field')
    );
    $form[$key]['accesskey'] = array(
      '#type' => 'textfield',
      '#title' => t('Accesskey attribute'),
      '#default_value' => $fontsize_properties['accesskey'],
      '#description' => t('Accesskey attribute')
    );
    $form[$key]['onmouseover'] = array(
      '#type' => 'textfield',
      '#title' => t('OnMouseOver JavaScript'),
      '#default_value' => $fontsize_properties['onmouseover'],
      '#description' => t('OnMouseOver JavaScript')
    );
    $form[$key]['onmouseout'] = array(
      '#type' => 'textfield',
      '#title' => t('OnMouseOut JavaScript'),
      '#default_value' => $fontsize_properties['onmouseout'],
      '#description' => t('OnMouseOut JavaScript')
    );
    $form[$key]['onfocus'] = array(
      '#type' => 'textfield',
      '#title' => t('OnFocus JavaScript'),
      '#default_value' => $fontsize_properties['onfocus'],
      '#description' => t('OnFocus JavaScript')
    );

  }

  // Cookie settings
  $cookie_properties = variable_get('fontsize_cookie', array());

  $cookie_default = array(
    'name' => 'fontsize',
    'expires' => 365,
    'path' => '/',
    'domain' => ''
  );

  // Merge the variables and their default values
  $cookie_properties = array_merge($cookie_default, $cookie_properties);

  $form['fontsize_cookie'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cookie settings'),
    '#collapsible' => true,
    '#collapsed' => true,
    '#tree' => true
  );
  $form['fontsize_cookie']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie name'),
    '#default_value' => $cookie_properties['name'],
    '#size' => '20',
    '#description' => t('The name of the fontsize cookie. Defaults to <em>@name</em>.', array('@name' => 'fontsize')),
    '#required' => true
  );
  $form['fontsize_cookie']['expires'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie expires'),
    '#default_value' => $cookie_properties['expires'],
    '#size' => '5',
    '#field_suffix' => t('days'),
    '#description' => t('The cookie lifetime in days. Defaults to <em>365</em> days.'),
    '#required' => true
  );
  $form['fontsize_cookie']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie path'),
    '#default_value' => $cookie_properties['path'],
    '#description' => t('The path the cookie is saved for. If you change default "/" the cookie cannot be read inside other directories.'),
    '#required' => true
  );
  $form['fontsize_cookie']['domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie domain'),
    '#default_value' => $cookie_properties['domain'],
    '#description' => t('If you need a domain cookie, enter "<em>.example.com</em>". A blank string defaults to current domain.'),
    '#required' => false
  );

  return system_settings_form($form);
}

function fontsize_admin_settings_form_validate($form, &$form_state) {

  // Global settings validation
  if ($form_state['values']['fontsize_min'] <= 10 || $form_state['values']['fontsize_min'] > 100) {
    form_set_error('fontsize_min', t('Minimum font size setting should between 10-100.'));
  }
  if ($form_state['values']['fontsize_max'] <= 10 || $form_state['values']['fontsize_max'] > 500) {
    form_set_error('fontsize_max', t('Maximum font size setting should between 10-500.'));
  }
  if ($form_state['values']['fontsize_default'] <= 10 || $form_state['values']['fontsize_default'] > 200) {
    form_set_error('fontsize_default', t('Default font size setting should between 10-200.'));
  }
  if ($form_state['values']['fontsize_increment'] <= 0 || $form_state['values']['fontsize_increment'] > 50) {
    form_set_error('fontsize_increment', t('Increment/decreases steps value setting should between 1-50.'));
  }

  // Cookie validation
  if (!ereg("^[[:alnum:]]*$", $form_state['values']['fontsize_cookie']['name'])) {
    form_set_error('fontsize_cookie][name', t('Only use alphanumeric characters 0-9, A-Z or a-z for cookie name.'));
  }
  if ($form_state['values']['fontsize_cookie']['expires'] <= 0 || $form_state['values']['fontsize_cookie']['expires'] > 1000) {
    form_set_error('fontsize_cookie][expires', t('Set the cookie livetime to 1-1000 days.'));
  }

}
