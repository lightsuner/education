<?php

require_once 'boot.php';

$dateFormat = 'D, d M Y H:i:s O';

$rssFeed = '<?xml version="1.0" encoding="utf-8" ?>';
$rssFeed .= '<rss version="2.0">';
$rssFeed .= '<channel>';
$rssFeed .= '<title>Наши новости</title>';
$rssFeed .= '<link>http://iit-lab6.dev/rss.php</link>';
$rssFeed .= '<description>Самые свежие в мире новости у нас!</description>';
$rssFeed .= '<lastBuildDate>'.date($dateFormat).'</lastBuildDate>';


foreach ($db->getLatestNews() as $item) {
    $link = 'http://iit-lab6.dev/content/'.$item['id'];

    $rssFeed .= '<item>';
    $rssFeed .= '<title>'.$item['title'].' ('.date('Y/m/d', $item['created']).')</title>';
    $rssFeed .= '<link>'.$link.'</link>';
    $rssFeed .= '<description>'.$item['body'].'</description>';
    $rssFeed .= '<comments>'.$link.'/'.$item['id'].'#comments</comments>';
    $rssFeed .= '<pubDate>'.date($dateFormat, $item['created']).'</pubDate>';
    $rssFeed .= '<guid isPermaLink="true">'.$link.'</guid>';
    $rssFeed .= '</item>';
}

$rssFeed .= '</channel>';
$rssFeed .= '</rss>';

echo $rssFeed;
