$( document ).bind("pagebeforecreate", function(event) {
	
	reset_cv_mobistyle();
	
});

function reset_cv_mobistyle()
{
	var $cv_mobile_page = $('body').children('#cv');
	
	//$cv_mobile_page.find('div.cv').css({"background-color":"#0000FF"});//TODO debug
	
	// CV mobile globale style =================================================
	$cv_mobile_page.find('.xpdate').css({"float":"left"});
	$cv_mobile_page.find('.xpenterprise').css({"float":"right"});
	
	$cv_mobile_page.find('.xptechnolabel').css({"float":"left","margin-right":"2em"});
	$cv_mobile_page.find('.xptechnolist').css({"float":"left"});

	$cv_mobile_page.find('.clearfloatting').css({"clear":"both"});
	
	$cv_mobile_page.find('h2').attr('data-role','header') ; 
	$cv_mobile_page.find('h2').attr('data-theme','b');

	//Skills styles =============================================================
	$cv_mobile_page.find('#skillstable').css({
		'align':'center'
		,'width':'90%'
		,'margin-left':'auto'
		,'margin-right':'auto'
		,'border-bottom':'1px solid'
		,'border-collapse':'collapse'
		,'border-color':'#A0A0A0'
	});
	$cv_mobile_page.find('td.cvskills').css({
		'border-left':'1px solid'
		,'border-right':'1px solid'
		,'border-color':'#A0A0A0'
	});
	
	$cv_mobile_page.find('p.skilllabel').attr('data-role','header') ; 
	$cv_mobile_page.find('p.skilllabel').attr('data-theme','c');
	$cv_mobile_page.find('p.skilllabel').css({
		'margin-top':'0'
		,'padding-top':'0'
	}) ;
	
	//Experiences styles =============================================================
	$cv_mobile_page.find('.xpdatebar').attr('data-role','header') ; 
	$cv_mobile_page.find('.xpdatebar').attr('data-theme','c');
	$cv_mobile_page.find('.xpdatebar').css({'padding':'0'});
	$cv_mobile_page.find('.xpdate').css({'margin':'0','padding':'0'});
	$cv_mobile_page.find('.xpenterprise').css({'margin':'0','padding':'0'});
	
	$cv_mobile_page.find('.xptechnobar').css({'font-weight':'bold'});
	
	$cv_mobile_page.find('.xpItem').attr('data-role','content'); 
	$cv_mobile_page.find('.xpItem').attr('data-theme','c');
	
	
	//Education styles =============================================================
	$cv_mobile_page.find('#educationtable').css({
		'align':'center'
		,'margin-left':'auto'
		,'margin-right':'auto'
	});
	
	$cv_mobile_page.find('td.cveducation').css({'padding-left':'1em'});
	
	$cv_mobile_page.find('td.cveducation').attr('data-role','content'); 
	$cv_mobile_page.find('td.cveducation').attr('data-theme','c');

	$cv_mobile_page.find('td.cveducationyear').attr('class','ui-bar ui-bar-d')  ;

}