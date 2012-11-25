$(document).ready(function() {
	
	reset_cv_style();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_cv_style();
	});
	
});

function reset_cv_style()
{
	$('h1').css({"color":"#0000FF"});
}