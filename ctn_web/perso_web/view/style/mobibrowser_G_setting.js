/* 
 * MOBILE BROWSER SETTING
 */
$( document ).bind( "pageinit", function(  ){

	// Let the framework know we're going to handle the load.
	//event.preventDefault();

	initialize_mobile_browser();
	
	//data.deferred.reject( data.absUrl, data.options );

});



function initialize_mobile_browser()
{
	set_global_mobile_layout();
	
	$("img.langbutton").live('click',function(event) {
		event.preventDefault();
		update_langue($(this).attr("id"));
	});
	
	$("a.navigatebutton").live('click',function(event) {
		event.preventDefault();
		update_maincontent($(this).attr("id"));
	});

	$("#contentnavigator").live('divinnerreloaded',function(event) {
		reset_contentnavigator_style();
	});
	
	$("#bottom-wrapper").live('divinnerreloaded',function(event) {
		reset_contentnavigator_style();
	});
}

/*
	page-wrapper     [non for mobile]
	 top-wrapper     [non for mobile]
  	whole-page
	 top-page        
sidebar     content
	 bottom-page      
	bottom-wrapper   [different for mobile (included in the whole page instead of a wrapper)]
 */

function set_global_mobile_layout()
{
	// mobile globale layout ================================================ 
	$('#langnavigator').attr('data-role', 'navbar');
	$('#contentnavigator').attr('data-role', 'navbar');
	$('#whole-page').attr('data-role', 'page');
	$('#navigator').attr('data-role', 'header');
	$('#content').attr('data-role','content');
	$('#bottom-wrapper').attr('data-role','footer');
}


function update_langue(newlang)
{
	//alert('actual lang is '+ get_actual_lang_state() ); //Debug

	var lang_request    = newlang;
	var content_request = get_actual_content_state();
	var isMobile_request= 'true';
	
	$.ajax({
		type: 'GET'
		,url : 'controller/ContentNavigatorRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedcontentnavigator ) {
		$('#contentnavigator').empty().html( loadedcontentnavigator );
		$('#contentnavigator').trigger('divinnerreloaded');
	});
	
	
	$.ajax({
		type: 'GET'
		,url : 'controller/MainContentRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedmaincontentdiv ) {
		
		$('#maincontent').empty().html(loadedmaincontentdiv);
		$('#maincontent').trigger('divinnerreloaded');
	});
	
	$.ajax({
		type: 'GET'
		,url : 'controller/PageFooterRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedfooterpage ) {
		$('#bottom-wrapper').empty().html( loadedfooterpage );
		$('#bottom-wrapper').trigger('divinnerreloaded');
	});
	
	reset_actual_lang_state(newlang);
	//alert('new lang is '+ get_actual_lang_state() );    //Debug
}

function update_maincontent(newcontentlabel)
{
	//alert('actual content is '+ get_actual_content_state() );    //Debug

	var lang_request    = get_actual_lang_state();
	var content_request = newcontentlabel;
	var isMobile_request= 'true';

	
	$.ajax({
		type: 'GET'
		,url : 'controller/SpecificStyleRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( specificstylescript ) {
		$('head .specificstyle').remove();
		$('head').append(specificstylescript);
	});
	
	
	$.ajax({
		type: 'GET'
		,url : 'controller/MainContentRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedmaincontentdiv ) {
		
		$('#maincontent').empty().html(loadedmaincontentdiv);
		$('#maincontent').trigger('divinnerreloaded');

	});

	reset_actual_content_state(newcontentlabel);	
	//alert('new content label is '+ get_actual_content_state() ); //Debug
}