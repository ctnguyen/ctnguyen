$( document ).bind("pagebeforecreate", function(event) {
	
	reset_home_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_home_mobistyle();
	});

});

function reset_home_mobistyle()
{
	$('div.home').attr('data-role','button');
	$('h1').css({"color":"#FFFF00"});
}