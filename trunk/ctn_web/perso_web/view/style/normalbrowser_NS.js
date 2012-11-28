$(document).ready(function() {
	
	reset_navierstocks_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_home_style();
	});
});


function reset_navierstocks_style()
{
	$('h1.NS').css({"color":"#FFFF00"});
}