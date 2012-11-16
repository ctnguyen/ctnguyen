<?php 
	require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
	require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
?>

<html>
<head>
<title>General Request State Test</title>
</head>
<body>
	<h1>TEST DYNAMIC CONSTRUCTOR CONTROLER STATES</h1>
	<form method='get' action='<?php echo $_SERVER['PHP_SELF'];?>'>
		<p>
			lang: <input type="text" name='flang'/>
		</p>
		<p>
			content: <input type="text" name='fcontent'/>
		</p>
		<p>
		<input type="checkbox" name='fismobile'>isMobile<br>
		</p>
		<p>
			<input type="submit" value="BuildRequestState">
		</p>
		<?php 
		$rstate = new GeneralRequestState('','',false);
		if (!empty($_GET['flang']))
		{
			$rstate->resetLang($_GET['flang']);
		}
		if (!empty($_GET['fcontent']))
		{
			$rstate->resetContent($_GET['fcontent']);
		}
		if (isset($_GET['fismobile']))
		{
			$rstate->resetIsMobil(TRUE);
		}
		else
		{
			$rstate->resetIsMobil(FALSE);
		}
		echo '<h1>lang state=[' . $rstate->_lang_state .']</h1><h1>content state=['. $rstate->_content_state .']</h1>';
		if($rstate->_isMobile)
		{
			echo '<h1>Is Mobile=[true]';
		}else
		{
			echo '<h1>Is Mobile=[false]';
		}
		?>
	</form>
</body>
</html>
