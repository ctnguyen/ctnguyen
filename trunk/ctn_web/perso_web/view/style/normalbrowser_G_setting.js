/* 
 * NORMAL BROWSER SETTING
 * 
 * This script aim to globally setting of the page for the normal web browser (non-mobile)
 *  1. set global layout, size and positionning divs () 
 *	                    page-wrapper     [non for mobile]
 *	                     top-wrapper     [non for mobile]
 *  	                 whole-page
 *	                      top-page        
 *		              sidebar     content
 *	                      bottom-page      
 *	                    bottom-wrapper   [different for mobile (included in the whole page instead of a wrapper)]
 *  2. set common styles for common blocs 
 *  3.  binding event 'click' to buttons 
 *  4. defining dynamic loading method when click event on a specific button is triggered
 *  
 */

// call initialization when document is loaded
$(document).ready(function() {
	initialize_normal_browser();
});


/** initilizse page
 * - set global layout
 * - bind click events
 * - bind specific reset style when a DOM is dynamically reloaded 
 */ 
function initialize_normal_browser()
{
	set_global_normal_layout();

	$("a.langbutton").live('click',function(event) {
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
		reset_page_footer_style();
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
//		,"border-right-style":"groove"
//		,"border-right-width":"5px"
//		,"border-right-color":"red"
	});
	
	reset_contentnavigator_style();

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

	reset_page_footer_style();

	debug_layout();
}

function reset_page_footer_style()
{
	$('#page-footer').css({		
		"font-size":"1em" 
		,"padding-top":"40px"
	});
}

function reset_contentnavigator_style()
{
	$('ul.navigatebutton').css({		
		"list-style-type":"none"
	});
}

/** action to do when a langbutton is clicked
 * - defining the actual state of the page (lang, content, isMobile) and 
 *   send request with the new lang to server
 * - reload the contentnavitagor adequate to the requested lang
 * - reload the same maincontent adequate to the requested lang
 * - reload the page-footer adequate to the requested lang 
 * - launch event 'divinnerreloaded' to the 'contentnavigator', 'maincontent' and 'bottom-wrapper' divs
 */
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


/** action to do when a navigationbutton is clicked
 * - defining the actual state of the page (lang, content, isMobile) and 
 *   send request with the new lang to server
 * - delete the specific style to the content, replace it by a new style in adequate to the new content
 * - reload the new maincontent 
 * - launch event 'divinnerreloaded' to the 'maincontent' div 
 */
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
		$('#maincontent').trigger('divinnerreloaded');

	});

	reset_actual_content_state(newcontentlabel);	
	//alert('new content label is '+ get_actual_content_state() ); //Debug
}


/** debuging the global layout by printing all principale blocs (div)
 */
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