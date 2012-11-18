function bindmobilecvstyle() 
{
	//mobile global layout 
	$('#whole-page').attr('data-role', 'page');
	$('#navigator').attr('data-role', 'header');
	$('#contentnavigator').attr('data-role', 'navbar');
	$('#content').attr('data-role','content');
	$('#page-footer').attr('data-role','footer');
	
	
	// CV mobile style 
	$('.xpdate').css({"float":"left"});
	$('.xpenterprise').css({"float":"right"});
	
	$('.xptechnolabel').css({"float":"left","margin-right":"3em"});
	$('.xptechnolist').css({"float":"left"});

	$('.clearfloatting').css({"clear":"both"});

	
	$('h2').attr('data-role','header')          ; $('h2').attr('data-theme','b');
	$('.xpdatebar').attr('data-role','header')  ; $('.xpdatebar').attr('data-theme','c');
	$('.xptechnobar').attr('data-role','footer'); $('.xptechnobar').attr('data-theme','c');
	
	$('.xpItem').attr('data-role','content'); $('.xpItem').attr('data-theme','c');
	
}