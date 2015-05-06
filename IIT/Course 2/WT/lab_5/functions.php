<?php
/**
 * User: alkuk
 * Date: 04.05.15
 * Time: 21:13
 */

function printHeader($text)
{
    echo '<h2>'.$text.'</h2><br>';
}

function isValidEmail($email)
{
    $pattern = '/^([0-9a-zA-Z]+[-_.])*[0-9a-zA-Z]+@([0-9a-zA-Z-_]+[.])+[a-zA-Z]{2,8}$/';
    return preg_match($pattern, $email);
}

function checkEmails($emails)
{
    foreach ($emails as $email) {
        echo "Email: ".$email." => ";
        echo (isValidEmail($email) ? "<font color='green'>Корректен</font>" : "<font color='red'>Не корректен</font>");
        echo "<br>";
    }
}

function removeHTMLComments($html)
{
    $pattern = '/<!--((?!-->)(?!\[if.*ie.*\]).)*-->/is';
    return preg_replace($pattern, '', $html);
}

function removeHTMLTags($html)
{
    $pattern = '/<[^>]+>/is';
    return preg_replace($pattern, '', $html);
}
