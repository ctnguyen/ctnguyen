$(document).ready(function() {
	/* 		_cv_html = $.parseXML( 'html_fr/_cv_fr.html' );
	 _cv_content = _cv_html.find("content");
	 $( "div#content" ).append( $_cv_content.text() ); */

/*	$("div#content").load('html_fr/_cv_fr.html');
	$("#contentstyle").attr("href", "styles/_cv_style_1.css");*/
});

$(document).ready(function() {
	$("div#content").load("html_fr/_cv_fr.html  #content  div");
	$("#contentstyle").attr("href", "styles/_cv_style_1.css");


	$("div#sidebar").load("html_fr/_sidebar_fr.html  #sidebar  div");
	$("#sidebarstyle").attr("href", "styles/_sidebar_style_1.css");
	

	$("div#footer").html("<h1>" +"TOTO XML" +"</h1>");
	
	var xml = $.load("toto.xml");
	
/*	 		_cv_html = $.parseXML( 'toto.xml' );
	 _cv_content = _cv_html.find("content");
	 $( "div#sidebar" ).append( $_cv_content.text() ); */

});