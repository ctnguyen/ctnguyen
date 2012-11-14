<?php

/* Definning here all constant variable helping for ease of use server information
 * Every information of server
*/
class RequestState
{

	public $_lang_state;
	public $_content_state;

	public function __construct($_l ,$_c)
	{
		$this->_lang_state    = $_l;
		$this->_content_state = $_c;
	}

	public function reset($_l,$_c)
	{
		$this->_lang_state    = $_l;
		$this->_content_state = $_c;
	}
	
	public function resetLang($_l)
	{
		$this->_lang_state    = $_l;
	}
	
	public function resetContent($_c)
	{
		$this->_content_state = $_c;
	}

}

?>