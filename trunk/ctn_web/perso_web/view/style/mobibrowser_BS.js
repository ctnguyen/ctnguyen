$(document).ready(function() {
	
	reset_blacksholes_mobistyle();
	
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_blacksholes_mobistyle();
	});
});


function reset_blacksholes_mobistyle()
{
	$('h1').css({"color":"#FF0000"});	
}