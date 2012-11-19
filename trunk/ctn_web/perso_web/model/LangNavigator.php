<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');
require_once GlobalConfig::SERVER_ROOT_DIR.'controller/GeneralRequestState.php';

class LangNavigator
{
	public $htmlcontent;
	
	public function __construct($_general_request , $nbIndent=0)
	{
		$indent = '';
		for($i=0; $i< $nbIndent ; $i++)
		{
			$indent .= '	';
		}
		
		$this->htmlcontent='';
		$this->htmlcontent .= $indent.'<div id="langnavigator">'.PHP_EOL;
		$this->htmlcontent .= $indent.'	<table>'.PHP_EOL;
		$this->htmlcontent .= $indent.'		<tr>'.PHP_EOL;

		$this->htmlcontent .= $indent.'			<td><img id="en" class="langbutton" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_en.png"/></td>'.PHP_EOL;
		$this->htmlcontent .= $indent.'			<td><img id="fr" class="langbutton" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_fr.png"/></td>'.PHP_EOL;
		$this->htmlcontent .= $indent.'			<td><img id="vn" class="langbutton" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_vn.png"/></td>'.PHP_EOL;
		
		$this->htmlcontent .= $indent.'		</tr>'.PHP_EOL;
		$this->htmlcontent .= $indent.'	</table>'.PHP_EOL;
		$this->htmlcontent .= $indent.'</div>'.PHP_EOL;
		
		$this->htmlcontent .= $indent.'<div align="center">'.PHP_EOL;
		$this->htmlcontent .= $indent.'	<img id="logo" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/ctn.jpg"/>'.PHP_EOL;
		$this->htmlcontent .= $indent.'</div>'.PHP_EOL;
	}
}

?>