<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';

/* \class MainContent
 * This class in handle the main content of the web. The content is stored in a .html file
 * 
 * It is build by giving a GeneralRequestState from user. 
 *  
 */

class MainContent
{
	public $htmlcontent;
	
	public function __construct($_general_request,$nbIndent=0)
	{
		//get path to the html file.
		$filepath  = GlobalConfig::SERVER_ROOT_DIR.'model/htmldata/';
		$filepath .= $_general_request->_lang_state . '/';
		$filepath .= $_general_request->_content_state . '.html';
		
		$additionalInden = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$additionalInden .= '	';
		}
		
		
		$htmlcontent = '';
		if( file_exists($filepath) )
		{
			$handle = @fopen($filepath, 'r');
			if ($handle) {
				while (($buffer = fgets($handle, 4096)) !== false) {
					$this->htmlcontent .= $additionalInden . $buffer;
				}
				if (!feof($handle)) {
					$this->htmlcontent .= '<p style="color:red"><b>Error: unexpected fgets() fail</b></p>'.PHP_EOL;
				}
				fclose($handle);
			}	
		}
		else
		{
			$this->htmlcontent = '<p style="color:red"><b>ERROR file path=['.$filepath.'] does not exists</b></p>';
		}
	}
}


?>