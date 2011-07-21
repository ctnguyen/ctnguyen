
/* reload all page when language(fr en vi) changed */
function ctn_reload(lang)
{	
	set_layout();
	_load_sidebar("fr");
	_load_content("fr", "home");		
	_load_footer("fr");
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
			$('#content').attr('class', contentLabel);
			
			//Replacing the local style of index page by the one newly loaded in the uriSideBar page
			$('#contentstyle').attr('href', $(loadedXHTML).contents().find('link#contentstyle').attr('href'));			
		  }
		  ,"xml"
         );	
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


function set_layout()
{
	$('body').css(
	{
		"margin":"0 0 0 0"
		,"padding":"0 0 0 0"
		,"background":"#FFFFFF"
		,"border":"1px solid #F0F8FF"////////
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
		,"border":"1px solid #D2691E"//////////
	});


	$('#top-page').css(
	{
		"margin":"0"
		,"padding":"0"
		,"clear":"both"
		,"border":"1px solid #808080"////////
	});

	$('#page').css(
	{
		"margin-top":"0"
		,"margin-bottom":"0"
		,"margin-right":"auto"
		,"margin-left":"auto"
		,"padding":" 0 0 0 0"
		,"width":" 70em"
		,"border":"1px solid #008000"///////////
	});

	$('#content').css(
	{
		"margin":" 0 0 0 0"
		,"padding":" 0 0 0 0"
		,"width":" 63%"
		,"float":"right"
		,"border":"1px solid #00BFFF"////////
	});

	$('#sidebar').css(
	{
		"margin":" 0 0 0 0"
		,"padding":" 0 0 0 0"
		,"width":" 33%"
		,"float":"left"
		,"border":"1px solid #0000FF"////////////////
	});

	$('#botton-page').css(
	{
		"margin":" 0"
		,"padding":" 0"
		,"clear":"both"
		,"border":"1px solid #808080"//////////
	});

	$('#page-footer').css(
	{
		"margin":" 0"
		,"padding":" 0"
		,"height":"100px"
		,"background":"#ffffff url(images/bottom_wraper.jpg) repeat-x"
		,"text-align":"center"
		//,"border":"1px solid #D2691E",/////////
	});
}


///////////////////////////   CTN TEST PLUGIN JQUERY    ///////////////////////
(function($){
	 
    $.fn.extend({
         
        //pass the options variable to the function
        ctn_background_gradient: function(options) {
 
 
            //Set the default values, use comma to separate the settings, example:
            var defaults = {
                color1    :'#000000' ,
                color2    :'#ffffff' ,
                direction :'vertical',
                steps     : 1,
            };
                 
            var options =  $.extend({},defaults, options);
 
            return this.each(function() {
                var o = options;
                var obj = $(this); 
                //code to be inserted here
                //you can access the value like this
                //var m_div = $( document.createElement('div') );
                //m_div.html("<h1>" + "color1 :" + o.color1 + "    color2 :" + o.color2 + "   direction :" + o.direction + "    steps :"+o.steps + "</h1>");
//                m_div.css("margin","0 0 0 0");
//                m_div.css("padding","0 0 0 0");
//                m_div.css("border","1px solid");;////////
//                m_div.css("border-color","#FF0000");//////
//                
//                var m_div2 = $( document.createElement('div') );
//                //m_div.html("<h1>" + "color1 :" + o.color1 + "    color2 :" + o.color2 + "   direction :" + o.direction + "    steps :"+o.steps + "</h1>");
//                m_div2.css("margin","0 0 0 0");
//                m_div2.css("padding","0 0 0 0");
//                m_div2.css("border","1px solid");;////////
//                m_div2.css("border-color","#FF0000");//////
//                
//                obj.append(m_div);
//                obj.append(m_div2);
                var parentHeight   = obj.innerHeight();
                var parentWidth    = obj.innerWidth();
                var parentPosition = obj.offset();

                var stepLenght   = parentHeight / o.steps ;
                obj.html("<h1>" + "parentHeight :" + parentHeight + "    parentWidth :" + parentWidth + "    stepLenght :" + stepLenght  
                		        + "   parentPosition.top :" + parentPosition.top + "    parentPosition.left :"+parentPosition.left+ "</h1>");
                
                for(var i=0;i<o.steps;i++) 
            	{
            		var m_div = $( document.createElement('div') );
                    m_div.css("margin","0 0 0 0");
                    m_div.css("padding","0 0 0 0");
                    m_div.css("height", stepLenght);
                    m_div.css("width", parentWidth);
                    m_div.css("position","absolute"); m_div.css("z-index","0"); 
                    var mdivtop = Math.round(parentPosition.top+i*stepLenght);
                    m_div.css("top",mdivtop + "px"); 
                    m_div.css("left","0");
                    m_div.css("border","1px solid");////////
                    m_div.css("border-color","#FF0000");//////
                    obj.append(m_div);
            	}
                
                
                

                //obj.html("<h1>" + "color1 :" + o.color1 + "    color2 :" + o.color2 + "   direction :" + o.direction + "    steps :"+o.steps + "</h1>");
             
            });
        }
    });
     
})(jQuery);
///////////////////////////   CTN TEST PLUGIN JQUERY    ///////////////////////