<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/helper.php';
?>

<html>
<head>
<title>Main Content Test</title>
</head>
<body>
	<h1>TEST FOR HTML CONTROLLER LIST CONTENT</h1>
	<h1>type ctr+u to see sources</h1>
	<hr />
	<?php 

	$time_start = microtime(true);

	$request = new GeneralRequestState('en','home',true);
	
	/*
	$request = new GeneralRequestState('fr','home',true);
	$request = new GeneralRequestState('en','home',true);
	*/
		
	$htmlNavigator = ModelHelper::getHtmlNavigator($request );
	echo $htmlNavigator;
	
	$time_end = microtime(true);
	$elapsed_time = ($time_end - $time_start);
	echo '	<hr/>'.PHP_EOL;
	echo '<div><b>Total Execution Time: '.$elapsed_time.' seconds</b></div>'.PHP_EOL;
	?>
</body>
</html>
