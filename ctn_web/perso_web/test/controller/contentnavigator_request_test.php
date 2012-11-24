<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
?>

<html>
<head>
<title>Content Navigator Request Test</title>
</head>
<body>
	<h1>TEST REQUEST CONTENT NAVIGATOR (without FLAGS PART)</h1>
	<form method='get'  target="_blank" action="<?php echo GlobalConfig::DOMAINE_NAME.'controller/ContentNavigatorRequest.php';?>">
		<p>
			lang: <input type="text" name='lang'/>
		</p>
		<p>
			content: <input type="text" name='content'/>
		</p>
		<p>
			ismobile: <input type="text" name='ismobile'/> (enter "true" if mobile request)
		</p>
		<p>
			<input type="submit" value="getContentNavigator">
		</p>
	</form>
</body>
</html>
