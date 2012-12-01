$( document ).bind("pagebeforecreate", function(event) {
	
	reset_navierstocks_mobistyle();

});


function reset_navierstocks_mobistyle()
{
	var $NS_mobile_page = $('body').children('#NS');
	
	$NS_mobile_page.find('div.NS').css({"background-color":"#FFFF00"});//TODO debug
	
	$NS_mobile_page.find('img').css({
		"display":"block"
		,"margin-left":"auto"
		,"margin-right":"auto"
	});
	
	$NS_mobile_page.find('h1.projectname').css({
		"text-align":"center"
		,"font-variant":"small-caps"
		,"font-family":"Georgia, 'Times New Roman', Times, serif"
	});

}