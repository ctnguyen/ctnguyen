<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');

/** view helpers 
 */

//
class ViewHelper
{
	/** Print the html common part for the html <heade>
	 *  depending on the content requested and the device (mobile or not)
	 *  <head>
	 *  	[print the common part of this part]
	 *  
	 *  
	 *  </head>
	 */
	public static function getCommonHeader()
	{
		$commonheader = '<!-- common html header for all case-->'.PHP_EOL;
		$commonheader.= '	<base href="'.GlobalConfig::DOMAINE_NAME.'">'.PHP_EOL;
		$commonheader.= '	<title>Chi-Thanh NGUYEN</title>'.PHP_EOL;
		$commonheader.= '	<meta name="keywords" content="NGUYEN Chi-Thanh, SOFA, INRIA, CEMEF, nanoindentation, UPMC, ANEDP, Paris 6, Paris VI"/>'.PHP_EOL;
		$commonheader.= '	<meta http-equiv="content-type"	content="application/xhtml+xml; charset=utf-8" />'.PHP_EOL;
		$commonheader.= '	<meta name="author" content="Chi-Thanh NGUYEN" />'.PHP_EOL.PHP_EOL;
		
		// jquery is a common use
		$commonheader.= '	<script src="http://code.jquery.com/jquery-1.8.2.min.js"></script>'.PHP_EOL;
		$commonheader.= '	<script src="'.GlobalConfig::DOMAINE_NAME.'view/style/common_setting.js"></script>'.PHP_EOL;
		
		return $commonheader;
	}
	
	
	/** Print the html tag <script class="specificstyle"> for the html <heade>
	 *  depending on the content requested and the device (mobile or not) 
	 *   <head>
	 *   
	 *   
	 *  	<script class="specificstyle" src="[DOMAINE_NAME]/view/style/[mobi]_[content].js"></script>
	 *  </head>
	 */
	public static function getSpecificStyleSetting(&$_general_request)
	{
		$specificstylescript = '';
		
		if($_general_request->_isMobile)
		{
			$specificstylescript .= '	<script class="specificstyle" src="'.GlobalConfig::DOMAINE_NAME.'view/style/mobibrowser_'.$_general_request->_content_state.'.js"></script>'.PHP_EOL;
		}
		else
		{
			$specificstylescript .= '	<script class="specificstyle" src="'.GlobalConfig::DOMAINE_NAME.'view/style/normalbrowser_'.$_general_request->_content_state.'.js"></script>'.PHP_EOL;
		}
		
		return $specificstylescript;
	}
}
?>