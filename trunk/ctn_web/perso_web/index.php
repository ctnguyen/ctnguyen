<?php

include 'global-config.php';
include 'controller/request_state.php';

GlobalConfig::init(5);//TODO set to big number

$requeststate = new RequestState('','');

//default content is 'home'
if(empty($_GET['maincontent']) )
{
	$requeststate->resetContent('home');
}
else
{
	$requeststate->resetContent($_GET['maincontent']);
}

//normally after build GlobalConfig, cookie['lang'] is not empty
if(empty($_GET['lang']))
{
	if(empty($_COOKIE['lang']))
	{
		$requeststate->resetLang(GlobalConfig::DEFAULT_LANG);
	}
	else
	{
		$requeststate->resetLang($_COOKIE['lang']);
	}
}
else
{
	$requeststate->resetLang($_GET['lang']);
}


echo '<h1>hello index works</h1>'


?>