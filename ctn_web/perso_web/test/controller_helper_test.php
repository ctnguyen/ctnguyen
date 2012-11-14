<?php include '../controller/helper.php' ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<?php 
$headercommonpart = getCommonHeader();
echo $headercommonpart;
?>
</head>
<body>
	<h1>type ctr + u to see the header</h1>
	<br/>
	<?php 
	$footer_en = getFooter('en');
	echo $footer_en.PHP_EOL;
	?>
	<br/>
	<?php 
	$footer_fr = getFooter('fr');
	echo $footer_fr.PHP_EOL;
	?>
	<br/>
	<?php 
	$footer_vn = getFooter('vn');
	echo $footer_vn.PHP_EOL;
	?>
</body>
</html>
