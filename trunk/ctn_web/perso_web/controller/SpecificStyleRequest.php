<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/ViewHelper.php';


/* \script SpecificStyleRequest
 *
* Giving a GeneralReauestState, UpdateLang controller give the html with feature as
* [no header tag in the given page]
*<head>
*
*
*
*
*	<script class="specificstyle" src="[DOMAINE_NAME]/view/style/[mobi]_[content].js"></script>
*</head>
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

$htmlResult .= ViewHelper::getSpecificStyleSetting($_general_request);

echo $htmlResult;

?>