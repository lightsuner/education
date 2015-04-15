<?php

function echoNewLine($string = '')
{
    echo '<b>' . $string . '</b>', '<br>';
}

function taskPrint($number)
{
    echoNewLine();
    echoNewLine('Задание ' . $number);
    echoNewLine();
}

header('Content-Type: text/html; charset=utf-8');


$cars = array(
    array(
        'Марка' => 'Peugeot',
        'Модели' => array(
            '207',
            '406',
            '307',
        ),
    ),
    array(
        'Марка' => 'Лада',
        'Модели' => array(
            'Калина',
            'Приора',
        ),
    )
);

#echo strlen('Машина');

echoNewLine('ЛР2 - Основы PHP');


// Task 1
taskPrint(1);

$intVar = 1;
$stringVar = 'Строка';
$floatVar = 10.3;
$boolVar = false;
$arrayVar = array(
    1,
    2,
    'строка',
    'key' => 'value'
);



echoNewLine('Целочисленная переменная $intVar:');
var_Dump($intVar);

echoNewLine('Строковая переменная $stringVar:');
var_Dump($stringVar);

echoNewLine('Дробная переменная $floatVar:');
var_Dump($floatVar);

echoNewLine('Логическая переменная $boolVar:');
var_Dump($boolVar);
echo "зднсь логич:";
echo $boolVar;
echo null;

echoNewLine('Массив $arrayVar:');
var_Dump($arrayVar);

// Task 2
$a = 555;
$b = 'ZZZ';

taskPrint(2);


echoNewLine('Складываем как числа:');
var_dump($a + $b);
echoNewLine();
echoNewLine('Складываем как строки:');
var_dump($a . $b);


// Task 3

taskPrint(3);

$employees = array(
    array(
        'name'  => 'Иванов',
        'phone' => '77-88-99',
        'email' => 'ivanov@domain.com',
        'cars' => array(
            'Peugeot - 207',
            'Alfa Romeo - Mito'
        )
    ),
    array(
        'name'  => 'Попов',
        'phone' => '66-55-44',
        'email' => 'petrov@domain.com',
        'cars' => array(
            'BMW - X5',
            'Citroen - C4'
        )
    ),
    array(
        'name'  => 'Сидоров',
        'phone' => '11-22-33',
        'email' => 'sidorov@domain.com',
        'cars' => array(
            'Fiat - Punto',
            'Kia - Avella'
        )

    )
);

var_dump($employees);


taskPrint(4);

$elements = array(
    1,
    2,
    "A",
    3.764,
    34,
    "B",
    12
);

echoNewLine('Исходный массив:');
var_dump($elements);
echoNewLine();
echoNewLine();

foreach ($elements as $key => $value) {
    if (!is_numeric($value)) {
        unset($elements[$key]);
    }
}

echoNewLine('Массив после фильтрации:');
var_dump($elements);
echoNewLine();
echoNewLine();

taskPrint(5);


?>
<table width="100%">
    <?php for ($i = 1; $i <= 1000; $i++): ?>
        <?php
        $hex = dechex($i % 256);
        $pad = str_pad($hex, 2, '0', STR_PAD_LEFT);
        $color = '#' . $pad . $pad . $pad;
        ?>
        <tr style="background-color: <?php echo $color ?> ">
            <td width="33%"><?php echo $i ?></td>
            <td width="33%">&nbsp;</td>
            <td width="33%">&nbsp;</td>
        </tr>
    <?php endfor ?>
</table>