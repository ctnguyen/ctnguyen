<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/html_header.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php';
?>
<html>
<head>
<?php 
$rstate = new GeneralRequestState('en','home',false);
if (!empty($_GET['fcontent']))
{
$rstate->resetContent($_GET['fcontent']);
}
if (isset($_GET['fismobile']))
{
$rstate->resetIsMobil(TRUE);
}

$headertool = new HtmlHeader($rstate);
echo $headertool->htmlcontent;
?>
</head>
<body>
<?php
$rstate = new GeneralRequestState('en','home',false);
if (!empty($_GET['flang']))
{
	$rstate->resetContent($_GET['flang']);
}
if (!empty($_GET['fcontent']))
{
	$rstate->resetContent($_GET['fcontent']);
}
if (isset($_GET['fismobile']))
{
	$rstate->resetIsMobil(TRUE);
}

echo '	<div id="whole-page">'.PHP_EOL;


$htmlNavigator = ModelHelper::getHtmlNavigator($rstate);
echo $htmlNavigator;

$maincontent = ModelHelper::getHtmlMainContent($rstate);
echo $maincontent;

// Print out footer
$footercontent = ModelHelper::getHtmlFooter($rstate->_lang_state);
echo $footercontent;

echo '	</div>'.PHP_EOL;
?>
</body>
</html>
