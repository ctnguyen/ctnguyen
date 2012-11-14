<?php 
	include '../controller/request_state.php';
	include '../global-config.php';
?>

<html>
<head>
<title>Personal INFO</title>
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
			<input type="submit" value="BuildRequestState">
		</p>
		<?php 
		$rstate = new RequestState('','');
		if (!empty($_GET['flang']))
		{
			$rstate->resetLang($_GET['flang']);
		}
		if (!empty($_GET['fcontent']))
		{
			$rstate->resetContent($_GET['fcontent']);
		}
		echo '<h1>lang state=[' . $rstate->_lang_state .']</h1>  <h1>content state=['. $rstate->_content_state .']</h1>';
		?>
	</form>
</body>
</html>
