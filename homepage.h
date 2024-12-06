// To create literal strings stored in flash memory enclose your HTML code between
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover">
   <meta http-equiv="refresh" content="3">//refreshes webpage every 3 s
    <title>WebServer</title>
<style>
    body
    {
        background-color: dodgerblue;
        button{ padding: 10px 20px; font-size: 16px; cursor: pointer; }
    }
    .flex-Container{
        display: flex;
        flex-direction: column;
        background-color: dodgerblue;
        align-items: center;
    }
    h1{
        font: bold;
        font-size: 40px;
        font-family: Arial;
        color: navy;
        text-align: center;
    }
    p{
        font-size: 25px;
        font-family: Arial;
        color: navy;
        text-align:center;
    }
    th,td{
        font-size:25px;
        padding:8px;
        text-align: left;
        border-bottom: 1px solid #ddd;
    }

</style>
</head>
<body>
    <div class="flex-Container"> 
    <h1>Smart Pet Feeder</h1>
    <p>Welcome to my website displaying values from my project</p>
     <p>My video Stream</p>
    <iframe width="560" height="315" src="http://172.20.10.11:81/stream" frameborder="0" alt="Camera Stream currently unavailable" allowfullscreen></iframe>

    //code to activate servo button
    <h1>Button to toggle servo</h1>
    <p>Click the button to toggle the servo state</p>
    <button onclick="handleTurnOn()">Toggle Servo</button>
    <script>
        function handleTurnOn() {
            fetch('/turnon').then(response => response.text()).then(alert);
        }
    </script>

    <table>
        <tr>
            <th>Sensor</th>
            <th>Value</th>
            <th>Unit</th>
        </tr>
        <tr>
            <td>Capacity</td>
            <td> )=====");
String homePagePart2 = F(R"=====(</td>
           
            <td>cm</td>
        </tr> 
        
         <tr>
            <td>Weight</td>
            <td> )=====");
String homePagePart3 = F(R"=====(</td>
 
            <td>kg</td>
        </tr>
       
    </table>
</div>
</body>
</html>)=====");

