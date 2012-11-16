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
	$('#navigator').css({
		"width":_get_sidebar_width()
		,"margin-right":"0"
//			,"border-right-style":"groove"
//			,"border-right-width":"5px"
//			,"border-right-color":"red"
	});
	
	$('#maincontent').css({
		"width":_get_content_width()
		,"margin-right":"0"
			,"padding-left":"2em"
				,"border-left-style":"groove"
					,"border-left-width":"1px"
						,"border-left-color":"#000000"
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
//	_debug_layout();
}