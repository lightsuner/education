<?php

function pathTOSrc($path)
{
    return APP_PATH.'/'.$path;
}

function readTemplate($name)
{
    return file_get_contents(pathTOSrc('templates/'.$name.'.tpl'));
}

function placeholdersPrepare($placeholders)
{
    foreach ($placeholders as &$value) {
        $value = '{'.$value.'}';
    }

    return $placeholders;
}

function prepareOutput($layout, $blocks, $variables)
{
    $output = str_replace(
        placeholdersPrepare(array_keys($blocks)),
        array_values($blocks),
        $layout
    );

    $output = str_replace(
        placeholdersPrepare(array_keys($variables)),
        array_values($variables),
        $output
    );

    return $output;
}
