<?php
// $Id: page.tpl.php,v 3.1.0.12 2009/06/07 00:00:00 hass Exp $
?><?php if (!empty($xml_prolog)) { print $xml_prolog; } ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>
</head>

<body class="<?php print $body_classes; ?>">
<?php if (isset($fontsize_init)) { print $fontsize_init; } ?>

<div class="page_margins">
  <?php print $border_top ?>
  <div class="page">

    <div id="header" class="clearfix">
      <div id="topnav">
        <a class="skip" href="#navigation" title="<?php print t('Skip to the navigation') ?>"><?php print t('Skip to the navigation') ?></a><span class="hideme">.</span>
        <a class="skip" href="#content" title="<?php print t('Skip to the content') ?>"><?php print t('Skip to the content') ?></a><span class="hideme">.</span>
        <?php if (!empty($secondary_links)) { ?><?php print theme('links_secondary', $secondary_links, array('class' => 'links secondary-links')) ?><?php } ?>
      </div>
      <?php print $header ?>
      <?php if ($logo) { ?><a href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><img id="site-logo" class="_trans" src="<?php print $logo ?>" alt="<?php print t('Home') ?>" /></a><?php } ?>
      <?php if ($site_name) { ?><h1 id="site-name"><a href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><?php print $site_name ?></a></h1><?php } ?>
      <?php if ($site_slogan) { ?><div id="site-slogan"><?php print $site_slogan ?></div><?php } ?>
      <?php print $search_box ?>
    </div>

    <!-- begin: main navigation #nav -->
    <div id="nav"> <a id="navigation" name="navigation"></a> <!-- skip anchor: navigation -->
      <?php if (isset($primary_links)) { ?>
      <div class="hlist">
        <?php print theme('links', $primary_links, array('class' => 'primary-links')) ?>
      </div>
      <?php } ?>
    </div>
    <div id="nav-bar" class="clearfix">
      <?php print $breadcrumb ?>
      <?php if (isset($fontsize_links)) { print $fontsize_links; } ?>
    </div>
    <!-- end: main navigation -->

    <!-- begin: main content area #main -->
    <div id="main">

      <?php if ($mission) { ?>
      <!-- #mission: between main navigation and content -->
      <div id="mission" class="clearfix">
        <?php print $mission ?>
      </div>
      <?php } ?>

      <!-- Subtemplate: 2 Spalten mit 66/33 Teilung -->
      <div class="subcolumns">
        <div class="c66l">
          <div class="subc">
            <?php if ($title) { ?><h1 class="title"><?php print $title ?></h1><?php } ?>
            <?php if ($tabs) { ?><div class="tabs"><?php print $tabs ?></div><?php } ?>
            <?php if ($show_messages && $messages): print $messages; endif; ?>
            <?php print $help ?>
            <?php print $content ?>
            <?php print $feed_icons ?>
          </div>
        </div>
        <div class="c33r">
          <div class="subcolumns">
            <div class="c50l">
              <div class="subcr">
                <?php print $left ?>
              </div>
            </div>
            <div class="c50r">
              <div class="subcr">
                <?php print $right ?>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- Subtemplate: 3 Spalten mit 33/33/33 Teilung -->
      <div class="subcolumns">
        <div class="c33l">
          <div class="subcl">
            <?php print $bottom_left ?>
          </div>
        </div>
        <div class="c33l">
          <div class="subc">
            <?php print $bottom_center ?>
          </div>
        </div>
        <div class="c33r">
          <div class="subcr">
            <?php print $bottom_right ?>
          </div>
        </div>
      </div>

    </div>
    <!-- end: #main -->

    <!-- begin: #footer -->
    <div id="footer">
      <!--
      GERMAN:
      Diese Rückverlinkung darf nur entfernt werden,
      wenn Sie eine YAML-Framework und YAML für Drupal Lizenz besitzen.
      :: Lizenzbedingungen: http://www.yaml.de und http://www.yaml-fuer-drupal.de

      ENGLISH:
      This back linking maybe only removed,
      if you possess a YAML Framework and YAML for Drupal license.
      :: License conditions: http://www.yaml.de and http://www.yaml-for-drupal.com
      -->
      <?php print $footer ?>
      <?php print phptemplate_footer($footer_message) ?>
    </div>
    <!-- end: #footer -->

  </div>
  <?php print $border_bottom ?>
</div>
<?php print $closure ?>
</body>
</html>
