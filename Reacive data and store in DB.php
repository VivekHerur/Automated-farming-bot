<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "Self Study";
$Moisture = $_GET["Moisture"];
//$Sem = $_GET["Sem"];
//$Sec = $_GET["Sec"];
//$Sub = $_GET["Sub"];
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
//$date = "2017-01-01 09:00:00";
//$sql = "INSERT INTO Completed_classes(Teacher_id, Date_time, Semester, Section_elective, Subject_Subject_code) VALUES ('$id','$date','$Sem','$Sec','$Sub')";
$sql = "UPDATE current_moisture SET Moisture='$Moisture' WHERE ID=1";
$sql = "insert into Water_Time(COUNT) values(1)";
if ($conn->query($sql) === TRUE) {
    echo "Record updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

/*$flag = 1;
$sql1 = "SELECT Teacher_Teacher_id, Classroom_Semester, Classroom_Section_elective FROM Attendance.Schedule";
$result = $conn->query($sql1);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        if($row["Teacher_Teacher_id"] == $id)
        {
            if($flag==1)
            {
            echo "Sem=";
            echo $row["Classroom_Semester"];
            echo "Sec=";
            echo $row["Classroom_Section_elective"];
            //$.get("http://192.168.0.7:80/", {command:$cmd});
            $flag = 0;
            }
        }
        
    }
} else {
    echo "0 results";
}*/
$conn->close();
?>
