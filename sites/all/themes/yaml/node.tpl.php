<?php
// $Id: node.tpl.php,v 3.1.0.12 2009/06/07 00:00:00 hass Exp $
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
  <div class="clearfix">
    <?php if ($page == 0): ?>
      <h3><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h3>
    <?php endif; ?>
    <?php print $picture ?>
    <?php if ($terms || $submitted): ?>
      <div class="meta">
      <?php if ($submitted): ?>
        <span class="submitted"><?php print $submitted ?></span>
      <?php endif; ?>
      <?php if ($terms): ?>
        <div class="terms"><?php print $terms ?></div>
      <?php endif;?>
      </div>
    <?php endif; ?>
    <div class="content"><?php print $content ?></div>
  </div>
  <?php if ($links) { print $links; } ?>
</div>
