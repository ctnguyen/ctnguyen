<?php

/* Definning here all constant variable helping for ease of use server information
 * Every information of server
 */
class GlobalConfig
{

	// define here all global constants
	const SERVER_ROOT_DIR   = '/home/ctnguyen/localserver/ctn_web/';
	const DOMAINE_NAME      = 'localhost/';
	const DEFAULT_LANG      = 'en';
	
	/** constructor for global config. setting cookies to the default value if it is not setted
	 *  the cookie time is usually setted to the time estimated of a visitor 
	 */
	public static function init($_cookie_time = 3600)
	{
		if( ($_COOKIE['lang'] !=='en') && ($_COOKIE['lang'] !=='fr') && ($_COOKIE['lang'] !=='vn') )
		{
			setcookie("lang", self::DEFAULT_LANG , time()+$_cookie_time);
		}
	}
	
	// Debug by printing global config constants
	public static  function get_global_config()
	{
		echo '<h1>SERVER_ROOT_DIR : [' . self::SERVER_ROOT_DIR . ']</h1>';
		echo '<h1>DOMAINE_NAME    : [' . self::DOMAINE_NAME    . ']</h1>';
		echo '<h1>DEFAULT_LANG    : [' . self::DEFAULT_LANG    . ']</h1>';
	}
}


?>