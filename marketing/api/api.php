<?php

echo 'Welcome to api.';

$query = "SELECT * FROM Ads";

if ($result = $mysqli->query($query))
{

    /* fetch associative array */
    while ($row = $result->fetch_assoc())
    {
        $test[$row["ID"]]["Title"] = $row["Title"];
        $test[$row["ID"]]["URL"] = $row["URL"];
        $test[$row["ID"]]["ImageURL"] = $row["ImageURL"];
        $test[$row["ID"]]["Description"] = $row["Description"];
        $test[$row["ID"]]["IsActive"] = $row["IsActive"];
    }
}
