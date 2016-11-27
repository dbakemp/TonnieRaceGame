<?php
if (!empty($_GET['id']))
{
    //MySqli Delete Query
    $results = $mysqli->query("DELETE FROM Ads WHERE ID=".$mysqli->real_escape_string($_GET['id']));

    if($results)
    {
        header("Location: index.php?page=dashboard&sub=manage");
    }
    else
    {
        print 'Error : ('. $mysqli->errno .') '. $mysqli->error;
    }
}
else
{
    header("Location: index.php?page=dashboard&sub=manage");
}


