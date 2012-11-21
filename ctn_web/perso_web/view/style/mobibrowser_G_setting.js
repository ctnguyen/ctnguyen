/* 
 * MOBILE BROWSER SETTING
 */

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
	$('#whole-page').attr('data-role', 'page');
	$('#navigator').attr('data-role', 'header');
	$('#langnavigator').attr('data-role', 'navbar');
	$('#contentnavigator').attr('data-role', 'navbar');
	$('#content').attr('data-role','content');
	$('#bottom-wrapper').attr('data-role','footer');
}


function update_langue(newlang)
{
	alert('actual lang is '+ get_actual_lang_state() ); //Debug
	
	reset_actual_lang_state(newlang);
	alert('new lang is '+ get_actual_lang_state() );    //Debug
}

function update_maincontent(newcontentlabel)
{
	alert('actual content is '+ get_actual_content_state() );    //Debug
	
	
	reset_actual_content_state(newcontentlabel);	
	alert('new content label is '+ get_actual_content_state() ); //Debug
}