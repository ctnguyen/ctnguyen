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
	
	/** initialize the lang cookie.
	 * if  _COOKIE['lang'] is not 'en', nor 'fr', nor 'vn',
	 * set it to de default lange i.e 'en' 
	 */
	public static function init_cookie_lang($_cookie_time = 3600)
	{
		if( ($_COOKIE['lang'] !=='en') && ($_COOKIE['lang'] !=='fr') && ($_COOKIE['lang'] !=='vn') )
		{
			setcookie("lang", self::DEFAULT_LANG , time()+$_cookie_time);
		}
	}
	
	
	/** request if user is in a mobile browser
	 * 
	 */
	public static function isMobile()
	{
		$ismobile = false;
		if(strstr(strtolower($_SERVER['HTTP_USER_AGENT']), 'mobile') || strstr(strtolower($_SERVER['HTTP_USER_AGENT']), 'android'))
		{
			$ismobile = true;
		}
		return $ismobile;
	}
}


?>