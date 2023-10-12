<?php
$temp = '<p>&nbsp;</p>
<h2>Time/date</h2>
<p>&nbsp;</p>
<h2>Attendance</h2>
<p>&nbsp;</p>
<h2>Spaces Occupied</h2>
<p>&nbsp;</p>
<h2>Goals</h2>
<p>&nbsp;</p>
<h2>Log</h2>
<p>&nbsp;</p>
<h2>ToDo</h2>
<p>&nbsp;</p>
<h2>Notes</h2>
<p>&nbsp;</p>
<h2>Weather</h2>
<p>&nbsp;</p>
<h2>Data</h2>
</html>';

$fileName = date('Ymd');
$filePath = '/var/www/obs-web.rs.umbc.edu/data/pages/blog/';
$filePath .= $fileName . '.txt';
$file = fopen($filePath, 'w');

$template = '<html><h1>' . $fileName . '</h1>' . $temp;

if ($file) {
    $content = "This is the content of the file.";
    fwrite($file, $template);
    fclose($file);
}

echo $fileName;
?>
