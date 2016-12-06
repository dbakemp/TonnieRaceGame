<?php
if (isset($_GET['sub']))
{
    if ($_GET['sub'] == "ads")
    {
        $query = "SELECT * FROM ads";

        if ($result = $mysqli->query($query))
        {

            $char = array();


            $arr["Title"] = "Advertenties";
            $arr["Ads"] = "";
            $toet = array();
            /* fetch associative array */
            while ($row = $result->fetch_assoc())
            {
				$pieces = explode("/", $row["ImageURL"]);
				
                $test["Title"] = $row["Title"];
                $test["URL"] = $row["URL"];
                $test["ImageURL"] = "http://timmeehh.xyz/".$row["ImageURL"];
                $test["Description"] = $row["Description"];
                $test["IsActive"] = $row["IsActive"];
				$test["FileName"] = $pieces[1];
                $toet[] = $test;

            }

            $arr["Ads"] = $toet;
        }
        echo json_encode($arr);
    }
    else if ($_GET['sub'] == "highscores")
    {
        if (isset($_GET['action']) && $_GET['action'] == "read")
        {
            if (isset($_GET['level']))
            {
                $scoreArray = array();
                $query = "SELECT * FROM highscores WHERE level = '".$mysqli->real_escape_string($_GET['level'])."'";

                if ($result = $mysqli->query($query))
                {
                    while ($row = $result->fetch_assoc())
                    {
                        $score["Name"] = $row["Name"];
                        $score["Level"] = $row["Level"];
                        $score["Score"] = $row["Score"];
                        $score["InsertTime"] = $row["InsertTime"];
                        $score["InsertIP"] = $row["InsertIP"];
                        $scoreArray[] = $score;
                    }

                    echo json_encode($scoreArray);
                }
                else
                {
                    $arr["Error"] = "No scores available";
                    echo json_encode($arr);
                }
            }
            else
            {
                $arr["Error"] = "No level supplied.";
                echo json_encode($arr);
                die();
            }
        }
        if (isset($_GET['action']) && $_GET['action'] == "insert" && $_SERVER['REQUEST_METHOD'] == "POST")
        {
            //values to be inserted in database table
            $name = '"'.$mysqli->real_escape_string($_POST['Name']).'"';
            $level = '"'.$mysqli->real_escape_string($_POST['Level']).'"';
            $score = '"'.$mysqli->real_escape_string($_POST['Score']).'"';
            $ip = '"'.$mysqli->real_escape_string($_SERVER['REMOTE_ADDR']).'"';

            //MySqli Insert Query
            $insert_row = $mysqli->query("INSERT INTO highscores (Name, Level, Score, InsertIP) VALUES($name, $level, $score, $ip)");

            if($insert_row){
                $arr["Success"] = "true";
                echo json_encode($arr);

            }else{
                $arr["Error"] =$mysqli->error;
                echo json_encode($arr);
            }
        }
    }
    else
    {
        $arr["Error"] = "Invalid API usage";
        echo json_encode($arr);
    }
}
else
{
    $arr["Error"] = "Invalid API usage";
    echo json_encode($arr);
}