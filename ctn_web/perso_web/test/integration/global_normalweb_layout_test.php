<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
?>
<html>
<head>
<title>General Request init</title>
</head>
<body>
	<h1>TEST GENERAL INIT REQUEST</h1>
	<form method="get" target="_blank" action="<?php echo GlobalConfig::DOMAINE_NAME.'index.php';?>">
		<p>
			lang: <input type="text" name='lang' />
		</p>
		<p>
			content: <input type="text" name='content' />
		</p>
		<p>
			isMobile: <input type="text" name='isMobile' />
		</p>
		<p>
			<input type="submit" value="initRequest">
		</p>
	</form>
</body>
</html>
