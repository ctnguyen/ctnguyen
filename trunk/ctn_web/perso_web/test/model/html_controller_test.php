<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'model/ContentNavigator.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'model/LangNavigator.php';
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

	$html_flag = new LangNavigator();

	$html_en = new ContentNavigator('en');
	echo $html_flag->htmlcontent;
	echo $html_en->htmlcontent;
	/*
	 $html_fr = new ContentNavigator('fr');
	echo $html_flag->htmlcontent;
	echo $html_fr->htmlcontent;

	$html_vn = new ContentNavigator('vn');
	echo $html_flag->htmlcontent;
	echo $html_vn->htmlcontent;
	*/
	$time_end = microtime(true);
	$elapsed_time = ($time_end - $time_start);
	echo '	<hr/>'.PHP_EOL;
	echo '<div><b>Total Execution Time: '.$elapsed_time.' seconds</b></div>'.PHP_EOL;
	?>
</body>
</html>
