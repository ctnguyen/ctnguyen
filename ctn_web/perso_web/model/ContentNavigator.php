<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');

/* class returning the content html of all controllers
 * concretly this is the sidebar in the web
 */
class ContentNavigator
{
	public $htmlcontent;
	
	public function __construct($_lang)
	{
		$datafilename = '';
		$datafilename .= GlobalConfig::SERVER_ROOT_DIR.'controller/data/NavigatorList.xml';
		
		$xmlDoc = new DOMDocument;
		$xmlDoc->load($datafilename);

		$langnode   = $xmlDoc->getElementsByTagName($_lang)->item(0);
		$buttonlist = $langnode->getElementsByTagName("navigatebutton");
		
		$this->htmlcontent = '';
		$this->htmlcontent .= '		<div id="contentnavigator">'.PHP_EOL;
		$this->htmlcontent .= '			<ul>'.PHP_EOL;
		
		foreach($buttonlist as $button)
		{
			$buttonID = $button->getElementsByTagName("idNAME")->item(0);
			if($buttonID)
			{
				$this->htmlcontent .= '				<li><a ';
				$this->htmlcontent .= 'id="'.$buttonID->nodeValue.'"';
				$this->htmlcontent .= '>'.$button->getElementsByTagName("htmlNAME")->item(0)->nodeValue;
				$this->htmlcontent .= '</a></li>'.PHP_EOL;
			}
			else
			{
				$this->htmlcontent .= '				'.$button->getElementsByTagName("htmlNAME")->item(0)->nodeValue.PHP_EOL;;
			}
			
		}
		
		$this->htmlcontent .= '			</ul>'.PHP_EOL;
		$this->htmlcontent .= '		</div>'.PHP_EOL;
	}	
}

?>