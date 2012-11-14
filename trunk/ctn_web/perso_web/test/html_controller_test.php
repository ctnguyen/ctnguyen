<?php
include '../controller/html_controller.php';

$html_en = new HtmlController('en');
echo $html_en->htmlcontent;

$html_fr = new HtmlController('fr');
echo $html_fr->htmlcontent;

$html_vn = new HtmlController('vn');
echo $html_vn->htmlcontent;

?>