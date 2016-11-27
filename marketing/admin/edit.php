<?php

$title = "";
$url = "";
$imageURL = "";
$description = "";
$isActive = "";

if (!empty($_GET['id']))
{

    if ($_SERVER['REQUEST_METHOD'] == "POST")
    {

        $title = '"'.$mysqli->real_escape_string($_POST['title']).'"';
        $url = '"'.$mysqli->real_escape_string($_POST['url']).'"';
        $description = '"'.$mysqli->real_escape_string($_POST['omschrijving']).'"';
        $isActive = 0;
        if (!empty($_POST['active']) && $_POST['active'] == 'Yes')
        {
            $isActive = 1;
        }

        if (!empty($_FILES['fileToUpload']['name']))
        {

            $target_dir = "uploads/";

            $ext = pathinfo($_FILES["fileToUpload"]["name"], PATHINFO_EXTENSION);

            $target_file = $target_dir . date("YmdHms") .".". $ext;

            $uploadOk = 1;
            $imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
            // Check if image file is a actual image or fake image
            if(isset($_POST["submit"])) {
                $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
                if($check !== false) {
                    echo "File is an image - " . $check["mime"] . ".";
                    $uploadOk = 1;
                } else {
                    echo "File is not an image.";
                    $uploadOk = 0;
                }
            }
            // Check if file already exists
            if (file_exists($target_file)) {
                echo "Sorry, file already exists.";
                $uploadOk = 0;
            }
            // Check file size
            if ($_FILES["fileToUpload"]["size"] > 500000) {
                echo "Sorry, your file is too large.";
                $uploadOk = 0;
            }
                // Allow certain file formats
            if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
                && $imageFileType != "gif" ) {
                echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
                $uploadOk = 0;
            }
            // Check if $uploadOk is set to 0 by an error
            if ($uploadOk == 0) {
                echo "Sorry, your file was not uploaded.";
            // if everything is ok, try to upload file
            } else {
                if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {

                    $fileName = $target_file;

                    $imageURL = '"'.$mysqli->real_escape_string($fileName).'"';

                    $results = $mysqli->query("UPDATE Ads SET Title=".$title.", URL=".$url.", Description=".$description.", IsActive=".$isActive.", ImageURL=".$imageURL." WHERE ID=".$_GET['id']);

                    if($results){
                        header("Location: index.php?page=dashboard&sub=manage");
                    }else{
                        print 'Error : ('. $mysqli->errno .') '. $mysqli->error;
                    }


                } else {
                    echo "Sorry, there was an error uploading your file.";
                }
            }
        }
        else
            {
            $results = $mysqli->query("UPDATE Ads SET Title=" . $title . ", URL=" . $url . ", Description=" . $description . ", IsActive=" . $isActive . " WHERE ID=" . $_GET['id']);

            if ($results) {
                header("Location: index.php?page=dashboard&sub=manage");
            } else {
                print 'Error : (' . $mysqli->errno . ') ' . $mysqli->error;
            }
        }
    }
    else
    {
        $results = $mysqli->query("SELECT title, url, imageurl, description, isactive FROM Ads WHERE id = " . $mysqli->real_escape_string($_GET['id']));
        while ($row = $results->fetch_object())
        {
            $title = $row->title;
            $url = $row->url;
            $imageURL = $row->imageurl;
            $description = $row->description;
            $isActive = $row->isactive;

            if ($isActive == 1)
            {
                $isActive = "checked";
            }
        }
    }
}
else
{
    header("Location: index.php?page=dashboard&sub=manage");
}
?>

<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Tonnie's grote racewereld - Admin</title>

    <!-- Bootstrap Core CSS -->
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- MetisMenu CSS -->
    <link href="vendor/metisMenu/metisMenu.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="dist/css/sb-admin-2.css" rel="stylesheet">

    <!-- Morris Charts CSS -->
    <link href="vendor/morrisjs/morris.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
    <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

