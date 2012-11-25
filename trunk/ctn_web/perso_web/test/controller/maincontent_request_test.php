<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
?>

<html>
<head>
<title>Maint Content Request Test</title>
</head>
<body>
	<h1>TEST REQUEST MAIN CONTENT</h1>
	<form method="get" target="_blank" action="<?php echo GlobalConfig::DOMAINE_NAME.'controller/MainContentRequest.php';?>">
		<p>
			lang: <input type="text" name='lang'/>
		</p>
		<p>
			content: <input type="text" name='content'/>
		</p>
		<p>
			isMobile: <input type="text" name='isMobile'/> (enter "true" if mobile request)
		</p>
		<p>
			<input type="submit" value="getMainContent">
		</p>
	</form>
</body>
</html>
