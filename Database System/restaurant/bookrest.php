<?php
/**
 * Created by PhpStorm.
 * User: lenovo
 * Date: 2017/11/11
 * Time: 22:22
 */

include "mysql.php";

$cname = $_GET['cname'];
$rid = $_GET['rid'];
$number = $_GET['number'];
$btime = $_GET['btime'];

$sqlc = "select * from customer where cname='{$cname}'";

if($smt = $pdo->query($sqlc)){
    $cinfo = $smt->fetch(PDO::FETCH_ASSOC);
} else {
    echo "<script>alert('No this User!')</script>";
}


$cid = $cinfo['cid'];

$addbook = "insert into booking(cid, rid, btime, quantity) values({$cid}, {$rid}, '{$btime}', '{$number}')";

if(!$pdo->exec($addbook)) {
    echo "<script>alert('Booking Failure!')</script>";
}

$sqlbook= "select * from restaurant natural join booking natural join customer where cid={$cid}";

?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Restaurant Booking</title>
    <link rel="stylesheet" type="text/css" href="bs/css/bootstrap.min.css">
    <script src="bs/js/jquery-3.1.1.min.js"></script>
    <script src="bs/js/bootstrap.min.js"></script>
</head>
<body>
<div class="container">
    <table class="table table-striped table-hover table-bordered">
        <h1 class="page-header">Customer Booking</h1>
        <tr>
            <th>rname</th>
            <th>cname</th>
            <th>btime</th>
            <th>quantity</th>
            <th>phone</th>
        </tr>
        <?php
        if($smt = $pdo->query($sqlbook)){
            $rows = $smt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            $rows = array();
            echo "<script>alert('Query Failure!')</script>";
        }
        foreach($rows as $row)
        {
            echo "<tr>";
            echo "<td>{$row['rname']}</td>";
            echo "<td>{$row['cname']}</td>";
            echo "<td>{$row['btime']}</td>";
            echo "<td>{$row['quantity']}</td>";
            echo "<td>{$row['phone']}</td>";
            echo "</tr>";

        }
        ?>
    </table>
    <div class="">
        <div style="max-width: 400px; margin: 0 auto 10px;" class="well">
            <a href="index.php">
            <button class="btn btn-large btn-block btn-warning" type=""
                    value="">
                Home
            </button>
            </a>
        </div>
    </div>
</div>
</body>
</html>

