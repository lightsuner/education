<?php
header('Content-type: text/html; charset=utf-8');

require_once 'functions.php';

printHeader('Задание 1 - проверка email.');

$correctEmails = array(
    'vasya-pupkin@mail.com',
    'vasya_pupkin@mail.com',
    'vasya.pupkin@mail.com',
    'v.v.pupkin@firma.mail.com',
    'v.v.pupkin@firma-mail.com',
    'v.v.pupkin12@firma_mail.com',
    'v.v.pupkin-director@firma.mail.com',
);

$invalidEmails = array(
    '-vasya--pupkin@mail.com',
    'vasya_pupkin@mail..com',
    'vasya.-pupkin@mail.com',
    'v.v.pup kin@firma.mail.com',
    'v.v.pup#kin@firma-mail.com_',
);


checkEmails($correctEmails);
checkEmails($invalidEmails);


printHeader('Задание 2 - удаления html комментариев.');

$html = '
    Текст до комментариев
    <!-- comments-->    <!-- comments-->    <!-- comments-->
   <!--[if IE]>
     <link href="/css/invstroyIEfix.css" rel="stylesheet" type="text/css" />
    <![endif]-->
	<!-- бла бла бла --> <!-- фвафыва -->
    Текст после комментариев
';

printHeader('До:');
echo nl2br(htmlentities($html));
printHeader('После:');
echo nl2br(htmlentities(removeHTMLComments($html)));


printHeader('Задание 3 - Удалить html теги.');

$html = '
<a href="http://somegreatsite.com">Link Name</a>
is a link to another nifty site
<H1>This is a Header</H1>
<H2>This is a Medium Header</H2>
Send me mail at <a href="mailto:support@yourcompany.com">
support@yourcompany.com</a>.
<P> This is a new paragraph!
<P> <B>This is a new paragraph!</B>
<BR> <B><I>This is a new sentence without a paragraph break, in bold italics.</I></B>
';

printHeader('До:');
echo nl2br(htmlentities($html));

printHeader('После:');
echo nl2br(htmlentities(removeHTMLTags($html)));


printHeader('Задание 5 - Выделить слова которые больше 5 букв и написаны большими буквами.');

$pattern = '/\b[A-Z]{3,4}/s';
$text = "LOREM ipsum DOLOR SIT AMET, A consectetur adipiscing ELIT. Maecenas EFFICITUR justo justo, UT pharetra velit blandit at. nam vitae leo id nibh CONGUE feugiat. Duis IMPERDIET nunc elit, sed efficitur neque placerat in. Sed luctus magna eget sollicitudin semper. Curabitur quis efficitur libero, sed condimentum lectus.";

printHeader('До:');
echo $text;

printHeader('После:');
echo preg_replace(array(
    '/\b[A-Z]{5,}/s',
    '/\b[A-Z]{3,4}[^A-Z]/s',
), array(
    '<font color="red"><b>$0</b></font>',
    '<font color="green"><b>$0</b></font>',
), $text);

