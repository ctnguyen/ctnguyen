
/*
           whole-page
          page-header
             page
           top-page
      sidebar     content
         botton-page
          page-footer
*/


function resetLayout()
{
	$('#page-header').css({
		"height":"50px"
		,"background" : "#FFFFFF url(images/top_wrapper.jpg) repeat-x"
			});
	
	$('#page').css({
		"width":"71em"
		,"margin-left":"10em"
	    ,"margin-right":"auto"
	});
	$('#sidebar').css({
		"width":"20em"
		,"margin":"0 0 0 0"
	});
	$('#content').css({
		"width":"50em"
		,"margin":"0 0 0 0"		
	});
	
	$('#page-footer').css({
		"height":"50px"
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
	$('#content').css({"border":"1px solid #00BFFF"});
	$('#sidebar').css({"border":"1px solid #0000FF"});
	$('#botton-page').css({"border":"1px solid #808080"});
	$('#page-footer').css({"border":"1px solid #D2691E"});
	$('ul._sidebar.menu').css({"border":"1px solid black"});
}