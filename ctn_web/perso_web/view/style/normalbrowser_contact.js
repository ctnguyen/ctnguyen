$(document).ready(function() {
	
	reset_contact_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_contact_style();
	});
});

function reset_contact_style()
{
	$('div.contact').css({"background-color":"#00FF00"});//TODO debug
	
	$('ul.contact').css({
		"list-style-type":"none"
	});
	
	$('#bottom-wrapper').css({	"position":"fixed"	});
}