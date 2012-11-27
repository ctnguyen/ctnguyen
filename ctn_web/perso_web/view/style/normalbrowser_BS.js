$(document).ready(function() {
	
	reset_blacksholes_style();
	
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_blacksholes_style();
	});
});


function reset_blacksholes_style()
{
	$('h1.BS').css({"color":"#FF0000"});	
}