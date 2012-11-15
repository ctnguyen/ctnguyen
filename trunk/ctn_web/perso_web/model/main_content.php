<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/general_request_state.php';

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
		$filepath .= $_general_request->_content_state . '.html';
		
		if( file_exists($filepath) )
		{
			//$this->htmlcontent = 'file path=['.$filepath.']';
			$filename = "/usr/local/something.txt";
			$handle = fopen($filepath, 'r');
			$this->htmlcontent = fread($handle, filesize($filepath));
			fclose($handle);
		}
		else
		{
			$this->htmlcontent = '<p style="color:red"><b>ERROR file path=['.$filepath.'] does not exists</b></p>';
		}
	}
}


?>