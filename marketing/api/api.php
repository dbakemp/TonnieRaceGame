<?php

$query = "SELECT * FROM Ads";

if ($result = $mysqli->query($query))
{

    $char = array();


    $arr["book"] = "Alice in Wonderland";
    $arr["year"] = "1865";
    $arr["characters"] = "";


    /* fetch associative array */
    while ($row = $result->fetch_assoc())
    {
        $arr[$row["ID"]]["Title"] = $row["Title"];
        $arr[$row["ID"]]["URL"] = $row["URL"];
        $arr[$row["ID"]]["ImageURL"] = $row["ImageURL"];
        $arr[$row["ID"]]["Description"] = $row["Description"];
        $arr[$row["ID"]]["IsActive"] = $row["IsActive"];
    }
}

//echo '<pre>';
//var_dump($arr);