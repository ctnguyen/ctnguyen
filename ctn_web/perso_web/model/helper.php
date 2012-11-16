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
	
	public static function getHtmlFooter($_lang)
	{
		$footerDiv .= '	<div id="footer">'.PHP_EOL;
		$footerDiv .= '		Chi-Thanh NGUYEN &copy;';
		$footerDiv .= date('Y').' ';
		if($lang=='vn')
		{
			$footerDiv .= 'Web Đang xây dựng';
		}
		elseif($lang=='fr')
		{
			$footerDiv .= 'Web in construction';
		}
		else
		{
			$footerDiv .= 'Web in construction';
		}
		$footerDiv .= PHP_EOL;
		$footerDiv .= '	</div>'.PHP_EOL;
		
		return $footerDiv;
	}
	
	
	public static function getHtmlNavigator($_request)
	{
		$html_navigator = '';
		
		$flag_part = new LangNavigator();
		
		$content_part = new ContentNavigator($_request->_lang_state);
		
		$html_navigator .= '	<div id="navigator">'.PHP_EOL;
		$html_navigator .= 			$flag_part->htmlcontent;
		$html_navigator .= 			$content_part->htmlcontent;
		$html_navigator .= '	</div>'.PHP_EOL;
		
		return $html_navigator;
	}
	
	public static function getHtmlMainContent($_request)
	{
		$html_maincontent = '';

		$maincontent_part = new MainContent($_request);

		$html_maincontent .= '	<div id="maincontent">'.PHP_EOL;
		$html_maincontent .= $maincontent_part->htmlcontent;
		$html_maincontent .= '	</div>'.PHP_EOL;

		return $html_maincontent;
	}
	
}
?>