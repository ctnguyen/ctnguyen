<?php 
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php'; 

$footer_en = ModelHelper::getFooter('fr');
echo $footer_en.PHP_EOL;

$footer_fr = ModelHelper::getFooter('fr');
echo $footer_fr.PHP_EOL;

$footer_vn = ModelHelper::getFooter('vn');
echo $footer_vn.PHP_EOL;

?>