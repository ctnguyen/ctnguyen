/* 
 * MOBILE BROWSER SETTING
 */

// Binding 'pagebeforecreate' event on document for mobile is 
// someway equivalent of the usual 'ready' event on document use for normal browser



$( document ).bind("pagebeforecreate", function(event) {

	initialize_mobile_browser();

});



function initialize_mobile_browser()
{
	set_global_mobile_layout();
	
	// dynamically changing math content of the page
	// http://docs.mathjax.org/en/v1.1-latest/typeset.html
	MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
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
	
	nbPages = navigatorJSONDATA.length;
	//alert("number of pages = "+nbPages);
	for (var i = 0; i < nbPages ; i++) {
		pageSelector = "#" + navigatorJSONDATA[i].pageID;
		//alert("page ["+i+"] name is "+ pageSelector);

		var $page = $('body').children(pageSelector);
		var $navigator        = $page.children("#navigator");
		var $langnavigator    = $navigator.children("#langnavigator");
		var $contentnavigator = $navigator.children("#contentnavigator");
		var $content          = $page.children("#maincontent");
		var $bottom_wrapper   = $page.children("#bottom-wrapper");

		$navigator.attr(       'data-role', 'header');
		$langnavigator.attr(   'data-role', 'navbar');	 
		$contentnavigator.attr('data-role', 'navbar');
		$content.attr(         'data-role','content');
		$bottom_wrapper.attr(  'data-role','footer');
	}
	
	$('.referencing').css({ "display":"none" });
}


//TODO debug when change lang button does not behave as desire
//Listen for any attempts to call changePage().
/*
$(document).bind("pagebeforechange", function(e, data) {

	if ( typeof data.toPage === "string") {

		var u = $.mobile.path.parseUrl(data.toPage);

		//window.location.href = 'http://localhost/index.php';
	//		alert("document.pagebeforechange is fired off");
			
	//		$.mobile.changePage(u.hrefNoHash);

	//		e.preventDefault();
	}
});
*/