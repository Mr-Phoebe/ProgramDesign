<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Restaurant Booking</title>
    <link rel="stylesheet" type="text/css" href="bs/css/bootstrap.min.css">
    <script src="bs/js/jquery-3.1.1.min.js"></script>
    <script src="bs/js/bootstrap.min.js"></script>
    <style>
        .input-group {
            margin-bottom: 10px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1 class="page-header">Restaurant Booking</h1>
        <form action='showrest.php' method='post'>
            <div class="row">
                <div class="col-md-4"></div>
                <div class="col-md-7" style="margin-bottom: 30px;">
                    <div class="input-group">
                        <span class="glyphicon glyphicon-user"></span>
                        <input name='username' type="text"
                               class="form-control" placeholder="Username" required>
                    </div>
                    <div class="input-group">
                        <span class="glyphicon glyphicon-tags"></span>
                        <input name='keyword' type="text"
                               class="form-control" placeholder="Keyword">
                    </div>
                    <div class="input-group">
                        <span class="glyphicon glyphicon-sort"></span>
                        <input name="numper" type="number" min="1"
                               class="form-control" value="1">
                    </div>
                    <div class="input-group">
                        <span class="glyphicon glyphicon-time"></span>
                        <input name = 'booktime' type="datetime-local"
                               class="form-control" value="2017-11-11T16:00:00"
                               step="3600" required>
                    </div>
                </div>
            </div>
            <div class="bs-docs-example">
                <div style="max-width: 400px; margin: 0 auto 10px;" class="well">
                    <button class="btn btn-large btn-block btn-primary" type="submit"
                        value="search">
                        Search
                    </button>
                    <button class="btn btn-large btn-block" type="reset"
                        value="reset">
                        Reset
                    </button>
                </div>
            </div>
        </form>
    </div>
</body>
</html>


