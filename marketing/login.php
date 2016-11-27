<?php
include_once 'includes/db_connect.php';
include_once 'includes/functions.php';
session_start();


if (login_check($mysqli) == true) {
    header('Location: index.php?page=dashboard');
} else {
    $logged = 'out';
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Secure Login: Log In</title>
    <link rel="stylesheet" href="css/style.css" />
    <link rel='stylesheet prefetch' href='http://maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css'>
    <script type="text/JavaScript" src="js/index.js"></script>
    <script type="text/JavaScript" src="js/sha512.js"></script>
    <script type="text/JavaScript" src="js/forms.js"></script>

</head>
<body>
<?php
//if (isset($_GET['error'])) {
//    echo '<p class="error">Error Logging In!</p>';
//}
//?>
<!--<form action="includes/process_login.php" method="post" name="login_form">-->
<!--    Email: <input type="text" name="email" />-->
<!--    Password: <input type="password"-->
<!--                     name="password"-->
<!--                     id="password"/>-->
<!--    <input type="button"-->
<!--           value="Login"-->
<!--           onclick="formhash(this.form, this.form.password);" />-->
<!--</form>-->
<form action="includes/process_login.php" method="post" name="login_form">
<div class="login-form">
    <h1><img src="images/logo.png" /></h1>
    <?php

    if (isset($error))
    {
        if ($error == 'login')
        {
            echo "<span id='alert'>Onbekende gegevens</span><br />&nbsp;";
        }
    }

    ?>
    <div class="form-group ">
        <input type="text" class="form-control" placeholder="E-mailadres " id="email" name="email">
        <i class="fa fa-user"></i>
    </div>
    <div class="form-group log-status">
        <input type="password" class="form-control" placeholder="Wachtwoord" name="password" id="password">
        <i class="fa fa-lock"></i>
    </div>

<!--    <input type="submit" class="log-btn" ></input>-->
        <input type="button"
               value="Login"
               class="log-btn"
               onclick="formhash(this.form, this.form.password);" />
<!--    <button type="button" class="log-btn" >Log in</button>-->
</form>

</div>
<script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
<script src="js/index.js"></script>

<?php
//if (login_check($mysqli) == true) {
//    echo '<p>Currently logged ' . $logged . ' as ' . htmlentities($_SESSION['username']) . '.</p>';
//
//    echo '<p>Do you want to change user? <a href="includes/logout.php">Log out</a>.</p>';
//} else {
//    echo '<p>Currently logged ' . $logged . '.</p>';
//    echo "<p>If you don't have a login, please <a href='register.php'>register</a></p>";
//}
//?>
</body>
</html>