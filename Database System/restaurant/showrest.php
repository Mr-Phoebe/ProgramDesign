<?php
/**
 * Created by PhpStorm.
 * User: lenovo
 * Date: 2017/11/9
 * Time: 21:21
 */

include "mysql.php";

$cname = $_POST['username'];
$keyword = $_POST['keyword'];
$number = $_POST['numper'];
$btime = $_POST['booktime'];

if(!empty($keyword)) {
    $sqlrest = "select * from restaurant where description like '%{$keyword}%' 
                and {$number} <= restaurant.capacity
                and rid not in (
                  select rid from restaurant as res natural join booking
                  where btime='{$btime}'
                  group by booking.rid
                  having sum(booking.quantity) + {$number} > restaurant.capacity
                )";

} else {
    $sqlrest = "select * from restaurant where description like '%{$keyword}%' 
                and {$number} <= restaurant.capacity
                and rid not in (
                  select rid from restaurant as res natural join booking
                  where btime='{$btime}'
                  group by booking.rid
                  having sum(booking.quantity) + {$number} > restaurant.capacity
                )";
}
echo $sqlrest;

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Restaurant Booking</title>
    <link rel="stylesheet" type="text/css" href="bs/css/bootstrap.min.css">
    <script src="bs/js/jquery-3.1.1.min.js"></script>
    <script src="bs/js/bootstrap.min.js"></script>
    <script type="text/javascript" language="javascript">
        function btnClick(n){
            location.href="bookrest.php?cname=<?php echo "{$cname}"; ?>&btime=<?php echo "{$btime}"; ?>&number=<?php echo "{$number}"; ?>&rid="+ n.value;

        }
    </script>
</head>
<body>
<div class="container">
    <table class="table table-striped table-hover table-bordered">
        <h1 class="page-header">customer table</h1>
        <tr>
            <th>restaurant</th>
            <th>description</th>
            <th>remain</th>
            <th>book</th>
        </tr>
        <?php
        if($smt = $pdo->query($sqlrest)){
            $rows = $smt->fetchAll(PDO::FETCH_ASSOC);
        } else {
            $rows = array();
            echo "<script>alert('Query Failure!')</script>";
        }
        foreach($rows as $row)
        {
            $remain = $row['capacity'] - $row['nowsum'];
            echo "<tr>";
            echo "<td>{$row['rname']}</td>";
            echo "<td>{$row['description']}</td>";
            echo "<td>{$remain}</td>";
            echo "<td>
                    <button class=\"btn btn-success\" onclick=\"btnClick(this);\" 
                    type=\"button\" value=\"{$row['rid']}\">Book it!</button></td>";
            echo "</tr>";
        }
        ?>
    </table>
</div>
</body>
</html>
