<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/html_controller.php';

$time_start = microtime(true);

$html_en = new HtmlController('en');
echo $html_en->htmlcontent;

$html_fr = new HtmlController('fr');
echo $html_fr->htmlcontent;

$html_vn = new HtmlController('vn');
echo $html_vn->htmlcontent;

$time_end = microtime(true);
$elapsed_time = ($time_end - $time_start);
echo '<div><b>Total Execution Time: '.$elapsed_time.' seconds</b></div>';
?>