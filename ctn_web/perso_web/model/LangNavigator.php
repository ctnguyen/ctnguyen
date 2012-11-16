<?php
require_once realpath( dirname(__FILE__ ) . '/../global-config.php');

class LangNavigator
{
	public $htmlcontent;
	
	public function __construct()
	{
		$this->htmlcontent='';
		$this->htmlcontent .= '		<div id="langnavigator">'.PHP_EOL;
		$this->htmlcontent .= '			<table>'.PHP_EOL;
		$this->htmlcontent .= '				<tr>'.PHP_EOL;

		$this->htmlcontent .= '					<td><img id="en" class="langbutton" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_en.png"/></td>'.PHP_EOL;
		$this->htmlcontent .= '					<td><img id="fr" class="langbutton" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_fr.png"/></td>'.PHP_EOL;
		$this->htmlcontent .= '					<td><img id="vn" class="langbutton" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_vn.png"/></td>'.PHP_EOL;
		
		$this->htmlcontent .= '				</tr>'.PHP_EOL;
		$this->htmlcontent .= '			</table>'.PHP_EOL;
		$this->htmlcontent .= '		</div>'.PHP_EOL;
		
		$this->htmlcontent .= '		<div align="center">'.PHP_EOL;
		$this->htmlcontent .= '				<img id="logo" src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/ctn.jpg"/>'.PHP_EOL;
		$this->htmlcontent .= '		</div>'.PHP_EOL;
	}
}

?>