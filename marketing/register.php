<?php
include_once 'includes/register.inc.php';
include_once 'includes/functions.php';
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Tonnie's grote racewereld</title>
    <link rel="stylesheet" href="css/style.css" />
    <script type="text/JavaScript" src="js/sha512.js"></script>
    <script type="text/JavaScript" src="js/forms.js"></script>
    <link rel="stylesheet" href="styles/main.css" />
</head>
<body>
<!-- Registration form to be output if the POST variables are not
set or if the registration script caused an error. -->
<?php
if (!empty($error_msg)) {
    echo $error_msg;
}
?>
<!--<ul>-->
<!--    <li>Usernames may contain only digits, upper and lowercase letters and underscores</li>-->
<!--    <li>Emails must have a valid email format</li>-->
<!--    <li>Passwords must be at least 6 characters long</li>-->
<!--    <li>Passwords must contain-->
<!--        <ul>-->
<!--            <li>At least one uppercase letter (A..Z)</li>-->
<!--            <li>At least one lowercase letter (a..z)</li>-->
<!--            <li>At least one number (0..9)</li>-->
<!--        </ul>-->
<!--    </li>-->
<!--    <li>Your password and confirmation must match exactly</li>-->
<!--</ul>-->
<!--<form action="--><?php //echo esc_url($_SERVER['REQUEST_URI']); ?><!--"-->
<!--      method="post"-->
<!--      name="registration_form">-->
<!--    Username: <input type='text'-->
<!--                     name='username'-->
<!--                     id='username' /><br>-->
<!--    Email: <input type="text" name="email" id="email" /><br>-->
<!--    Password: <input type="password"-->
<!--                     name="password"-->
<!--                     id="password"/><br>-->
<!--    Confirm password: <input type="password"-->
<!--                             name="confirmpwd"-->
<!--                             id="confirmpwd" /><br>-->
<!--    <input type="button"-->
<!--           value="Register"-->
<!--           onclick="return regformhash(this.form,-->
<!--                                   this.form.username,-->
<!--                                   this.form.email,-->
<!--                                   this.form.password,-->
<!--                                   this.form.confirmpwd);" />-->
<!--</form>-->
<form action="<?php echo esc_url($_SERVER['REQUEST_URI']); ?>" method="post" name="login_form">
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
            <input type="text" class="form-control" placeholder="Gebruikersnaam " id="username" name="username">
            <i class="fa fa-user"></i>
        </div>
        <div class="form-group ">
            <input type="text" class="form-control" placeholder="E-mailadres " id="email" name="email">
            <i class="fa fa-user"></i>
        </div>
        <div class="form-group log-status">
            <input type="password" class="form-control" placeholder="Wachtwoord" name="password" id="password">
            <i class="fa fa-lock"></i>
        </div>
        <div class="form-group log-status">
            <input type="password" class="form-control" placeholder="Wachtwoord herhalen" name="confirmpwd" id="confirmpwd">
            <i class="fa fa-lock"></i>
        </div>
        <input type="button"
               value="Register"
               class="log-btn"
               onclick="return regformhash(this.form,
                                   this.form.username,
                                   this.form.email,
                                   this.form.password,
                                   this.form.confirmpwd);" />
</form>
<!--<p>Return to the <a href="index.php">login page</a>.</p>-->
</body>
</html>