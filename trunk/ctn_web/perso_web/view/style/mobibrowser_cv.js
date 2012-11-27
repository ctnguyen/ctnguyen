$( document ).bind("pagebeforecreate", function(event) {
	
	reset_cv_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_cv_mobistyle();
	});
	
});

function reset_cv_mobistyle()
{
	$('div.cv').attr('data-role','button');
	$('h1').css({"color":"#0000FF"});
}