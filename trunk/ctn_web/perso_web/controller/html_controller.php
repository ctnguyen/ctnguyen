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

		$langnode   = $xmlDoc->getElementsByTagName($_lang)->item(0);
		$buttonlist = $langnode->getElementsByTagName("htmlbutton");
		
		$this->htmlcontent = '';
		$this->htmlcontent .= '	<div id="navigatorlist">'.PHP_EOL;
		foreach($buttonlist as $htmlbutton){
			$this->htmlcontent .= '		'.$htmlbutton->nodeValue.PHP_EOL;
		}
		$this->htmlcontent .= '	</div>'.PHP_EOL;
	}	
}

?>