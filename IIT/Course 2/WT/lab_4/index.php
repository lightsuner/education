<?php

define('APP_PATH', __DIR__);

setlocale(LC_TIME, 'ru_RU');

require_once 'functions.php';


$siteConfig = parse_ini_file(pathTOSrc('config/main.cfg'));

$db = new Lab4DBManager(
    $siteConfig['host'],
    $siteConfig['port'],
    $siteConfig['database'],
    $siteConfig['username'],
    $siteConfig['password']
);

$layout = readTemplate('main');


$blocks = array(
    //'MAIN_MENU' => readTemplate('main_menu', buildMenuTree($db)),
    'MAIN_MENU' => menuRender(buildMenuTree($db)),
    'CONTENT' => readTemplate('blocks/content'),
    'NEWS' => readTemplate('blocks/news', $db->getLatestNews(4)),
    'COPYRIGHT' => readTemplate('blocks/copyright'),
    'ADDRESS' => readTemplate('blocks/address'),
);

$variables = array(
    'HEADER_TITLE' => 'Задание  3 - основы разработки сайтов',
    'HEADER_DESCRIPTION' => 'основы разработки сайтов',
    'HEADER_KEYWORDS' => 'ИИТ, Сайты, Разработка',
    'TODAY_D' => date('d'),
    'TODAY_M' => date('m'),
    'TODAY_Y' => date('Y'),
    'NOW_H' => date('H'),
    'NOW_M' => date('i'),
    'NOW_S' => date('s'),
    'MAIN_COLOR' => $siteConfig['main_color'],
    'COPYRIGHT_COLOR' => $siteConfig['copyright_color'],
);

echo prepareOutput($layout, $blocks, $variables);
