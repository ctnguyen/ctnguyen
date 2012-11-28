$( document ).bind("pagebeforecreate", function(event) {
	
	reset_blacksholes_mobistyle();

});


function reset_blacksholes_mobistyle()
{
	$('div.BS').attr('data-role','button');
	$('h1.BS').css({"color":"#FF0000"});	
}