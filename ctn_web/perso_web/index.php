<?php

require_once realpath( dirname(__FILE__ ) . '/global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/HtmlHeader.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ModelHelper.php';


// DEFAUTL REQUEST IS SETTING HERE WHEN VISITE index.php without GET[]
$default_lang = 'en';
$default_content = 'home';


GlobalConfig::init_cookie_lang(5);//TODO set to big number

$isMobile = false;
if ($_GET['isMobile'] ==='true' ){
	$isMobile = true;
}
if (ControllerHelper::isMobile()){
	$isMobile = true;
}

$good_request = true;


$_general_request = new GeneralRequestState($default_lang, $default_content, $isMobile);

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
//if(!$good_request){$_general_request->resetLang($default_lang); $_general_request->resetContent($default_content);}//TODO

////	HTML	HTML	HTML	HTML	HTML	HTML	HTML	HTML	/////   
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
	echo '		<div id="whole-page">'.PHP_EOL;
}
else
{
	echo '		<div id="whole-page" data-role="page">'.PHP_EOL;
}


$htmlTopPage = ModelHelper::getHtmlTopPage($_general_request,3);
echo $htmlTopPage; 

$htmlNavigator = ModelHelper::getHtmlNavigator($_general_request,3);
echo $htmlNavigator;
$maincontent = ModelHelper::getHtmlMainContent($_general_request,3);
echo $maincontent;


$htmlBottomPage = ModelHelper::getHtmlBottomPage($_general_request,3);
echo $htmlBottomPage;


$footercontent = ModelHelper::getHtmlFooter($_general_request,2);

if(!$_general_request->_isMobile)//if not mobile, footer is out of whole-page
{
	echo '		</div>'.PHP_EOL; //end if of <div id="whole-page">
	echo $footercontent;
}
else//if mobile, footer is in whole-page
{
	echo $footercontent;	
	echo '		</div>'.PHP_EOL; //end if of <div id="whole-page">
}

if(!$_general_request->_isMobile)
{
	echo '	</div>'.PHP_EOL;//end div of  <div id="page-wrapper">
}

//when it is a mobile, jquery instead of use document.ready for all initialize, 
//jquery mobile cannot, and have to call the initialize function here
//TODO modify if found the equivalent of document ready on jquery mobile 
if($_general_request->_isMobile)
{
	echo '		<script type="text/javascript">'.PHP_EOL ;
	echo '			initialize_mobile_browser();'.PHP_EOL ;
	echo '		</script>'.PHP_EOL ;
}

echo '</body>'.PHP_EOL;
//	HTML	HTML	HTML	HTML	HTML	HTML	HTML	HTML	/////

?>