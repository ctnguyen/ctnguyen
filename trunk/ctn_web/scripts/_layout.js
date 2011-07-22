
/* reload all page when language(fr en vi) changed */
function ctn_reload(lang)
{	
	resetLayout();
	_load_sidebar(lang);
	
	var actualcontent = '';//defining the actual Label as string
	actualcontent +=$('#content').attr('class');
	if(actualcontent === 'undefined' || actualcontent ==='' )
	{
		_load_content(lang, 'home');
	}
	else
	{
		_load_content(lang, actualcontent);
	}	
	
	_load_footer(lang);	

	
	_debug_layout();
	//_debug_windows_size();
	//_debug_browser_fontsize();
	//_debug_lang();
    _debug_content_class();
	
}



/* loading the content block in function of language and the content label
 * 
 * */
function _load_content(lang, contentLabel)
{	

// lang allow to determine the html folder in form             html_'lang'
// content label allow to determine 
//            the html filename               _'Label'.html
//   path = html_'lang'  +   _'Label'.html

	var htmlfolder = "html_" + lang + "/";
	var uriContent = htmlfolder + "_"+contentLabel+".html";
    $.get(uriContent
		  ,function(loadedXHTML){
    		
    		//Replacing the div#sidebar of index page  by the one newly loaded in the uriSideBar page
			$('#content').html( $(loadedXHTML).contents().find('div#content').html() );
			
			//Replacing the local style of index page by the one newly loaded in the uriSideBar page
			$('#contentstyle').attr('href', $(loadedXHTML).contents().find('link#contentstyle').attr('href'));			
		  }
		  ,"xml"
         );	

    $('#content').removeClass($('#content').attr('class') );
    $('#content').addClass(contentLabel);   
}

/* loading the sidebar block in function of language
 * 
 * */
function _load_sidebar(lang)
{	
	var htmlfolder = "html_" + lang + "/";
	var uriSideBar = htmlfolder + "_sidebar.html";
    $.get(uriSideBar
		  ,function(loadedXHTML){
    		
    		//Replacing the div#sidebar of index page  by the one newly loaded in the uriSideBar page
			$('#sidebar').html( $(loadedXHTML).contents().find('div#sidebar').html() );
			
			//Replacing the local style of index page by the one newly loaded in the uriSideBar page
			$('#sidebarstyle').attr('href', $(loadedXHTML).contents().find('link#sidebarstyle').attr('href'));			
		  }
		  ,"xml"
         );
}


function _load_footer(lang)
{
	var _date = new Date();
	var _year = _date .getFullYear();
	var _footertext = "<a href='mailto:chithanhnguyen.math@gmail.com'>Chi-Thanh NGUYEN</a> &copy; " + _year;	

	if (lang=="fr")
	{
		_footertext +=" Français";
	}
	if (lang=="en")
	{
		_footertext +=" English";
	}
	if (lang=="vi")
	{
		_footertext +=" Tiếng Việt";
	}	
	$("#page-footer").html("<h1 class='footer'>" +_footertext +"</h1>");	
}

function resetLayout()
{
	$('body').css(
	{
		"margin":"0 0 0 0"
		,"padding":"0 0 0 0"
		,"background":"#FFFFFF"
	});


	$('#whole-page').css(
	{
		"margin":"0 0 0 0"
		,"padding":"0 0 0 0"
	});

	$('#page-header').css(
	{
		"margin":"0 0 0 0"
		,"padding":"0 0 0 0"
		,"height":"100px"
		,"background": "#ffffff url(images/top_wraper.jpg) repeat-x"
	});


	$('#top-page').css(
	{
		"margin":"0"
		,"padding":"0"
		,"clear":"both"
	});

	$('#page').css(
	{
		"margin-top":"0"
		,"margin-bottom":"0"
		,"margin-right":"auto"
		,"margin-left":"auto"
		,"padding":" 0 0 0 0"
		,"width":" 70em"
	});

	$('#content').css(
	{
		"margin":" 0 0 0 0"
		,"padding":" 0 0 0 0"
		,"width":" 63%"
		,"float":"right"
	});

	$('#sidebar').css(
	{
		"margin":" 0 0 0 0"
		,"padding":" 0 0 0 0"
		,"width":" 33%"
		,"float":"left"
	});

	$('#botton-page').css(
	{
		"margin":" 0"
		,"padding":" 0"
		,"clear":"both"
	});

	$('#page-footer').css(
	{
		"margin":" 0"
		,"padding":" 0"
		,"height":"100px"
		,"background":"#ffffff url(images/bottom_wraper.jpg) repeat-x"
		,"text-align":"center"
	});
}



function _debug_browser_fontsize()
{
	var sizeinPx = parseFloat($("body").css("font-size"));
	$('#page-header').html("<h1>font-size : "+sizeinPx+"px = " 
			               +convertToEm(sizeinPx)+"em = "+convertToPx(convertToEm(sizeinPx))+ "px</h1>");
}

function _debug_windows_size()
{
	$(window).resize(function(){
		$('#page-header').html("<h1>windows width:"+$(window).width() + "     windows height:" + $(window).height()+"</h1>" );
		});	
}

function _debug_layout()
{
	//plot border of all bloc
	$('body').css({"border":"1px solid #F0F8FF"});
	$('#page-header').css({"border":"1px solid #D2691E"});
	$('#top-page').css({"border":"1px solid #808080"});
	$('#page').css({"border":"1px solid #008000"});
	$('#content').css({"border":"1px solid #00BFFF"});
	$('#sidebar').css({"border":"1px solid #0000FF"});
	$('#botton-page').css({"border":"1px solid #808080"});
	$('#page-footer').css({"border":"1px solid #D2691E"});
}

function _debug_lang()
{
	//plot lang
	var m_lang = get_lang();
	$('#page-header').html('<h1>'+m_lang+'</h1>');
}

function _debug_content_class()
{
	 $('#page-header').html('<h1>' + $('#content').attr('class') + '</h1>');
}
///////////////////////////   CTN TEST PLUGIN JQUERY    ///////////////////////