function write_h1()
{
	document.write("<h1>This h1 is written by JavaScript</h1>");	
}

function _load_content()
{
	var xmlhttp;
	if (window.XMLHttpRequest)
	{// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
		document.write("<h1>This h1 is written by JavaScript</h1>");	
	}
	else
	{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		//document.write("<h1>This h1 is written by JavaScript</h1>");	
	}
	
	xmlhttp.onreadystatechange = function()
	{
		document.write("<h1>This h1 is written by JavaScript onreadystatechange</h1>");	
		document.getElementByTagName("body").innerHTML=xmlhttp.responseText;
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//document.getElementById("myDiv").innerHTML=xmlhttp.responseText;
			
		}
	};
	
	xmlhttp.open("GET","html_fr/_cv_fr.html",true);
	xmlhttp.send();
}