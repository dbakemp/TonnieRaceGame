<?php
include_once 'includes/db_connect.php';
include_once 'includes/functions.php';

session_start();
?>
<?php if (login_check($mysqli) == true)
{
//    echo '
//    <p>Welcome' .htmlentities($_SESSION['username']) .'!</p>
//    <p>
//        This is an example protected page.  To access this page, users
//        must be logged in.  At some stage, well also check the role of
//        the user, so pages will be able to determine the type of user
//        authorised to access the page.
//    </p>
//    <p>Return to <a href="index.php">login page</a></p>
//    <p>Do you want to change user? <a href="includes/logout.php">Log out</a>.</p>';

    if (isset($sub))
    {
        if ($sub == "manage")
        {
            include 'admin/manage.php';
        }
        else if ($sub == "add")
        {
            include 'admin/add.php';
        }
        else if ($sub == "edit")
        {
            include 'admin/edit.php';
        }
        else if ($sub == "delete")
        {
            include 'admin/delete.php';
        }
        else
        {
            include 'admin/dashboard.php';
        }
    }
    else
    {
        include 'admin/dashboard.php';
    }
}
else
{
    header('Location: index.php?page=login');
}
?>

</body>
</html>