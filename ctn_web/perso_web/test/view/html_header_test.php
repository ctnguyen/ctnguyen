<?php
require_once realpath( dirname(__FILE__ ) . '/../../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/HtmlHeader.php';
?>
<html>
<head>
<?php 

$rstate = new GeneralRequestState('en','home',false);
if (!empty($_GET['fcontent']))
{
$rstate->resetContent($_GET['fcontent']);
}
if (isset($_GET['fisMobile']))
{
$rstate->resetIsMobil(TRUE);
}

$headertool = new HtmlHeader($rstate);
echo $headertool->htmlcontent;
?>
</head>
<body>
	<h1>TEST FOR MAIN CONTENT REQUEST</h1>
	<form method='get' action='<?php echo $_SERVER['PHP_SELF'];?>'>
		<p>
			<input type="checkbox" name="fisMobile">isMobile<br>
		</p>
		<p>
			content: <input type="text" name="fcontent" value="home" />
		</p>
		<p>
			<input type="submit" value="RequestHeader">
		</p>
	</form>
	<h1>Html Header Content, type ctr+u to see sources</h1>
	<hr />
</body>
</html>
