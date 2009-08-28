<?php
// $Id: links-secondary.tpl.php,v 3.1.0.12 2009/06/07 00:00:00 hass Exp $

/**
 * This snippet changes seconday links layout.
 */
$output = '';

if (count($links) > 0) {
  // Add custom classes for theming.
  $output .= '<span'. drupal_attributes($attributes) .'>';

  // Display the right cap of the 'button bar'.
  if (!empty($settings['leftcab'])) {
    $output .= $settings['leftcab'];
  }

  // Build the list of themed links.
  $link_list = array();
  foreach ($links as $link) {
    if (isset($link['href'])) {
      // Pass in $link as $options, they share the same keys.
      $link_list[] = l($link['title'], $link['href'], $link);
    }
    else if (!empty($link['title'])) {
      // Some links are actually not links, but we wrap these in <span> for adding title and class attributes
      if (empty($link['html'])) {
        $link['title'] = check_plain($link['title']);
      }
      $span_attributes = '';
      if (isset($link['attributes'])) {
        $span_attributes = drupal_attributes($link['attributes']);
      }
      $link_list[] = '<span'. $span_attributes .'>'. $link['title'] .'</span>';
    }
  }

  // Add delimiter between the links.
  if (!empty($settings['delimiter'])) {
    $output .= implode($settings['delimiter'], $link_list);
  }
  else {
    $output .= implode('', $link_list);
  }

  // Display the right cap of the 'button bar'.
  if (!empty($settings['rightcab'])) {
    $output .= $settings['rightcab'];
  }

  $output .= '</span>';
}

print $output;
?>