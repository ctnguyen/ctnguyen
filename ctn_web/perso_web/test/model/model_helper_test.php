<?php 
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php'; 

$request = new GeneralRequestState('en','home',false);

$footer_en = ModelHelper::getHtmlFooter($request);
echo $footer_en;

$request->resetLang('fr');
$footer_fr = ModelHelper::getHtmlFooter($request);
echo $footer_fr;

$request->resetLang('vn');
$footer_vn = ModelHelper::getHtmlFooter($request);
echo $footer_vn;

?>