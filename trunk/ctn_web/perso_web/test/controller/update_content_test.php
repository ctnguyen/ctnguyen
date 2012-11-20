<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/UpdateContent.php';
?>

<html>
<head>
<title>Update Content Test</title>
</head>
<body>
	<h1>TEST REQUEST CONTROLLER UPDATE CONTENT</h1>
	<form method="get" target="_blank" action="<?php echo GlobalConfig::DOMAINE_NAME.'controller/UpdateContent.php';?>">
		<p>
			lang: <input type="text" name='lang'/>
		</p>
		<p>
			content: <input type="text" name='content'/>
		</p>
		<p>
		<input type="checkbox" name='ismobile'>isMobile<br>
		</p>
		<p>
			<input type="submit" value="getUpdateContent">
		</p>
	</form>
</body>
</html>
