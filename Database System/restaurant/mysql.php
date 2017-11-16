<?php
/*链接到数据库*/
try{
    $pdo = new PDO('mysql:host=127.0.0.1;dbname=restaurantbooking;charset=utf8',
        'root', 'admin');
    $pdo->exec('set names utf8');
} catch (PDOException $e) {
    die('Could not connect: ' . $e);
}

?>