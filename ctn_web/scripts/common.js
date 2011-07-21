
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
