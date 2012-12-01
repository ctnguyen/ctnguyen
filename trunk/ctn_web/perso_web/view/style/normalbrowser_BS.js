$(document).ready(function() {
	
	reset_blacksholes_style();
	
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_blacksholes_style();
	});
});


function reset_blacksholes_style()
{
	$('div.BS').css({"background-color":"#00FFFF"});//TODO debug
}