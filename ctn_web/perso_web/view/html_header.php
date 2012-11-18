<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/helper.php';

/* \class HtmlHeader
 *
 * This class in handle the part in the HEADER of the web.
 * This HEADER depend on
 * - if the user's browser is a Mobile
 * - the main content requested by user
 *
 * Everythings between html tag HEAD will be stored in the proprety $htmlcontent
 *
 */

class HtmlHeader
{
	public $htmlcontent;

	public function __construct($_general_request)
	{
		$this->htmlcontent = ViewHelper::getCommonHeader();
		
		$this->htmlcontent .= PHP_EOL.'<!-- common global style (mobile or normal browser)-->'.PHP_EOL;
		
		$auxStyleBindRelativePath = '';
		if($_general_request->_isMobile)
		{
			$this->htmlcontent .= '<meta name="viewport" content="width=device-width, initial-scale=1">';
			$this->htmlcontent .= '	<link rel="stylesheet" href="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.css" />'.PHP_EOL;
			$this->htmlcontent .= '	<script src="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.js"></script>'.PHP_EOL;
			
			$this->htmlcontent .= '	<script src="'.GlobalConfig::DOMAINE_NAME .'view/style/global_mobibrowser_layout.js"></script>'.PHP_EOL;
			$auxStyleBindRelativePath .= 'view/style/mobi_'.$_general_request->_content_state . '.js';
		}
		else
		{
			$this->htmlcontent .= '	<script src="'.GlobalConfig::DOMAINE_NAME .'view/style/global_normalbrowser_layout.js"></script>'.PHP_EOL;
			$auxStyleBindRelativePath .= 'view/style/'.$_general_request->_content_state .'.js';
		}
		
		$this->htmlcontent .= '<!--'.PHP_EOL;
		$this->htmlcontent .= ' Auxiliar style specific to a content (might be pluriel)'.PHP_EOL;
		$this->htmlcontent .= ' Each time user change content, this part will also be updated'.PHP_EOL;
		$this->htmlcontent .= ' The file name rule is view/[<mobile?>_][contentID].js'.PHP_EOL;
		$this->htmlcontent .= '-->'.PHP_EOL;
		$this->htmlcontent .= '	<script class="specificstyle" src="'. GlobalConfig::DOMAINE_NAME . $auxStyleBindRelativePath .'"></script>'.PHP_EOL;
		//$this->htmlcontent .= '	<script type="text/javascript" src="'. GlobalConfig::DOMAINE_NAME . $auxStyleBindRelativePath .'"></script>'.PHP_EOL;
	}
}

?>