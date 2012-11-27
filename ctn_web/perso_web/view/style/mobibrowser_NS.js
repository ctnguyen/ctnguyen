$( document ).bind("pagebeforecreate", function(event) {
	
	reset_navierstocks_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_home_style();
	});
});


function reset_navierstocks_mobistyle()
{
	$('div.NS').attr('data-role','button');
	$('h1.NS').css({"color":"#FFFF00"});
}