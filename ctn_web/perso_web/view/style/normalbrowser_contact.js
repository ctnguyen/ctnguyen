$(document).ready(function() {
	
	reset_contact_style();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_contact_style();
	});
});

function reset_contact_style()
{
	$('h1.contact').css({"color":"#00FF00"});	
}