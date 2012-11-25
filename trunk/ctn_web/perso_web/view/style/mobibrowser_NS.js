$(document).ready(function() {
	
	reset_navierstocks_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_home_style();
	});
});


function reset_navierstocks_mobistyle()
{
	$('h1').css({"color":"#FFFF00"});
}