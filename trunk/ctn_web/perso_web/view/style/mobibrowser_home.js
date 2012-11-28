$( document ).bind("pagebeforecreate", function(event) {
	
	reset_home_mobistyle();

});

function reset_home_mobistyle()
{
	var $home_mobile_page = $('body').children('#home');
	
	$home_mobile_page.find('div.home').css({"background-color":"#FFFF00"});//TODO debug
	
	$home_mobile_page.find('ul#motivations.home').css({
		"list-style-type":"square"
	});

	$home_mobile_page.find('ul#webtechnologies.home').css({
		"list-style-type":"none"
	});
}