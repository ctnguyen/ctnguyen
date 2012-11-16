<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/general_request_state.php';
require_once dirname(__FILE__ ) . '/LangNavigator.php';
require_once dirname(__FILE__ ) . '/ContentNavigator.php';

/** model helpers 
 */

class ModelHelper
{
	
	public static function getFooter($_lang)
	{
		$footerDiv = '	<div id="footer">';

		$footerDiv .= 'Chi-Thanh NGUYEN &copy;';
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

		$footerDiv .= '</div>';
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
	
}
?>