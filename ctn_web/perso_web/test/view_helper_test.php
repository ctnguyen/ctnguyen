<?php 
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'view/helper.php'; 
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<?php 
$headercommonpart = ViewHelper::getCommonHeader();
echo $headercommonpart;
?>
</head>
<body>
	<h1>type ctr + u to see the header</h1>	
</body>
</html>
