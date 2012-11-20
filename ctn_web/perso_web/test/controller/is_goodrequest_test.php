<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';
?>

<html>
<head>
<title>Check Good Request</title>
</head>
<body>
	<h1>CHECK GOOD REQUEST</h1>
	<form method="get" action="<?php echo $_SERVER['PHP_SELF'];?>">
		<p>
			lang: <input type="text" name='lang' />
		</p>
		<p>
			content: <input type="text" name='content' />
		</p>
		<p>
			<input type="submit" value="isGoodRequest">
		</p>
	</form>
	<hr />
	<?php 
	$isMobile = false;
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

	if( !ControllerHelper::isGoodRequest($_general_request) )
	{
		$good_request = false;
	}

	if($good_request)
	{
		echo '<h1>Good Request for : content['.$_general_request->_content_state.'] ,lang['.$_general_request->_lang_state.']</h1>'.PHP_EOL;
	}
	else
	{
		echo '<h1 style="color:red">Error Failed Reaquest for : content['.$_general_request->_content_state.'] ,lang['.$_general_request->_lang_state.']</h1>'.PHP_EOL;
	}

	?>
</body>
</html>
