/**
 * Settings patch for the staging server
 */
$conf = array(
  'cache' => '1',
  'cache_lifetime' => '0',
  'error_level' => '0',
  'preprocess_css' => '1',
  'watchdog_clear' => '1209600',
  'javascript_aggregator_aggregate_js' => '1',
  'javascript_aggregator_optimize_js' => '1',
  'xmlsitemap_engines_submit' => 0,
  'xmlsitemap_engines_cron_submit_frequency' => '-1',
  'nodewords' => array(
    'global' => array(
      'robots' => 'noindex,nofollow'
    )
  ),
);
