$( document ).bind("pagebeforecreate", function(event) {
	
	reset_contact_mobistyle();
	
	$("#maincontent").live('divinnerreloaded',function(event) {
		reset_contact_mobistyle();
	});
});

function reset_contact_mobistyle()
{
	$('div.contact').attr('data-role','button');
	$('h1').css({"color":"#00FF00"});	
}