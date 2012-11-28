$(document).ready(function() {
	
	reset_home_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_home_style();
	});

});

function reset_home_style()
{
	$('h1.home').css({"color":"#FFFF00"});
}