<?php

/*
 * Check informations on severs 
 */
echo 'HTTP_USER_AGENT=['; echo $_SERVER['HTTP_USER_AGENT'] . "]<br>";

echo 'SERVER_ROOT_DIR=[';  echo getcwd();echo ']<br>';

echo 'size of _COOKIE=' .count($_COOKIE).'<br>';

foreach ($_COOKIE as $_ckey => $_cvalue) {
	echo "Key=[$_ckey]    Value=[$_cvalue]<br>";
}

if(strstr(strtolower($_SERVER['HTTP_USER_AGENT']), 'mobile') || strstr(strtolower($_SERVER['HTTP_USER_AGENT']), 'android')) 
{
   echo "<h1>You are running a mobile webbrowser!<h1>";
}
//phpinfo();
?>