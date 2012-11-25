$(document).ready(function() {
	
	reset_navierstocks_style();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_home_style();
	});
});


function reset_navierstocks_style()
{
	$('h1').css({"color":"#FFFF00"});
}