<?php
/** controller helpers 
 */

//
function getCommonHeader()
{
	$commonheader = '';
	$commonheader.= '<title>Chi-Thanh NGUYEN</title>'.PHP_EOL;
	$commonheader.= '<meta http-equiv="content-type" content="application/xhtml+xml; charset=utf-8"/>'.PHP_EOL;
	$commonheader.= '<meta name="keywords" content="NGUYEN Chi-Thanh, SOFA, INRIA, CEMEF, nanoindentation, UPMC, ANEDP, Paris 6, Paris VI"/>'.PHP_EOL;
	$commonheader.= '<meta name="description" content=""/>'.PHP_EOL;
	$commonheader.= '<meta name="robots" content="follow"/>'.PHP_EOL;
	
	return $commonheader;
}
?>