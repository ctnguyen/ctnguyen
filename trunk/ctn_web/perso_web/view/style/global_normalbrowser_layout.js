$(document).ready(function(){
	set_global_layout();
});

/*
	whole-page
	page-header
  		page
	top-page
sidebar     content
	botton-page
	page-footer
 */
function _get_page_width(){return '80em';}
function _get_sidebar_width(){return '22%';}
function _get_content_width(){return '70%';}

/* setting up bloc size and several style like border, backround..
 * contribute with styles/layout.css
 * */
function set_global_layout()
{
	/*
	$('#page-header').css({
		"height":"100px"
			,"background" : "#FFFFFF url(images/top_wrapper.jpg) repeat-x"
	});
	 */
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
//			,"border-right-style":"groove"
//			,"border-right-width":"5px"
//			,"border-right-color":"red"
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


	$('#botton-page').css({
		"margin":"0 0 0 0"
		,"padding":"0 0 0 0"
		,"clear":"both"
	});
	
	$('#footer').css({
		"height":"100px"
			,"font-size":"1em" 
				//,"background" : "#FFFFFF url(images/bottom_wrapper.jpg) repeat-x"
	});
	/*
	$('h1.footer').css({		
		"font-size":"1em" 
			,"padding-top":"40px"
	});
	*/
	debug_layout();
}

function debug_layout()
{
	//plot border of all bloc
	//$('body').css({"border":"1px solid #ffffff"});
	$('#whole-page').css({"border":"1px solid #00FF00"});
	//$('#page-header').css({"border":"1px solid #D2691E"});
	$('#top-page').css({"border":"1px solid #808080"});
	//$('#page').css({"border":"1px solid #008000"});
	$('#maincontent').css({"border":"1px solid #00BFFF"});
	$('#navigator').css({"border":"1px solid #0000FF"});
	$('#botton-page').css({"border":"1px solid #808080"});
	$('#footer').css({"border":"1px solid #D2691E"});
	//$('ul._sidebar.menu').css({"border":"1px solid black"});
}