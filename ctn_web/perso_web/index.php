<?php

require_once realpath( dirname(__FILE__ ) . '/global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/HtmlHeader.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ModelHelper.php';


GlobalConfig::init_cookie_lang(5);//TODO set to big number

$isMobile = false;
if ($_GET['isMobile'] ==='true' ){
	$isMobile = true;
}
if (GlobalConfig::isMobile()){
	$isMobile = true;
}

$good_request = true;

// Default page request is in English and home page
$_general_request = new GeneralRequestState('en', 'home', $isMobile);

if (!empty($_GET['lang']))
{
	$_general_request->resetLang($_GET['lang']);
}

if (!empty($_GET['content']))
{
	$_general_request->resetContent($_GET['content']);
}

if( !ControllerHelper::isGoodRequest($_general_request) )
{
	$good_request = false;
}

// If request is bad, reset the request to the default one
//if(!$good_request){$_general_request->resetLang('en'); $_general_request->resetContent('home');}


$doctype = ModelHelper::getDocType($_general_request);
echo $doctype;


echo '<head>'.PHP_EOL;
$headertool = new HtmlHeader($_general_request);
echo $headertool->htmlcontent;
echo '</head>'.PHP_EOL;
echo '<body>'.PHP_EOL;

if(!$_general_request->_isMobile)
{
	echo '	<div id="page-wrapper">'.PHP_EOL;
	$headercontent = ModelHelper::getHtmlHeader($_general_request,2);
	echo $headercontent;
}
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


echo '		</div>'.PHP_EOL; //end if of <div id="whole-page">
$footercontent = ModelHelper::getHtmlFooter($_general_request,2);
echo $footercontent;


if(!$_general_request->_isMobile)
{
	echo '	</div>'.PHP_EOL;//end div of  <div id="page-wrapper">
}

echo '		<script type="text/javascript">'.PHP_EOL ;
if(!$_general_request->_isMobile)
{
echo '		set_global_normal_layout();'.PHP_EOL ;
}
else
{
	echo '			set_global_mobile_layout();'.PHP_EOL ;
}
echo '		$("img.langbutton").click(function() {'.PHP_EOL ;
echo '		update_langue($(this).attr("id"));'.PHP_EOL ;
echo '		'.PHP_EOL ;
echo '		});'.PHP_EOL ;
echo '		$("a.navigatebutton").click(function() {'.PHP_EOL ;
echo '		update_maincontent($(this).attr("id"));'.PHP_EOL ;
echo '		});'.PHP_EOL ;
echo '		</script>'.PHP_EOL ;

echo '</body>'.PHP_EOL;


?>