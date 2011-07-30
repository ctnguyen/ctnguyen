$(document).ready(function() {
	ctn_reload(get_lang());		
	
});


/* reload all page when language(fr en vi) changed */
function ctn_reload(lang)
{	

	
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

	
//	$('img').bind('load', function() {
//		alert('loaded image : ' + $(this).attr('src'));
//	});
	
//    $('img').each(function() {
//		alert('loaded image : ' +  $(this).attr('src'));
//		//$(this).show();
//	}
//	);
    

    
//    $('img').each(function() {
//		alert('loaded image : ' + $(this).attr('src'));
//	}
//	);
	
	resetLayout();
	
	//_debug_windows_size();
	//_debug_browser_fontsize();
	_debug_lang();	
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
    
    $.ajax({
        type: "GET",
        url: uriContent,
        cache: false,    // or set to false
        dataType: "xml",
        async: false,
        success: function(loadedXHTML) {
        	
    		//Replacing the div#sidebar of index page  by the one newly loaded in the uriSideBar page
			$('#content').empty().html( $(loadedXHTML).contents().find('div#content').html() );
			
			//Replacing the local style of index page by the one newly loaded in the uriSideBar page
			$('#contentstyle').attr('href', $(loadedXHTML).contents().find('link#contentstyle').attr('href'));
        }
    });

    
    $('#content').removeClass($('#content').attr('class') );
    $('#content').addClass(contentLabel);  
    //_debug_content_label();
}

/* loading the sidebar block in function of language
 * 
 * */
function _load_sidebar(lang)
{	
	var htmlfolder = "html_" + lang + "/";
	var uriSideBar = htmlfolder + "_sidebar.html";
    
    $.ajax({
        type: "GET",
        url: uriSideBar,
        cache: false,    // or set to false
        dataType: "xml",
        async: false,
        success: function(loadedXHTML) {
        	
    		//Replacing the div#sidebar of index page  by the one newly loaded in the uriSideBar page
			$('#sidebar').html( $(loadedXHTML).contents().find('div#sidebar').html() );
			
			//Replacing the local style of index page by the one newly loaded in the uriSideBar page
			$('#sidebarstyle').attr('href', $(loadedXHTML).contents().find('link#sidebarstyle').attr('href'));			
		  }        
    }); 
    
	$('a.itemNavigate').click(function(event) {
		  event.preventDefault();
			var contentLabel = $(this).attr('id');
			_load_content(get_lang(), contentLabel);
	});
}


function _load_footer(lang)
{
	var _date = new Date();
	var _year = _date .getFullYear();
	var _footertext = "Chi-Thanh NGUYEN &copy; " + _year;	

	if (lang=="fr")
	{
		_footertext +=" Français";
	}
	if (lang=="us")
	{
		_footertext +=" English";
	}
	if (lang=="vn")
	{
		_footertext +=" Tiếng Việt";
	}	
	$("#page-footer").html("<h1 class='footer'>" +_footertext +"</h1>");	
}




function convertToEm(value_px)
{
	//the defautl font-size of body is in pixel and is 1 em
	var px_value_by_1em = parseFloat($("body").css("font-size"));
	return value_px / px_value_by_1em;
}
function convertToPx(value_em)
{
	//the defautl font-size of body is in pixel and is 1 em
	var px_value_by_1em = parseFloat($("body").css("font-size"));
	return value_em*px_value_by_1em;	
}


function get_lang()
{
	return $("p#actuallang").text();
}

function set_lang(_lang)
{
	$("p#actuallang").html(_lang);
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


function _debug_lang()
{
	$('p#actuallang').css({'display':'inherit'});
	//plot lang
	//var m_lang = get_lang();
	//$('#page-header').html('<h1>'+m_lang+'</h1>');
}

function _debug_content_label()
{
	 $('#page-header').html('<h1>' + $('#content').attr('class') + '</h1>');
}