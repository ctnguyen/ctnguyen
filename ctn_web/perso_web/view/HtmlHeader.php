<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';
require_once GlobalConfig::SERVER_ROOT_DIR.'view/ViewHelper.php';

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

	public function __construct(&$_general_request)
	{
		$this->htmlcontent = ViewHelper::getCommonHeader();

		$this->htmlcontent .= PHP_EOL.'<!-- common global style (mobile or normal browser)-->'.PHP_EOL;

		if($_general_request->_isMobile)
		{
			$this->htmlcontent .= '	<script src="'.GlobalConfig::DOMAINE_NAME .'view/style/mobibrowser_G_setting.js"></script>'.PHP_EOL.PHP_EOL;

			$this->htmlcontent .= '	<meta name="viewport" content="width=device-width, initial-scale=1">'.PHP_EOL;
			$this->htmlcontent .= '	<link rel="stylesheet" href="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.css" />'.PHP_EOL;
			$this->htmlcontent .= '	<script src="http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.js"></script>'.PHP_EOL;
		}
		else
		{
			$this->htmlcontent .= PHP_EOL.'	<script src="'.GlobalConfig::DOMAINE_NAME .'view/style/normalbrowser_G_setting.js"></script>'.PHP_EOL;
		}

		//if is mobile, print a global variable containing data of all navigation pages 
		//in form of JSON data, that will be used for jquery
		if($_general_request->_isMobile)
		{
			$this->htmlcontent .= PHP_EOL.'	<!--JSON data of navigatorlist in relation to multipages-->'.PHP_EOL;
			$this->htmlcontent .= '	<script type="text/javascript">'.PHP_EOL;
			$this->htmlcontent .= '	var navigatordata = {['.PHP_EOL;
			
			
			$default_content_request = $_general_request->_content_state;
			$this->htmlcontent .=  '			{pageID :"'.$_general_request->_content_state.'" , loaded : true }'.PHP_EOL;     
			
			$datafilename = ControllerHelper::getDataNavigatorListFile();
			$xmlDoc = new DOMDocument;
			$xmlDoc->load($datafilename);
			$langnode   = $xmlDoc->getElementsByTagName($_general_request->_lang_state)->item(0);
			$buttonlist = $langnode->getElementsByTagName("navigatebutton");
			foreach($buttonlist as $button)
			{
				$buttonID = $button->getElementsByTagName("idNAME")->item(0);
				if($buttonID)
				{
					if($buttonID->nodeValue != $default_content_request)
					{
						$_general_request->resetContent($buttonID->nodeValue);
						$this->htmlcontent .=  '			,{pageID :"'.$_general_request->_content_state.'" , loaded : false }'.PHP_EOL;
					}
				}
			}
				
			//reset the default request because it is a reference
			$_general_request->resetContent($default_content_request);
			
			
			$this->htmlcontent .= '	]};'.PHP_EOL;
			$this->htmlcontent .= '	</script>'.PHP_EOL;
		}	
		
		
		$this->htmlcontent .= '<!--'.PHP_EOL;
		$this->htmlcontent .= ' specific style specific to a content (might be pluriel)'.PHP_EOL;
		$this->htmlcontent .= ' Each time user change content, this part will also be updated'.PHP_EOL;
		$this->htmlcontent .= ' The file name rule is view/[<mobile?>_][contentID].js'.PHP_EOL;
		$this->htmlcontent .= '-->'.PHP_EOL;
		//if is not mobile, print only the specific style adequate to the content
		$this->htmlcontent .= ViewHelper::getSpecificStyleSetting($_general_request);
		
		//if is mobile, print also all other specific styles 
		if($_general_request->_isMobile)
		{
			$default_content_request = $_general_request->_content_state;
			
			$datafilename = ControllerHelper::getDataNavigatorListFile();			
			$xmlDoc = new DOMDocument;
			$xmlDoc->load($datafilename);			
			$langnode   = $xmlDoc->getElementsByTagName($_general_request->_lang_state)->item(0);
			$buttonlist = $langnode->getElementsByTagName("navigatebutton");
			foreach($buttonlist as $button)
			{
				$buttonID = $button->getElementsByTagName("idNAME")->item(0);
				if($buttonID)
				{
					if($buttonID->nodeValue != $default_content_request)
					{
						$_general_request->resetContent($buttonID->nodeValue);
						$this->htmlcontent .= ViewHelper::getSpecificStyleSetting($_general_request);
					}
				}
			}
			
			//reset the default request because it is a reference
			$_general_request->resetContent($default_content_request);
		}
	}
}

?>