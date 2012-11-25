<?php 
	require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
	require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
	require_once GlobalConfig::SERVER_ROOT_DIR.'model/MainContent.php';
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
	</form>
	<h1>Main Content in the div content, type ctr+u to see sources</h1>
	<hr/>
	<?php 
	$time_start = microtime(true);
	
	$rstate = new GeneralRequestState('','',false);
	if (!empty($_GET['flang']))
	{
		$rstate->resetLang($_GET['flang']);
	}
	if (!empty($_GET['fcontent']))
	{
		$rstate->resetContent($_GET['fcontent']);
	}
	if (isset($_GET['fisMobile']))
	{
		$rstate->resetIsMobil(TRUE);
	}
	else
	{
		$rstate->resetIsMobil(FALSE);
	}
	
	$rcontent = new MainContent($rstate);
	
	echo '	<div id="maincontent">'.PHP_EOL;
	echo 		$rcontent->htmlcontent;
	echo '	</div>'.PHP_EOL;
	
	$time_end = microtime(true);
	$elapsed_time = ($time_end - $time_start);
	echo '<hr/>'.PHP_EOL;
	echo '<div><b>Total Execution Time: '.$elapsed_time.' seconds</b></div>';
	?>
	</body>
</html>
