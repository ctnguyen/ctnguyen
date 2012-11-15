<?php
include '../global-config.php';
include '../controller/general_request_state.php';

/* \class MainContent
 * This class in handle the main content of the web. The content is stored in a .html file
 * 
 * It is build by giving a GeneralRequestState from user. 
 *  
 */

class MainContent
{
	public $htmlcontent;
	
	public function __construct($_general_request)
	{
		//get path to the html file.
		$filepath  = GlobalConfig::SERVER_ROOT_DIR.'model/htmldata/';
		$filepath .= $_general_request->_lang_state . '/';
		$filepath .= $_general_request->_content_state . 'html';
		
		if( file_exists($filepath) )
		{
			$this->htmlcontent = 'file path=['.$filepath.']';
		}
		else
		{
			$this->htmlcontent = '<h1>ERROR file path=['.$filepath.'] does not exists<h1>';
		}
	}
}


?>