$(document).ready(function() {
	
	reset_cv_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_cv_mobistyle();
	});
	
});

function reset_cv_mobistyle()
{
	$('h1').css({"color":"#0000FF"});
}