$(document).ready(function() {
	
	reset_contact_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_contact_mobistyle();
	});
});

function reset_contact_mobistyle()
{
	$('h1').css({"color":"#00FF00"});	
}