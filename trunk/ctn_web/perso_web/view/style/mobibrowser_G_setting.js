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

		var $page = $(pageSelector);
		var  $langnavigator   = $page.children("#langnavigator")
		     ,$contentnavigator = $page.children("#contentnavigator")
		     ,$navigator        = $page.children("#navigator")
		     ,$content          = $page.children("#maincontent")
		     ,$bottom_wrapper  = $page.children("#bottom-wrapper");

		$navigator.attr('data-role', 'header');
		$langnavigator.attr('data-role', 'navbar');	 
		$contentnavigator.attr('data-role', 'navbar');
		$content.attr('data-role','content');
		$bottom_wrapper.attr('data-role','footer');
		// Get the content area element for the page.
	}
	/*
	// mobile globale layout ================================================ 
	//$('#whole-page').attr('data-role', 'page');
	$('#langnavigator').attr('data-role', 'listview');	 //TODO find a appropriated style
	$('#contentnavigator').attr('data-role', 'listview');//TODO find a appropriated style
	$('#navigator').attr('data-role', 'header');
	$('#content').attr('data-role','content');
	$('#bottom-wrapper').attr('data-role','footer');*/
}