<div id="wrapper">

    <!-- Navigation -->
    <nav class="navbar navbar-default navbar-static-top" role="navigation" style="margin-bottom: 0">
        <div class="navbar-header">
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
            <a class="navbar-brand" href="index.html">Tonnie's grote racewereld - Admin</a>
        </div>
        <!-- /.navbar-header -->

        <ul class="nav navbar-top-links navbar-right">

            <li class="dropdown">
                <a class="dropdown-toggle" data-toggle="dropdown" href="#">
                    <i class="fa fa-user fa-fw"></i> <i class="fa fa-caret-down"></i>
                </a>
                <ul class="dropdown-menu dropdown-user">
                    <li><a href="#"><i class="fa fa-user fa-fw"></i> User Profile</a>
                    </li>
                    <li><a href="#"><i class="fa fa-gear fa-fw"></i> Settings</a>
                    </li>
                    <li class="divider"></li>
                    <li><a href="index.php?page=logout"><i class="fa fa-sign-out fa-fw"></i> Logout</a>
                    </li>
                </ul>
                <!-- /.dropdown-user -->
            </li>
            <!-- /.dropdown -->
        </ul>
        <!-- /.navbar-top-links -->

        <div class="navbar-default sidebar" role="navigation">
            <div class="sidebar-nav navbar-collapse">
                <ul class="nav" id="side-menu">

                    <li>
                        <a href="index.php?page=dashboard"><i class="fa fa-dashboard fa-fw"></i> Dashboard</a>
                    </li>
                    <li>
                        <a href="#"><i class="fa fa-bar-chart-o fa-fw"></i> Advertenties<span class="fa arrow"></span></a>
                        <ul class="nav nav-second-level">
                            <li>
                                <a href="index.php?page=dashboard&sub=manage">Advertenties beheren</a>
                            </li>
                            <li>
                                <a href="index.php?page=dashboard&sub=add">Advertentie toevoegen</a>
                            </li>
                        </ul>
                        <!-- /.nav-second-level -->
                    </li>
                </ul>
            </div>
            <!-- /.sidebar-collapse -->
        </div>
        <!-- /.navbar-static-side -->
    </nav>


    <div id="page-wrapper">
        <div class="row">
            <div class="col-lg-12">
                <h1 class="page-header">Advertentie aanpassen</h1>
            </div>
            <!-- /.col-lg-12 -->
        </div>
        <!-- /.row -->
        <div class="row">
            <div class="col-lg-12">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        Advertentie toevoegen
                    </div>
                    <div class="panel-body">
                        <div class="row">
                            <div class="col-lg-6">
                                <form role="form" method="POST" action="#" enctype="multipart/form-data">
                                    <div class="form-group">
                                        <label>Titel van de advertentie</label>
                                        <input class="form-control" name="title" value="<?php echo $title; ?>">
                                        <p class="help-block">Voeg hier een titel voor uw advertentie toe.</p>
                                    </div>
                                    <div class="form-group">
                                        <label>URL voor de advertentie</label>
                                        <input class="form-control" name="url" value="<?php echo $url; ?>">
                                        <p class="help-block">Voeg hier de URL toe waar de bezoeker heen moet worden gestuurd.</p>
                                    </div>
                                    <div class="form-group">
                                        <label>Afbeelding vervangen</label>
                                        <input type="file" name="fileToUpload" value="<?php echo $imageURL; ?>">
                                        <p class="help-block">Kies hier een nieuwe afbeelding als de orginele afbeelding moet worden vervangen.</p>
                                    </div>
                                    <div class="form-group">
                                        <label>Omschrijving advertentie</label>
                                        <textarea class="form-control" rows="3" name="omschrijving"><?php echo $description; ?></textarea>
                                        <p class="help-block">Geef hier een korte omschrijving van de advertentie.</p>
                                    </div>
                                    <div class="form-group">
                                        <label>Opties</label>
                                        <div class="checkbox">
                                            <label>
                                                <input type="checkbox" value="Yes" name="active" <?php echo $isActive; ?>>Maak advertentie actief.
                                            </label>
                                            <p class="help-block">Vink dit aan om de advertentie weer te geven in Tonnie's grote racewereld.</p>
                                        </div>
                                    </div>


                                    <button type="submit" class="btn btn-default">Advertentie bijwerken</button>
                                    <button type="reset" class="btn btn-default">Velden leegmaken</button>
                                </form>
                            </div>
                            <!-- /.col-lg-6 (nested) -->
                            <div class="col-lg-6">
                                <h1>Voorbeeld van de advertentie:</h1>
                                <img src="<?php echo $imageURL; ?>" width="200"  />

                            </div>
                            <!-- /.col-lg-6 (nested) -->
                        </div>
                        <!-- /.row (nested) -->
                    </div>
                    <!-- /.panel-body -->
                </div>
                <!-- /.panel -->
            </div>
            <!-- /.col-lg-12 -->
        </div>
        <!-- /.row -->
    </div>
    <!-- /#page-wrapper -->

</div>
<!-- /#wrapper -->

<!-- jQuery -->
<script src="vendor/jquery/jquery.min.js"></script>

<!-- Bootstrap Core JavaScript -->
<script src="vendor/bootstrap/js/bootstrap.min.js"></script>

<!-- Metis Menu Plugin JavaScript -->
<script src="vendor/metisMenu/metisMenu.min.js"></script>

<!-- Morris Charts JavaScript -->
<script src="vendor/raphael/raphael.min.js"></script>
<script src="vendor/morrisjs/morris.min.js"></script>
<script src="data/morris-data.js"></script>

<!-- Custom Theme JavaScript -->
<script src="dist/js/sb-admin-2.js"></script>

</body>

</html>
