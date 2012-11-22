<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ModelHelper.php';

/* \script UpdateLang
 *
* Giving a GeneralReauestState, UpdateLang controller give the html with feature as
* [no header tag in the given page]
*<body>
*			<div id="navigator">
*				<content loaded here by using model MainContent>
* 			</div>
*			<div id="maincontent">
*				<content loaded here by using model MainContent>
* 			</div>
*			<div id="bottom-wrapper">
*				<content loaded here by using model MainContent>
* 			</div>
*</body>
*/


$isMobile = false;

if ($_GET['ismobile'] ==='true' ){
	$isMobile = true;
}
if (ControllerHelper::isMobile()){
	$isMobile = true;
}

$good_request = true;
$_general_request = new GeneralRequestState('', '', $isMobile);

if (!empty($_GET['lang'])){
	$_general_request->resetLang($_GET['lang']);
}
else
{
	$good_request = false;
}

if (!empty($_GET['content']))
{
	$_general_request->resetContent($_GET['content']);
}
else
{
	$good_request = false;
}



if( !ControllerHelper::isGoodRequest($_general_request) )
{
	$good_request = false;
}

$htmlResult = '';
$htmlResult .= '<body>'.PHP_EOL;
if($good_request)
{
	$htmlResult .= ModelHelper::getHtmlNavigator($_general_request,3);
	$htmlResult .= ModelHelper::getHtmlMainContent($_general_request,3);
	$htmlResult .= ModelHelper::getHtmlFooter($_general_request,3);
}
else
{
	$htmlResult .= '			<div id="maincontent">'.PHP_EOL;
	$htmlResult .= '				';
	$htmlResult .= '<h1>Failed Request for : content['.$_general_request->_content_state.'] ,lang['.$_general_request->_lang_state.']</h1>'.PHP_EOL;
	$htmlResult .= '			</div>'.PHP_EOL;
}
$htmlResult .= '</body>'.PHP_EOL;

echo $htmlResult;




?>