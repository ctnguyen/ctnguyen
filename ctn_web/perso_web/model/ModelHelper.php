<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once dirname(__FILE__ ) . '/LangNavigator.php';
require_once dirname(__FILE__ ) . '/ContentNavigator.php';
require_once dirname(__FILE__ ) . '/MainContent.php';

/** model helpers
 */

class ModelHelper
{
	/** return the Doctype for Html, depending if its a mobile browser or normal browser
	 * return here
	 * <head>
	 * </head>
	 */
	public static function getDocType(&$_request)
	{
		$doctype = '';
		if(!$_request->_isMobile)
		{
			$doctype .= '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">'.PHP_EOL;
		}
		else
		{
			$doctype .= '<!DOCTYPE html>'.PHP_EOL;
		}
		return $doctype;
	}

	/* return the interior of the head tag in Html
	 * <head>
	 * 	return here 
	 * </head>
	 */
	public static function getHtmlHeader($_request, $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$headerwrapimagepath = '\''. GlobalConfig::DOMAINE_NAME .'model/htmldata/image/top_wrapper.jpg\'';
		$headerDiv = '';
		if(!($_request->isMobile) )
		{
			$headerDiv .= $indent.'<div id="top-wrapper"  style="background-image:url('.$headerwrapimagepath.');background-repeat:repeat-x">'.PHP_EOL;
			$headerDiv .= $indent.'	&nbsp;&nbsp;'.PHP_EOL;
			$headerDiv .= $indent.'</div>'.PHP_EOL;
		}
		return $headerDiv;
	}

	// return the div of bottom-wrapper, containing page-footer
	public static function getHtmlFooter($_request, $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$footerwrapimagepath = '\''. GlobalConfig::DOMAINE_NAME .'model/htmldata/image/bottom_wrapper.jpg\'';

		$footerDiv  = '';
		if( !($_request->_isMobile) )
		{
			$footerDiv .= $indent.'<div id="bottom-wrapper" style="background-image:url('.$footerwrapimagepath.');background-repeat:repeat-x">'.PHP_EOL;
		}
		else
		{
			$footerDiv .= $indent.'<div id="bottom-wrapper">'.PHP_EOL;
		}
		$footerDiv .= $indent.'	<h1 id="page-footer"> Chi-Thanh NGUYEN &copy; ';
		$actualyear = date('Y');
		$footerDiv .= $indent. $actualyear .' ';
		
		if($_request->_lang_state=='vn')
		{
			$footerDiv .= 'Web Đang xây dựng';
		}
		elseif($_request->_lang_state =='fr')
		{
			$footerDiv .= 'Web en construction';
		}
		else
		{
			$footerDiv .= 'Web in construct';
		}
		$footerDiv .= '</h1>'.PHP_EOL;
		$footerDiv .= $indent.'</div>'.PHP_EOL;

		return $footerDiv;
	}

	/** return the div of top-page, containing nothings visible,
	 *  but useful for referencing and, important, 
	 *  TOOL FOR DETECTING ACTUAL STATE OF PAGE 
	 */ 
	public static function getHtmlTopPage($_request, $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$toppageDiv = '';
		$toppageDiv .= $indent.'<div id="top-page">'.PHP_EOL;
		$toppageDiv .= $indent.'	<div class="referencing"><h1>NGUYEN Chi Thanh, INRIA, SOFA, Digiplante, Paris VI, Paris 6</h1></div>'.PHP_EOL;
		$toppageDiv .= $indent.'	<div id="actuallangue" style="display:none;">fr</div>'.PHP_EOL;
		$toppageDiv .= $indent.'	<div id="actualcontent" style="display:none;">home</div>'.PHP_EOL;
		$toppageDiv .= $indent.'</div>'.PHP_EOL;
		return $toppageDiv;
	}

	// return the div of navigator (navbar for mobile, sidebar for normal visualization)
	public static function getHtmlNavigator($_request, $nbIndent=0)
	{
		$nbIndentPP =  $nbIndent+1;
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$html_navigator = '';

		$flag_part = new LangNavigator($_request,$nbIndentPP);

		$content_part = new ContentNavigator($_request,$nbIndentPP);

		$html_navigator .= $indent.'<div id="navigator">'.PHP_EOL;
		$html_navigator .= 					$flag_part->htmlcontent;
		$html_navigator .= 					$content_part->htmlcontent;
		$html_navigator .= $indent.'</div>'.PHP_EOL;

		return $html_navigator;
	}

	// return the div maincontent of the html page
	public static function getHtmlMainContent($_request, $nbIndent=0)
	{
		$nbIndentPP =  $nbIndent+1;
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}

		$html_maincontent = '';

		$maincontent_part = new MainContent($_request,$nbIndentPP);

		$html_maincontent .= $indent.'<div id="maincontent">'.PHP_EOL;
		$html_maincontent .= 				$maincontent_part->htmlcontent;
		$html_maincontent .= $indent.'</div>'.PHP_EOL;

		return $html_maincontent;
	}

	// return the div of Bottom page, nothing visible, but useful for referencing
	public static function getHtmlBottomPage($_request, $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}

		$bottompageDiv = '';
		$bottompageDiv .= $indent.'<div id="bottom-page">'.PHP_EOL;
		$bottompageDiv .= $indent.'	<div class="referencing"><h1>NGUYEN Chi Thanh, INRIA, SOFA, Digiplante, Paris VI, Paris 6</h1></div>'.PHP_EOL;
		$bottompageDiv .= $indent.'</div>'.PHP_EOL;
		return $bottompageDiv;
	}

}
?>