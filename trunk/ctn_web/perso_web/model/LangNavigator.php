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

		$this->htmlcontent .= '					<td><img src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_en.png" alt="en"/></td>'.PHP_EOL;
		$this->htmlcontent .= '					<td><img src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_fr.png" alt="fr"/></td>'.PHP_EOL;
		$this->htmlcontent .= '					<td><img src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/icon_vn.png" alt="vn"/></td>'.PHP_EOL;
		
		$this->htmlcontent .= '				</tr>'.PHP_EOL;
		$this->htmlcontent .= '			</table>'.PHP_EOL;
		$this->htmlcontent .= '		</div>'.PHP_EOL;
		
		$this->htmlcontent .= '		<div id="logo">'.PHP_EOL;
		$this->htmlcontent .= '			<center>'.PHP_EOL;
		$this->htmlcontent .= '				<img src="'. GlobalConfig::DOMAINE_NAME . 'model/htmldata/image/ctn.jpg"/>'.PHP_EOL;
		$this->htmlcontent .= '			</center>'.PHP_EOL;
		$this->htmlcontent .= '		<div id="logo">'.PHP_EOL;
	}
}

?>