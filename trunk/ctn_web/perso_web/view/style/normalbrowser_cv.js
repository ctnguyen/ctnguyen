$(document).ready(function() {
	
	reset_cv_style();
	
	$("#maincontent").live('maincontenthaschanged',function(event) {
		reset_cv_style();
	});
	
});

function reset_cv_style()
{
	//$('div.cv').css({"background-color":"#0000FF"});//TODO debug
	
	// CV mobile globale style =================================================
	$('div.cv').css({
		'font-family':'"Courier New", Courier, monospace'
	});
	
	$('h1.cv').css({
		'text-align':'center'
		,'font-variant':'small-caps'
		,'font-family':'Georgia, "Times New Roman", Times, serif'
		,'font-size':'200%'
	});
	
	$('h2.cv').css({
		'text-align':'left'
		,'background-color':'#BFBFBF'
		,'font-family':'"Comic Sans MS", cursive, sans-serif'
	});
	
	$('.xpdate').css({"float":"left"});
	$('.xpenterprise').css({"float":"right"});
	
	$('.xptechnolabel').css({"float":"left","margin-right":"2em"});
	$('.xptechnolist').css({"float":"left"});

	$('.clearfloatting').css({"clear":"both"});
	
	//Skills styles =============================================================
	$('#skillstable').css({
		'align':'center'
		,'width':'90%'
		,'border-collapse':'collapse'
		,'border':'1px solid black'
		,'margin-left':'auto'
		,'margin-right':'auto'
		,'margin-top':'1em'
		,'margin-bottom':'1em'
	});

	$('tr.cvskills').css({ 'border':'1px solid black' });
	$('td.cvskills').css({ 'border':'1px solid black' });
	
	$('p.skilllabel').css({
		'font-family':'Georgia, "Times New Roman", Times, serif','font-weight':'bold'
	}) ;
	
	//Experiences styles =============================================================
	$('.xpdatebar').css({
		'font-weight':'bold'
		,'font-family':'"Brush Script MT", monospace'
		,'font-size':'110%'
	});
	$('.xpdate').css({'margin':'0','padding':'0','background-color':'#BFBFBF','margin-bottom':'1em'});
	$('.xpenterprise').css({'margin':'0','padding':'0','background-color':'#BFBFBF','margin-bottom':'1em'});
	
	$('.xptechnobar').css({
		'margin':'0','padding':'0'
		,'margin-bottom':'4em'
	});
	$('.xptechnolabel').css({'font-weight':'bold'});
	
	//Education styles =============================================================
	$('#educationtable').css({
		'align':'center'
		,'margin-left':'auto'
		,'margin-right':'auto'
	});
	
	$('td.cveducation').css({'padding-left':'1em'});
	
	$('#bottom-wrapper').css({	"position":"static"	});
}