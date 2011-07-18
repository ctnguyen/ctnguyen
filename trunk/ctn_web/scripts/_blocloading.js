$(document).ready(function() {
	/* 		_cv_html = $.parseXML( 'html_fr/_cv_fr.html' );
	 _cv_content = _cv_html.find("content");
	 $( "div#content" ).append( $_cv_content.text() ); */


});

$(document).ready(function() {

	_load_sidebar("fr" , "_sidebar.html" , "_sidebar_style.css" );
	_load_content("fr" ,      "_cv.html" ,      "_cv_style.css" );	
	setting_blocsize();
	
	$("div#page-footer").html("<h1>" +"Here putting footer of page" +"</h1>");

	$("#page-footer").animateHighlight();

	//$("div#page-footer").gradienter({color_start: 'FE3627', color_end: '590512'});
});


function _load_content(lang, htmlfilepath, stylefilepath )
{
	
	//$("div#content").load("html_fr/_cv.html  #content  div");
	//$("#contentstyle").attr("href", "styles/_cv_style_1.css");
	
	var htmlfolder = "html_" + lang + "/";// html_fr/, html_en/, html_vn/
	var divId      = " #content div";
	$("div#content").load(htmlfolder + htmlfilepath + divId);
	
	var stylepath  = "styles/" + stylefilepath;
	$("#contentstyle").attr("href", stylepath);
}

function _load_sidebar(lang, htmlfilepath, stylefilepath )
{
//	$("div#sidebar").load("html_fr/_sidebar.html  #sidebar  div");
//	$("#sidebarstyle").attr("href", "styles/_sidebar_style.css");
	
	var htmlfolder = "html_" + lang + "/";// html_fr/, html_en/, html_vn/
	var divId      = " #sidebar div";
	$("div#sidebar").load(htmlfolder + htmlfilepath + divId);
	
	var stylepath  = "styles/" + stylefilepath;
	$("#sidebarstyle").attr("href", stylepath);
}



function setting_blocsize()
{
	$('body').css("background","#F0F8FF");
	$('body').css("border-style","solid");////////
	$('body').css("border-color","#F0F8FF");//////
	
	
	$('#page-header').css("margin","0");
	$('#page-header').css("padding","0");
	$('#page-header').css("height","8em");
	$('#page-header').css("border-style","solid");////////
	$('#page-header').css("border-color","#D2691E");//////
	
	
	$('#top-page').css("margin","0");
	$('#top-page').css("padding","0");
	$('#top-page').css("clear","both");
	$('#top-page').css("border-style","solid");////////
	$('#top-page').css("border-color","#808080");//////
	
	$('#page').css("margin-top","0");
	$('#page').css("margin-bottom","0");
	$('#page').css("margin-right","auto");
	$('#page').css("margin-left","auto");
	$('#page').css("padding"," 0 0 0 0");
	$('#page').css("width"," 70em");
	$('#page').css("border-style","solid");///////////
	$('#page').css("border-color"," #008000");///////


	$('#content').css("margin"," 0 0 0 0");
	$('#content').css("padding"," 0 0 0 0");
	$('#content').css("width"," 60%");
	$('#content').css("float","right");
	$('#content').css("border-style","solid");////////
	$('#content').css("border-color"," #00BFFF");/////////
	

	$('#sidebar').css("margin"," 0 0 0 0");
	$('#sidebar').css("padding"," 0 0 0 0");
	$('#sidebar').css("width"," 30%");
	$('#sidebar').css("float","left");
	$('#sidebar').css("border-style","solid");////////////////
	$('#sidebar').css("border-color"," #0000FF");////////////////
	
	
	$('#botton-page').css("margin"," 0");
	$('#botton-page').css("padding"," 0");
	$('#botton-page').css("clear","both");
	$('#botton-page').css("border-style","solid");//////////
	$('#botton-page').css("border-color"," #808080");//////

	$('#page-footer').css("margin"," 0");
	$('#page-footer').css("padding"," 0");
	$('#page-footer').css("height","8em");
	$('#page-footer').css("border-style","solid");/////////
	$('#page-footer').css("border-color"," #D2691E");////////
}