$(document).bind("mobileinit", function(){
  alert('mobileinit fire off');
});

$( document ).bind("pagebeforecreate", function(event) {
	alert('pagebeforecreate fire off');
	initialize_mobile_browser();
});


$( document ).bind("pagecreate", function() {
	alert('pagecreate fire off');
});


$( document ).bind("pageinit", function() {
	alert('pageinit fire off');
});

function initialize_mobile_browser()
{
	bindmobilestyle();
	alert('call of manually binding style');
}

function bindmobilestyle()
{
	//$('#whole-page').attr('data-role','page');
	$('#header').attr('data-role','header');
	$('#content').attr('data-role','content');
	$('#footer').attr('data-role','footer');
}