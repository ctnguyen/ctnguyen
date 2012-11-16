<?php 
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php'; 

$footer_en = ModelHelper::getHtmlFooter('fr');
echo $footer_en;

$footer_fr = ModelHelper::getHtmlFooter('fr');
echo $footer_fr;

$footer_vn = ModelHelper::getHtmlFooter('vn');
echo $footer_vn;

?>