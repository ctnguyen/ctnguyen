$(document).ready(function() {
	
	reset_blacksholes_style();
	
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_blacksholes_style();
	});
});


function reset_blacksholes_style()
{
	//$('div.BS').css({"background-color":"#00FFFF"});//TODO debug
	
	$('img').css({
		"display":"block"
		,"margin-left":"auto"
		,"margin-right":"auto"
	});

	$('h1.projectname').css({
		"text-align":"center"
		,"font-variant":"small-caps"
		,"font-family":"Georgia, 'Times New Roman', Times, serif"
	});
	
	$('#bottom-wrapper').css({	"position":"static"	});
}