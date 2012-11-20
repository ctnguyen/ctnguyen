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
	public static function getDocType($_request)
	{
		$doctype = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">'.PHP_EOL;
		return $doctype;
	}

	public static function getHtmlHeader($_request, $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$headerwrapimagepath = '\''. GlobalConfig::DOMAINE_NAME .'model/htmldata/image/top_wrapper.jpg\'';
		$headerDiv = '';
		$headerDiv .= $indent.'<div id="top-wrapper"  style="background-image:url('.$headerwrapimagepath.');background-repeat:repeat-x">'.PHP_EOL;
		$headerDiv .= $indent.'	&nbsp;&nbsp;'.PHP_EOL;
		$headerDiv .= $indent.'</div>'.PHP_EOL;
		return $headerDiv;
	}

	public static function getHtmlFooter($_request, $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$footerwrapimagepath = '\''. GlobalConfig::DOMAINE_NAME .'model/htmldata/image/bottom_wrapper.jpg\'';

		$footerDiv  = '';
		$footerDiv .= $indent.'<div id="bottom-wrapper" style="background-image:url('.$footerwrapimagepath.');background-repeat:repeat-x">'.PHP_EOL;
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

}
?>