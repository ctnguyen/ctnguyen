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
	public static function getDocType()
	{
		$doctype = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">';
		return $doctype;
	}
	
	public static function getHtmlHeader()
	{
		$headerwrapimagepath = '\''. GlobalConfig::DOMAINE_NAME .'model/htmldata/image/top_wrapper.jpg\'';
		$headerDiv = '';
		$headerDiv .= '		<div id="page-header"  style="background-image:url('.$headerwrapimagepath.');background-repeat:repeat-x">&nbsp;&nbsp;</div>'.PHP_EOL;
		return $headerDiv;
	}
	
	public static function getHtmlFooter($_lang)
	{
		$footerwrapimagepath = '\''. GlobalConfig::DOMAINE_NAME .'model/htmldata/image/bottom_wrapper.jpg\'';
		
		$footerDiv  = '';
		$footerDiv .= '		<div id="page-footer" style="background-image:url('.$footerwrapimagepath.');background-repeat:repeat-x">'.PHP_EOL;
		$footerDiv .= '			<h1 class="page-footer"> Chi-Thanh NGUYEN &copy; ';
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
		$footerDiv .= '</h1>'.PHP_EOL;
		$footerDiv .= '		</div>'.PHP_EOL;
		
		//$footerDiv .= '		<script type="text/javascript">	$(document).ready(function(){$(\'#page-footer\').css({	"background" :"#FFFFFF url(http://localhost/view/image/bottom_wrapper.jpg) repeat-x"});});</script>'.PHP_EOL;
		
		return $footerDiv;
	}
	
	
	public static function getHtmlNavigator($_request)
	{
		$html_navigator = '';
		
		$flag_part = new LangNavigator();
		
		$content_part = new ContentNavigator($_request->_lang_state);
		
		$html_navigator .= '			<div id="navigator">'.PHP_EOL;
		$html_navigator .= 					$flag_part->htmlcontent;
		$html_navigator .= 					$content_part->htmlcontent;
		$html_navigator .= '			</div>'.PHP_EOL;
		
		return $html_navigator;
	}
	
	public static function getHtmlMainContent($_request)
	{
		$html_maincontent = '';

		$maincontent_part = new MainContent($_request);

		$html_maincontent .= '			<div id="maincontent">'.PHP_EOL;
		$html_maincontent .= 				$maincontent_part->htmlcontent;
		$html_maincontent .= '			</div>'.PHP_EOL;

		return $html_maincontent;
	}
	
}
?>