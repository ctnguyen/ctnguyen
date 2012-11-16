<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ContentNavigator.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/LangNavigator.php';

$time_start = microtime(true);

$html_flag = new LangNavigator();

$html_en = new ContentNavigator('en');
echo $html_flag->htmlcontent;
echo $html_en->htmlcontent;
/*
$html_fr = new ContentNavigator('fr');
echo $html_flag->htmlcontent;
echo $html_fr->htmlcontent;

$html_vn = new ContentNavigator('vn');
echo $html_flag->htmlcontent;
echo $html_vn->htmlcontent;
*/
$time_end = microtime(true);
$elapsed_time = ($time_end - $time_start);
echo '<div><b>Total Execution Time: '.$elapsed_time.' seconds</b></div>';
?>