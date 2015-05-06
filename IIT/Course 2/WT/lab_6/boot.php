<?php
/**
 * User: alkuk
 * Date: 04.05.15
 * Time: 23:51
 */

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
