<?php
/*链接到数据库*/
try{
    $pdo = new PDO('mysql:host=localhost;dbname=restaurantbooking;charset=utf8',
        'root', 'root');
    $pdo->exec('set names utf8');
} catch (PDOException $e) {
    die('Could not connect: ' . $e);
}

?>