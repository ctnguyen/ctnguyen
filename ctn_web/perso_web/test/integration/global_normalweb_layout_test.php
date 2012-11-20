<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/html_header.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php';

$temporequest = new GeneralRequestState('en','home',false);
$doctype = ModelHelper::getDocType( $temporequest );
echo $doctype;

?>
<html>
<head>
<?php 
$_general_request = new GeneralRequestState('en','home',false);
if (!empty($_GET['fcontent']))
{
$_general_request->resetContent($_GET['fcontent']);
}
if (isset($_GET['fismobile']))
{
$_general_request->resetIsMobil(TRUE);
}

$headertool = new HtmlHeader($_general_request);
echo $headertool->htmlcontent;
?>
</head>
<body>
<?php
$_general_request = new GeneralRequestState('en','home',false);
if (!empty($_GET['flang']))
{
	$_general_request->resetContent($_GET['flang']);
}
if (!empty($_GET['fcontent']))
{
	$_general_request->resetContent($_GET['fcontent']);
}
if (isset($_GET['fismobile']))
{
	$_general_request->resetIsMobil(TRUE);
}

echo '	<div id="page-wrapper">'.PHP_EOL;

$headercontent = ModelHelper::getHtmlHeader($_general_request,2);
echo $headercontent;

echo '		<div id="whole-page">'.PHP_EOL;
echo '			<div id="top-page">'.PHP_EOL;
echo '				<div class="referencing"><h1>NGUYEN Chi Thanh, INRIA, SOFA, Digiplante, Paris VI, Paris 6</h1></div>'.PHP_EOL;
echo '				<div id="actuallangue" style="display:none;">fr</div>'.PHP_EOL;
echo '				<div id="actualcontent" style="display:none;">home</div>'.PHP_EOL;
echo '			</div>'.PHP_EOL;


$htmlNavigator = ModelHelper::getHtmlNavigator($_general_request,3);
echo $htmlNavigator;
$maincontent = ModelHelper::getHtmlMainContent($_general_request,3);
echo $maincontent;


echo '			<div id="bottom-page">'.PHP_EOL;
echo '				<div class="referencing"><h1>NGUYEN Chi Thanh, INRIA, SOFA, Digiplante, Paris VI, Paris 6</h1></div>'.PHP_EOL;
echo '			</div>'.PHP_EOL;


echo '		</div>'.PHP_EOL;
$footercontent = ModelHelper::getHtmlFooter($_general_request,2);
echo $footercontent;
echo '	</div>'.PHP_EOL;


echo '		<script type="text/javascript">'.PHP_EOL ;
echo '		$("img.langbutton").click(function() {'.PHP_EOL ;
echo '		update_langue($(this).attr("id"));'.PHP_EOL ;
echo '		'.PHP_EOL ;
echo '		});'.PHP_EOL ;
echo '		$("a.navigatebutton").click(function() {'.PHP_EOL ;
echo '		update_maincontent($(this).attr("id"));'.PHP_EOL ;
echo '		});'.PHP_EOL ;
echo '		</script>'.PHP_EOL ;

?>
</body>
</html>
