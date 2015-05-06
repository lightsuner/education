<?php

require_once 'database.php';

function pathTOSrc($path)
{
    return APP_PATH . '/' . $path;
}

function readTemplate($name, $data = null)
{
    ob_start();
    include(pathTOSrc('templates/' . $name . '.tpl'));
    $ret = ob_get_contents();
    ob_end_clean();

    return $ret;
}

function placeholdersPrepare($placeholders)
{
    foreach ($placeholders as &$value) {
        $value = '{' . $value . '}';
    }

    return $placeholders;
}

function prepareOutput($layout, $blocks, $variables)
{
    $output = str_replace(placeholdersPrepare(array_keys($blocks)), array_values($blocks), $layout);

    $output = str_replace(placeholdersPrepare(array_keys($variables)), array_values($variables), $output);

    return $output;
}

function buildMenuTree($db)
{
    $parentMenuItems = $db->getMenuElements();
    foreach ($parentMenuItems as &$menu) {
        menuTreeWalk($db, $menu);
    }

    return $parentMenuItems;
}

function menuTreeWalk($db, &$parentMenu)
{
    $children = $db->getMenuElements($parentMenu['id']);
    if (count($children)) {
        $parentMenu['children'] = & $children;
        foreach ($children as &$child) {
            menuTreeWalk($db, $child);
        }

    }
}

function menuRender($menuItems, $level = 0)
{
    $menuClass = 'mainmenu';
    if ($level) {
        $menuClass = 'mainmenuin' . $level;
    }
    $menu = '<ul class="'.$menuClass.'">';
    foreach ($menuItems as $menuItem) {
        $menu .= '<li><a href="#">'.$menuItem['title'].'</a>';
        if (!empty($menuItem['children'])) {
            $menu .= menuRender($menuItem['children'], $level+1);
        }
        $menu .= '</li>';
    }
    $menu .= '</ul>';

    return $menu;
}
