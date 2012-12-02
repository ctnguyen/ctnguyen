$( document ).bind("pagebeforecreate", function(event) {
	
	reset_blacksholes_mobistyle();

});


function reset_blacksholes_mobistyle()
{
	var $BS_mobile_page = $('body').children('#BS');
	
	$BS_mobile_page.find('div.BS').css({"background-color":"#00FFFF"});//TODO debug
	
	$BS_mobile_page.find('h1.projectname').css({
		"text-align":"center"
		,"font-variant":"small-caps"
		,"font-family":"Georgia, 'Times New Roman', Times, serif"
	});
	
}