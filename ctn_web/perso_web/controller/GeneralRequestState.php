<?php

/* \class GeneralRequestState
 * A Request State in general contain three informations
 * - the language
 * - the main content
 * - is user's browser from a mobile
 * All these informations are bind in this class
 */
class GeneralRequestState
{

	public $_lang_state;
	public $_content_state;
	public $_isMobile;

	public function __construct($_l ,$_c,$_isM)
	{
		$this->_lang_state    = $_l;
		$this->_content_state = $_c;
		$this->_isMobile      = $_isM;
	}

	public function reset($_l,$_c,$_isM)
	{
		$this->_lang_state    = $_l;
		$this->_content_state = $_c;
		$this->_isMobile      = $_isM;
	}
	
	public function resetLang($_l)
	{
		$this->_lang_state    = $_l;
	}
	
	public function resetContent($_c)
	{
		$this->_content_state = $_c;
	}

	public function resetIsMobil($_isM)
	{
		$this->_isMobile      = $_isM;
	}
}

?>