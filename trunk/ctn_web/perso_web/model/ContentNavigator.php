<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/ControllerHelper.php';

/** \class ContentNavigator
 * This class handle the par "contentnavigator" of the navigator in the html file
 * Containing roughly a list of disponible content, read from a data xml file
 *
 * <div id="contentnavigator">
 *	$htmlcontent
 * </div>
 * 
 * All html content of this DIV is stored in the member variable $htmlcontent	
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
				if(!$_general_request->_isMobile)
				{
					$this->htmlcontent .= $additionalInden.'		'.$button->getElementsByTagName("htmlNAME")->item(0)->nodeValue.PHP_EOL;;
				}
			}
		}
		
		$this->htmlcontent .= $additionalInden.'	</ul>'.PHP_EOL;
		$this->htmlcontent .= $additionalInden.'</div>'.PHP_EOL;
	}	
}

?>