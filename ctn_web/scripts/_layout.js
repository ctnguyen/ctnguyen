
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
function _get_content_width(){return '75%';}

/* setting up bloc size and several style like border, backround..
 * contribute with styles/layout.css
 * */
function resetLayout()
{
	$('#page-header').css({
		"height":"100px"
		,"background" : "#FFFFFF url(images/top_wrapper.jpg) repeat-x"
			});
	
	$('#page').css({
		"width":_get_page_width()
		,"margin-left":"10em"
	    //,"margin-right":"auto"
	});
	$('#sidebar').css({
		"width":_get_sidebar_width()
		,"margin-right":"0"
		//,"border-right-style":"groove"
		//,"border-right-width":"5px"
		//,"border-right-color":"red"
	});
	$('#content').css({
		"width":_get_content_width()
		,"margin-left":"0"
		,"padding-left":"2em"
		,"border-left-style":"groove"
		,"border-left-width":"1px"
		,"border-left-color":"#000000"
	});
	
	$('#page-footer').css({
		"height":"100px"
		,"background" : "#FFFFFF url(images/bottom_wrapper.jpg) repeat-x"
	});
	//_debug_layout();
}



function _debug_layout()
{
	//plot border of all bloc
	//$('body').css({"border":"1px solid #ffffff"});
	$('#whole-page').css({"border":"1px solid #00FF00"});
	$('#page-header').css({"border":"1px solid #D2691E"});
	$('#top-page').css({"border":"1px solid #808080"});
	$('#page').css({"border":"1px solid #008000"});
	//$('#content').css({"border":"1px solid #00BFFF"});
	$('#sidebar').css({"border":"1px solid #0000FF"});
	$('#botton-page').css({"border":"1px solid #808080"});
	$('#page-footer').css({"border":"1px solid #D2691E"});
	$('ul._sidebar.menu').css({"border":"1px solid black"});
}