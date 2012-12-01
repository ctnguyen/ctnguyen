$(document).ready(function() {
	
	reset_home_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_home_style();
	});

});

function reset_home_style()
{
	//$('div.home').css({"background-color":"#FF0000"});//TODO debug
	
	$('ul#motivations.home').css({
		"list-style-type":"square"
	});

	$('ul#webtechnologies.home').css({
		"list-style-type":"none"
	});
	
	$('#bottom-wrapper').css({	"position":"fixed"	});
}