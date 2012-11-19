function bindmobilecvstyle() 
{
	// CV mobile globale layout ================================================ 
	$('#whole-page').attr('data-role', 'page');
	$('#navigator').attr('data-role', 'header');
	$('#langnavigator').attr('data-role', 'navbar');
	$('#contentnavigator').attr('data-role', 'navbar');
	$('#content').attr('data-role','content');
	$('#bottom-wrapper').attr('data-role','footer');
	
	// CV mobile globale style =================================================
	$('.xpdate').css({"float":"left"});
	$('.xpenterprise').css({"float":"right"});
	
	$('.xptechnolabel').css({"float":"left","margin-right":"2em"});
	$('.xptechnolist').css({"float":"left"});

	$('.clearfloatting').css({"clear":"both"});
	
	$('h2').attr('data-role','header') ; $('h2').attr('data-theme','b');

	//Skills styles =============================================================
	$('#skillstable').css({
		'align':'center'
		,'width':'90%'
		,'margin-left':'auto'
		,'margin-right':'auto'
		,'border-bottom':'1px solid'
		,'border-collapse':'collapse'
		,'border-color':'#A0A0A0'
	});
	$('td.cvskills').css({
		'border-left':'1px solid'
		,'border-right':'1px solid'
		,'border-color':'#A0A0A0'
	});
	
	$('p.skilllabel').attr('data-role','header') ; $('p.skilllabel').attr('data-theme','c');
	$('p.skilllabel').css({
		'margin-top':'0'
		,'padding-top':'0'
	}) ;
	
	//Experiences styles =============================================================
	$('.xpdatebar').attr('data-role','header') ; $('.xpdatebar').attr('data-theme','c');
	$('.xpdatebar').css({'padding':'0'});
	$('.xpdate').css({'margin':'0','padding':'0'});
	$('.xpenterprise').css({'margin':'0','padding':'0'});
	
	$('.xptechnobar').css({'font-weight':'bold'});
	
	$('.xpItem').attr('data-role','content'); $('.xpItem').attr('data-theme','c');
	
	
	//Education styles =============================================================
	$('#educationtable').css({
		'align':'center'
		,'margin-left':'auto'
		,'margin-right':'auto'
	});
	
	$('td.cveducation').css({'padding-left':'1em'});
	
	$('td.cveducation').attr('data-role','content'); $('td.cveducation').attr('data-theme','c');

	$('td.cveducationyear').attr('class','ui-bar ui-bar-d')  ;
}