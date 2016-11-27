<?php
include_once 'includes/db_connect.php';
include_once 'includes/functions.php';

if (isset($_GET['page']))
{
    if ($_GET['page'] == "login")
    {
        include_once 'login.php';
    }
    else if ($_GET['page'] == "dashboard")
    {
        $sub = "";
        if (isset($_GET['sub']))
        {
            if ($_GET['sub'] == "manage")
            {
                $sub = "manage";
            }
            else if ($_GET['sub'] == "add")
            {
                $sub = "add";
            }
            else if ($_GET['sub'] == "edit")
            {
                $sub = "edit";
            }
            else if ($_GET['sub'] == "delete")
            {
                $sub = "delete";
            }
        }

        include_once 'protected_page.php';

    }
    else if ($_GET['page'] == "register")
    {
        include_once 'register.php';
    }
    else if ($_GET['page'] == "register_success")
    {
        include_once 'register_success.php';
    }
    else if ($_GET['page'] == "logout")
    {
        include_once 'includes/logout.php';
    }
    else if ($_GET['page'] == "api")
    {
        include_once 'api/api.php';
    }
    else
    {
        include_once 'login.php';
    }
}
else if (isset($_GET['error']))
{
    if ($_GET['error'] == "login")
    {
        $error = "login";
        include 'login.php';
    }
    else
    {
        echo 'ERROR: UNKNOWN ERROR.';
    }
}
else
{
    include_once 'login.php';
}