<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ContentNavigator.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/LangNavigator.php';

/* \script NavigatorRequest
 *
* Giving a GeneralReauestState, UpdateLang controller give the html with feature as
* [no header tag in the given page]
*<body>
*			<div id="navigator">
*				<THIS SCRIPT GIVE THE CONTENT HERE>
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
$_general_request = new GeneralRequestState('en', 'home', $isMobile);

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

$flag_part = new LangNavigator($_general_request,4);
$content_part = new ContentNavigator($_general_request,4);

$htmlResult .= $flag_part ->htmlcontent;
$htmlResult .= $content_part->htmlcontent;

echo $htmlResult;




?>