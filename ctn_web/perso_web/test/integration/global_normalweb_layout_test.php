<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/html_header.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php';

$doctype = ModelHelper::getDocType();
echo $doctype.PHP_EOL;
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

echo '	<div id="page-wrapper">'.PHP_EOL;

$headercontent = ModelHelper::getHtmlHeader();
echo $headercontent;

echo '		<div id="whole-page">'.PHP_EOL;
echo '			<div id="top-page">'.PHP_EOL;
echo '				<div class="referencing"><h1>NGUYEN Chi Thanh, INRIA, SOFA, Digiplante, Paris VI, Paris 6</h1></div>'.PHP_EOL;
echo '				<div id="actuallangue" style="display:none;">fr</div>'.PHP_EOL;
echo '				<div id="actuallnavication" style="display:none;">home</div>'.PHP_EOL;
echo '			</div>'.PHP_EOL;

$htmlNavigator = ModelHelper::getHtmlNavigator($rstate);
echo $htmlNavigator;

$maincontent = ModelHelper::getHtmlMainContent($rstate);
echo $maincontent;

echo '			<div id="bottom-page">'.PHP_EOL;
echo '				<div class="referencing"><h1>NGUYEN Chi Thanh, INRIA, SOFA, Digiplante, Paris VI, Paris 6</h1></div>'.PHP_EOL;
echo '			</div>'.PHP_EOL;


echo '		</div>'.PHP_EOL;
$footercontent = ModelHelper::getHtmlFooter($rstate->_lang_state);
echo $footercontent;
echo '	</div>'.PHP_EOL;

echo '	<script type="text/javascript">'.PHP_EOL          ;
//echo '		$(".referencing").remove();'.PHP_EOL.PHP_EOL          ;

echo '		$("img.langbutton").click(function() {'.PHP_EOL     ;
echo '			reset_actuallang($(this).attr("id"));'.PHP_EOL  ;
echo '			reload_allpage($(this).attr("id"));'.PHP_EOL ;
echo '		});'.PHP_EOL                                  ;

echo '		$("a.navigatebutton").click(function() {'.PHP_EOL     ;
echo '			reset_actualnaviation(attr("id"));'.PHP_EOL  ;
echo '			reload_maincontent($(this).attr("id"));'.PHP_EOL ;
echo '		});'.PHP_EOL                                  ;

echo '	</script>'.PHP_EOL                                ;

?>
</body>
</html>
