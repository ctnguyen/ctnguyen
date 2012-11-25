$(document).ready(function() {
	
	reset_home_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_home_mobistyle();
	});

});

function reset_home_mobistyle()
{
	$('h1').css({"color":"#FFFF00"});
}