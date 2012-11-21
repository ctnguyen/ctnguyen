/* 
 * COMMON SETTING FOR ALL BROWSER  : MOBILE AND NORMAL
 * 
 * Refactor here all common methods that can be use commonly everywhere
 * 
 */


function get_actual_lang_state()
{
	return $("div#actuallangue").text(); 
}

function reset_actual_lang_state(newlang)
{ 
	$("div#actuallangue").html(newlang); 
}

function get_actual_content_state()
{	
	return $("div#actualcontent").text(); 
}


function reset_actual_content_state(newlabel)
{
	$("div#actualcontent").html(newlabel); 
}