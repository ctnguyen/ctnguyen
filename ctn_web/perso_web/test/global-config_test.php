<?php

include '../global-config.php';


//strange behavior that when index setted cookie
//this page can not reset the cookie
//so return to index for removing the cookie setted
//setcookie("lang", "", time()-60000);

/* test if the cookie lang is setted after the constructor of GlobalConfig object
 * to set the time global small
 */
GlobalConfig::get_global_config();
GlobalConfig::init(5);
if( ($_COOKIE['lang'] !=='en') && ($_COOKIE['lang'] !=='fr') && ($_COOKIE['lang'] !=='vn') )
{
	echo '<h1>cookie lang is not setted in tree lang en,fr,vn</h1>';
}
else 
{
	echo '<h1>cookie lang is setted to default lang=['.$_COOKIE['lang'].']</h1>';
}

?>