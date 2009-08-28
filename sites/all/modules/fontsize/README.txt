This package contains a Fontsizer Module for Drupal 6.x.

All code is licensed under GPL except the EfA Fontsizer JavaScript code.

EfA original files:
******************************************************************************
So what is EfA? EfA is a abbreviation of "Einfach für Alle" in German. If you need 
more info check out the Website http://www.einfach-fuer-alle.de/artikel/fontsize/.

For the original and commented version of the main javascript file
see the file "js/efa_fontsize_org.js".

The "js/efa_fontsize.js" file has been altered to be smaller and extended
with a max/min resize limit feature. Additional the dynamic config part
is moved outside into an inline snippet produced by the drupal module.


Drupal Install and Setup:
******************************************************************************

1. Copy the fontsizer directory into your modules directory
2. Activate it under Administer > Site building > Modules
3. Configure permissions under Administer > Logs > Access control
4. Setup your fontsizer configuration Administer > Settings > Fontsizer

For more details http://www.yaml-fuer-drupal.de/de/tutorials/modul-fontsize.


Icons:
******************************************************************************

All icons are configurable. Simply place your icons into "sites/all/modules/fontsize/img"
and change the filenames in Administer > Settings > Font Size.

1. Iconcollection "Perfect Icons" (GPL), http://www.ebenlechner.at/de/perfect-icons.html,
   Gernot Ebenlechner released this icons and they are included per default in this
   package.

2. Mark James released many popular and beautiful icons at http://www.famfamfam.com/.
   This icons are released under a Creative Commons License and requires a backlink.
