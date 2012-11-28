$(document).ready(function() {
	
	reset_cv_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_cv_style();
	});
	
});

function reset_cv_style()
{
	$('h1.cv').css({"color":"#0000FF"});
}