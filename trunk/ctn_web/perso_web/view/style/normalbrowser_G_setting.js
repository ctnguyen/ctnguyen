/* 
 * NORMAL BROWSER SETTING
 */

$(document).ready(function() {
	initialize_normal_browser();
});


function initialize_normal_browser()
{
	set_global_normal_layout();

	$("img.langbutton").live('click',function(event) {
		event.preventDefault();
		update_langue($(this).attr("id"));
	});
	$("a.navigatebutton").live('click',function(event) {
		event.preventDefault();
		update_maincontent($(this).attr("id"));
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

//page width depend on how many character it has, so its convenient to set it in relation to em
function _get_page_width(){return '80em';}
function _get_sidebar_width(){return '22%';}
function _get_content_width(){return '70%';}

/* setting up bloc size and several style like border, backround..
 * contribute with styles/layout.css
 * */
function set_global_normal_layout()
{
	$('body').css({
		"margin":"0 0 0 0"
			,"padding":"0 0 0 0"
	});

	$('#page-wrapper').css({
		"margin":"0 0 0 0"
			,"padding":"0 0 0 0"
	});

	$('#top-wrapper').css({
		"height":"100px"
			,"width":$(window).width()
			,"margin":"0 0 0 0"
				,"padding":"0 0 0 0"
	});

	$('#whole-page').css({
		"width":_get_page_width()
		,"margin-left":"10em"
//			,"margin-right":"auto"
	});

	$('#top-page').css({
		"margin":"0 0 0 0"
			,"padding":"0 0 0 0"
				,"clear":"both"
	});

	$('#navigator').css({
		"width":_get_sidebar_width()
		,"margin-right":"0"
			,"float":"left"
//				,"border-right-style":"groove"
//				,"border-right-width":"5px"
//				,"border-right-color":"red"
	});

	$('#logo').css({
		"display":"block"
			,"width":"80%"
				,"margin-left":"auto"
					,"margin-right":"auto"
	});

	$('#maincontent').css({
		"width":_get_content_width()
		,"margin-right":"0"
			,"float":"right"
				,"border-left-style":"groove"
					,"border-left-width":"1px"
						,"border-left-color":"#000000"
	});


	$('#bottom-page').css({
		"margin":"0 0 0 0"
			,"padding":"0 0 0 0"
				,"clear":"both"
	});

	$('#bottom-wrapper').css({
		"height":"100px"
			,"width":$(window).width()
			,"font-size":"1em"
				,"margin":"0 0 0 0"
					,"padding":"0 0 0 0"
						,"text-align":"center"
							,"position":"fixed"
								,"bottom":"0px"
	});

	$('#page-footer').css({		
		"font-size":"1em" 
			,"padding-top":"40px"
	});

	debug_layout();
}

function debug_layout()
{
	//plot border of all bloc
	$('body').css({"border":"1px solid #ffffff"});
	$('#whole-page').css({"border":"1px solid #00FF00"});
	$('#top-page').css({"border":"1px solid #808080"});
	$('#maincontent').css({"border":"1px solid #00BFFF"});
	$('#navigator').css({"border":"1px solid #0000FF"});
	$('#bottom-page').css({"border":"1px solid #808080"});
	$('#bottom-wrapper').css({"border":"1px solid #D2691E"});
}


function update_langue(newlang)
{
	//alert('actual lang is '+ get_actual_lang_state() ); //Debug

	var lang_request    = newlang;
	var content_request = get_actual_content_state();
	var isMobile_request= 'false';
	
	$.ajax({
		type: 'GET'
		,url : 'controller/ContentNavigatorRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedcontentnavigator ) {
		$('#contentnavigator').empty().html( loadedcontentnavigator );
	});
	
	
	$.ajax({
		type: 'GET'
		,url : 'controller/MainContentRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedmaincontentdiv ) {
		
		$('#maincontent').empty().html(loadedmaincontentdiv);

	});
	
	$.ajax({
		type: 'GET'
		,url : 'controller/PageFooterRequest.php'
		,data:{'lang':lang_request,'content':content_request,'isMobile':isMobile_request}
		,dataType: 'html'
	}).done(function( loadedfooterpage ) {
		$('#bottom-wrapper').empty().html( loadedfooterpage );
	});
	
	reset_actual_lang_state(newlang);
	//alert('new lang is '+ get_actual_lang_state() );    //Debug
}

function update_maincontent(newcontentlabel)
{
	//alert('actual content is '+ get_actual_content_state() );    //Debug

	var lang_request    = get_actual_lang_state();
	var content_request = newcontentlabel;
	var isMobile_request= 'false';

	
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

	});

	reset_actual_content_state(newcontentlabel);	
	//alert('new content label is '+ get_actual_content_state() ); //Debug
}
