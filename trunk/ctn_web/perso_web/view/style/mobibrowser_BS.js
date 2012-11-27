$( document ).bind("pagebeforecreate", function(event) {
	
	reset_blacksholes_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_blacksholes_mobistyle();
	});

});


function reset_blacksholes_mobistyle()
{
	$('div.BS').attr('data-role','button');
	$('h1').css({"color":"#FF0000"});	
}