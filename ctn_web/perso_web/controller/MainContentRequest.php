<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/MainContent.php';

/* \script MainContentRequest
 *
* Giving a GeneralReauestState, UpdateContent controller give the html with feature as
*
*<head>
*	<script class="specificstyle" src="absolute_path_to_the_CONTENTLABEL.JS"></script>
*	[optional] <script class="specificstyle" src="other script found in NavitatorList.xml, tag specificheader"></script>
*</head>
*<body>
*			<div id="maincontent">
*				<THIS SCRIPT GIVE THE CONTENT HERE>
* 			</div>
*</body>
*/

$_isMobile = false;

if ($_GET['isMobile'] == 'true'){
	$_isMobile = true;
}
if (ControllerHelper::isMobile()){
	$_isMobile = true;
}

$good_request = true;
$_general_request = new GeneralRequestState('', '', $_isMobile);

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


if( !ControllerHelper::isGoodRequest($_general_request) )
{
	$good_request = false;
}



$htmlResult = '';

$maincontent_part = new MainContent($_general_request,4);

if($good_request)
{
	$htmlResult .= $maincontent_part->htmlcontent;
}
else
{
	$htmlResult .= '<h1>Failed Request for : content['.$_general_request->_content_state.'] ,lang['.$_general_request->_lang_state.']</h1>'.PHP_EOL;
}

echo $htmlResult;




?>