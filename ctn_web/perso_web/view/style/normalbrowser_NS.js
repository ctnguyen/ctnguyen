$(document).ready(function() {
	
	reset_navierstocks_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_navierstocks_style();
	});
});


function reset_navierstocks_style()
{
	//$('div.NS').css({"background-color":"#FFFF00"});//TODO debug
	
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