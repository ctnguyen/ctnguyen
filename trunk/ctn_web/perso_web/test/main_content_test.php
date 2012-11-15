<?php 
	include '../global-config.php';
	include '../controller/general_request_state.php';
	include '../model/main_content.php';
?>

<html>
<head>
<title>Main Content Test</title>
</head>
<body>
	<h1>TEST FOR MAIN CONTENT REQUEST</h1>
	<form method='get' action='<?php echo $_SERVER['PHP_SELF'];?>'>
		<p>
			lang: <input type="text" name='flang'/>
		</p>
		<p>
			content: <input type="text" name='fcontent'/>
		</p>
		<p>
			<input type="submit" value="RequestContent">
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
	
	$rcontent = new MainContent($rstate);
	
	echo '<div id="content">'. $rcontent->htmlcontent .'</div>';
	?>
	</form>
	<hr/>
	<h1>Main Content in the div content, type ctr+u to see sources</h1>
</body>
</html>
