<?php
include '../global-config.php';

/* class returning the content html of all controllers
 * concretly this is the sidebar in the web
 */
class HtmlController
{
	public $htmlcontent;
	
	public function __construct($_lang)
	{
		$datafilename = '';
		$datafilename .= GlobalConfig::SERVER_ROOT_DIR.'controller/data/HtmlController.xml';
		
		$xmlDoc = new DOMDocument;
		$xmlDoc->load($datafilename);

		$languenode     = $xmlDoc->getElementsByTagName($_lang)->item(0);
		$buttonnamelist = $languenode->getElementsByTagName('buttonname');
		
		$this->htmlcontent = '';
		$this->htmlcontent .= '<div id="navigatorlist">'.PHP_EOL;
		$this->htmlcontent .= '<ul>'.PHP_EOL;
		foreach($buttonnamelist as $buttonname){
			$this->htmlcontent .= '<li>';
			$this->htmlcontent .= $buttonname->nodeValue;
			$this->htmlcontent .= '</li>'.PHP_EOL;
		}
		$this->htmlcontent .= '</ul>'.PHP_EOL;
		$this->htmlcontent .= '</div>'.PHP_EOL;
	}	
}

?>