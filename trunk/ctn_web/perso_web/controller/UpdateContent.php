<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ModelHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/ViewHelper.php';

/* \script UpdateContent
 *
* Giving a GeneralReauestState, UpdateContent controller give the html with feature as
*
*<head>
*	<script class="specificstyle" src="absolute_path_to_the_CONTENTLABEL.JS"></script>
*	[optional] <script class="specificstyle" src="other script found in NavitatorList.xml, tag specificheader"></script>
*</head>
*<body>
*			<div id="maincontent">
*				<content loaded here by using model MainContent>
* 			</div>
*</body>
*/

$isMobile = false;

if ($_GET['ismobile'] == 'true'){
	$isMobile = true;
}
if (ControllerHelper::isMobile()){
	$isMobile = true;
}

$good_request = true;
$_general_request = new GeneralRequestState('', '', $isMobile);

if (!empty($_GET['lang']))
{
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

$htmlResult = '';

if( !ControllerHelper::isGoodRequest($_general_request) )
{
	$good_request = false;
}


$htmlResult .= '<head>'.PHP_EOL;
$htmlResult .= ViewHelper::getSpecificStyleSetting($_general_request);
$htmlResult .= '</head>'.PHP_EOL;
$htmlResult .= '<body>'.PHP_EOL;
if($good_request)
{
	$htmlResult .= ModelHelper::getHtmlMainContent($_general_request,3);
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