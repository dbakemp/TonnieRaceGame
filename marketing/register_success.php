<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Tonnie's grote racewereld</title>
    <link rel="stylesheet" href="css/style.css" />
</head>
<body>


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

    <h2>Succesvol geregistreerd!</h2>
    <center><p>Klik <a href="index.php">hier</a> om in te loggen</p></center>
</div>

</body>
</html>