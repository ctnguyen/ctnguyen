<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ContentNavigator.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/LangNavigator.php';

/* \script ContentNavigatorRequest
 *
* Giving a GeneralReauestState, UpdateLang controller give the html with feature as
* [no header tag in the given page]
*<body>
*
*			<div id="contentnavigator">
*				<THIS SCRIPT GIVE THE CONTENT HERE>
* 			</div>
*</body>
*/


$_isMobile = false;

if ($_GET['isMobile'] ==='true' ){
	$_isMobile = true;
}
if (ControllerHelper::isMobile()){
	$_isMobile = true;
}

$good_request = true;
$_general_request = new GeneralRequestState('en', 'home', $_isMobile);

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

$content_part = new ContentNavigator($_general_request,4);

$htmlResult .= $content_part->htmlcontent;

echo $htmlResult;




?>