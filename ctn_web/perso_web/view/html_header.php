<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/general_request_state.php';
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

	public function __constructor($_general_request)
	{
		$this->htmlcontent = ViewHelper::getCommonHeader();

		$auxStyleBindRelativePath = '';

		if($_general_request->_isMobile)
		{
			$this->htmlcontent .= '<link rel="stylesheet" href="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.css" />'.PHP_EOL;
			$this->htmlcontent .= '<script src="http://code.jquery.com/jquery-1.8.2.min.js"></script>'.PHP_EOL;
			$this->htmlcontent .= '<script src="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.js"></script>'.PHP_EOL;
		
			$auxStyleBindRelativePath = 'view/mobi_'.$_general_request.'.js';
		}
		else
		{
			$this->htmlcontent .= '<script src="'.GlobalConfig::DOMAINE_NAME .'view/normalbrowser_globallayout.js"></script>'.PHP_EOL;
		
			$auxStyleBindRelativePath = 'view/'.$_general_request.'.js';
		}
		
		$this->htmlcontent .= '<script src="'. GlobalConfig::DOMAINE_NAME . $auxStyleBindRelativePath .' "></script>'.PHP_EOL;

		
		
	}
}

?>