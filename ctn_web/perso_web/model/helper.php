<?php
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

}
?>