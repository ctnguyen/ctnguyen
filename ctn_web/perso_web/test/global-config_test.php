<?php

include '../global-config.php';


//strange behavior that when index setted cookie
//this page can not reset the cookie
//so return to index for removing the cookie setted
//setcookie("lang", "", time()-60000);

/* test if the cookie lang is setted after the constructor of GlobalConfig object
 * to set the time global small
 */

// Debug by printing global config constants
echo '<h1>SERVER_ROOT_DIR : [' . GlobalConfig::SERVER_ROOT_DIR . ']</h1>';
echo '<h1>DOMAINE_NAME    : [' . GlobalConfig::DOMAINE_NAME    . ']</h1>';
echo '<h1>DEFAULT_LANG    : [' . GlobalConfig::DEFAULT_LANG    . ']</h1>';

GlobalConfig::init_cookie_lang(5);
if( ($_COOKIE['lang'] !=='en') && ($_COOKIE['lang'] !=='fr') && ($_COOKIE['lang'] !=='vn') )
{
	echo '<h1>cookie lang is not setted in tree lang en,fr,vn</h1>';
}
else 
{
	echo '<h1>cookie lang is setted to default lang=['.$_COOKIE['lang'].']</h1>';
}

?>