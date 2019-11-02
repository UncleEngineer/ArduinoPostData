<?php
$time = date("M,d,Y h:i:s A");
$tempC = $_POST["temp"];
$file = 'index.html';
$data = $time." - ".$tempC;
file_put_contents($file, $data)
?>