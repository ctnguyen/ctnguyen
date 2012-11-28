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

$totalhtmldoc = '';
////	HTML	HTML	HTML	HTML	HTML	HTML	HTML	HTML	/////
$doctype = ModelHelper::getDocType($_general_request);
$totalhtmldoc .= $doctype;

if(!$_general_request->_isMobile)
{
	$totalhtmldoc .= '<head>'.PHP_EOL;
	$headertool = new HtmlHeader($_general_request);
	$totalhtmldoc .= $headertool->htmlcontent;
	$totalhtmldoc .= '</head>'.PHP_EOL;
	$totalhtmldoc .= '<body>'.PHP_EOL;

	$totalhtmldoc .= '	<div id="page-wrapper">'.PHP_EOL;
	$headercontent = ModelHelper::getHtmlTopWrapper($_general_request,2);
	$totalhtmldoc .= $headercontent;
	$totalhtmldoc .= '		<div id="whole-page">'.PHP_EOL;


	$htmlTopPage = ModelHelper::getHtmlTopPage($_general_request,3);
	$totalhtmldoc .= $htmlTopPage;

	$htmlNavigator = ModelHelper::getHtmlNavigator($_general_request,3);
	$totalhtmldoc .= $htmlNavigator;
	$maincontent = ModelHelper::getHtmlMainContent($_general_request,3);
	$totalhtmldoc .= $maincontent;


	$htmlBottomPage = ModelHelper::getHtmlBottomPage($_general_request,3);
	$totalhtmldoc .= $htmlBottomPage;


	$footercontent = ModelHelper::getHtmlFooter($_general_request,2);

	$totalhtmldoc .= '		</div>'.PHP_EOL; //end if of <div id="whole-page">
	$totalhtmldoc .= $footercontent;

	$totalhtmldoc .= '	</div>'.PHP_EOL;//end div of  <div id="page-wrapper">

	$totalhtmldoc .= '</body>'.PHP_EOL;
}
/* separate for mobile, is totally different senarios
 * page for mobile is printing in the multi-template pages
*  TODO first implementatin print all pages, but its not good
*  the idea is to print only the default page and load successively other
*  by ajax loading
*/
if($_general_request->_isMobile)
{
	$totalhtmldoc .= '<head>'.PHP_EOL;
	$headertool = new HtmlHeader($_general_request);
	$totalhtmldoc .= $headertool->htmlcontent;
	$totalhtmldoc .= '</head>'.PHP_EOL;
	$totalhtmldoc .= '<body>'.PHP_EOL;

	$htmlTopPage = ModelHelper::getHtmlTopPage($_general_request,1);
	$totalhtmldoc .= $htmlTopPage;

	$default_content_request = $_general_request->_content_state;


	//print the default page at first place
	$totalhtmldoc .= '	<div id="'.$_general_request->_content_state.'" data-role="page" data-url="'.$_general_request->_content_state.'">'.PHP_EOL;
	$htmlNavigator = ModelHelper::getHtmlNavigator($_general_request,2);
	$totalhtmldoc .= $htmlNavigator;
	$maincontent = ModelHelper::getHtmlMainContent($_general_request,2);
	$totalhtmldoc .= $maincontent;
	$footercontent = ModelHelper::getHtmlFooter($_general_request,2);
	$totalhtmldoc .= $footercontent;
	$totalhtmldoc .= '	</div>'.PHP_EOL;


	//loop printint all other mobile prefetch pages
	$datafilename = ControllerHelper::getDataNavigatorListFile();
	$xmlDoc = new DOMDocument;
	$xmlDoc->load($datafilename);
	$langnode   = $xmlDoc->getElementsByTagName($_general_request->_lang_state)->item(0);
	$buttonlist = $langnode->getElementsByTagName("navigatebutton");
	foreach($buttonlist as $button)
	{
		$buttonID = $button->getElementsByTagName("idNAME")->item(0);
		if($buttonID)
		{
			if($buttonID->nodeValue != $default_content_request)
			{
				$_general_request->resetContent($buttonID->nodeValue);

				$totalhtmldoc .= '	<div id="'.$_general_request->_content_state.'" data-role="page" data-url="'.$_general_request->_content_state.'">'.PHP_EOL;
				
				$htmlNavigator = ModelHelper::getHtmlNavigator($_general_request,2);
				$totalhtmldoc .= $htmlNavigator;
				
				$maincontent = ModelHelper::getHtmlMainContent($_general_request,2);
				$totalhtmldoc .= $maincontent;
				
				$footercontent = ModelHelper::getHtmlFooter($_general_request,2);
				$totalhtmldoc .= $footercontent;
				
				$totalhtmldoc .= '	</div>'.PHP_EOL;
			}
		}

	}
	//reset the content request to the default one
	$_general_request->resetContent($default_content_request);

	$htmlTopPage = ModelHelper::getHtmlBottomPage($_general_request,1);
	$totalhtmldoc .= $htmlTopPage;

	$totalhtmldoc .= '</body>'.PHP_EOL;

}

//	HTML	HTML	HTML	HTML	HTML	HTML	HTML	HTML	/////
echo $totalhtmldoc;
?>