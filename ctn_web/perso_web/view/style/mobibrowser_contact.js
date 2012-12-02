$( document ).bind("pagebeforecreate", function(event) {
	
	reset_contact_mobistyle();
	
});

function reset_contact_mobistyle()
{
	
	var $contact_mobile_page = $('body').children('#contact');
	
	//$contact_mobile_page.find('div.contact').css({"background-color":"#0000FF"});//TODO debug

	$contact_mobile_page.find('ul.contact').css({
		"list-style-type":"none"
	});
}