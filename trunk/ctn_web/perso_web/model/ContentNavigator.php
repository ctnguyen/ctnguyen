<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';

/* class returning the content html of all content
 * concretly this is the sidebar in the web
 */
class ContentNavigator
{
	public $htmlcontent;
	
	public function __construct(&$_general_request , $nbIndent=0)
	{
		$additionalInden = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$additionalInden .= '	';
		}
		
		$datafilename = ControllerHelper::getDataNavigatorListFile();
		
		$xmlDoc = new DOMDocument;
		$xmlDoc->load($datafilename);

		$langnode   = $xmlDoc->getElementsByTagName($_general_request->_lang_state)->item(0);
		$buttonlist = $langnode->getElementsByTagName("navigatebutton");
		
		$this->htmlcontent = '';
		$this->htmlcontent .= $additionalInden.'<div id="contentnavigator">'.PHP_EOL;
		$this->htmlcontent .= $additionalInden.'	<ul>'.PHP_EOL;
		
		foreach($buttonlist as $button)
		{
			$buttonID = $button->getElementsByTagName("idNAME")->item(0);
			if($buttonID)
			{
				$this->htmlcontent .= $additionalInden.'		<li><a ';
				$this->htmlcontent .= 'id="'.$buttonID->nodeValue.'" class="navigatebutton"';
				$this->htmlcontent .= '>'.$button->getElementsByTagName("htmlNAME")->item(0)->nodeValue;
				$this->htmlcontent .= '</a></li>'.PHP_EOL;
			}
			else
			{
				$this->htmlcontent .= $additionalInden.'		'.$button->getElementsByTagName("htmlNAME")->item(0)->nodeValue.PHP_EOL;;
			}
		}
		
		$this->htmlcontent .= $additionalInden.'	</ul>'.PHP_EOL;
		$this->htmlcontent .= $additionalInden.'</div>'.PHP_EOL;
	}	
}

?>