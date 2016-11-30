<?php

$query = "SELECT * FROM Ads";

if ($result = $mysqli->query($query))
{

    $char = array();


    $arr["Title"] = "Alice in Wonderland";
    $arr["Date"] = "1865";
    $arr["Ads"] = "";
    $toet = array();
    /* fetch associative array */
    while ($row = $result->fetch_assoc())
    {
        $test["Title"] = $row["Title"];
        $test["URL"] = $row["URL"];
        $test["ImageURL"] = $row["ImageURL"];
        $test["Description"] = $row["Description"];
        $test["IsActive"] = $row["IsActive"];
        $toet[] = $test;

    }

    $arr["Ads"] = $toet;
}
echo json_encode($arr);
//echo '<pre>';
//var_dump($arr);