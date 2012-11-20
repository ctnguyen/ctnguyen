/* 
 * MOBILE SETTING
 */

$(document).ready(function(){
	set_global_layout();
});

/*
	page-wrapper     [non for mobile]
	 top-wrapper     [non for mobile]
  	whole-page
	 top-page        
sidebar     content
	 bottom-page      
	bottom-wrapper   [different for mobile (included in the whole page instead of a wrapper)]
 */

function set_global_layout()
{
	// mobile globale layout ================================================ 
	$('#whole-page').attr('data-role', 'page');
	$('#navigator').attr('data-role', 'header');
	$('#langnavigator').attr('data-role', 'navbar');
	$('#contentnavigator').attr('data-role', 'navbar');
	$('#content').attr('data-role','content');
	$('#bottom-wrapper').attr('data-role','footer');
}