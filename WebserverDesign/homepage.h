// To create literal strings stored in flash memory enclose your HTML code between
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover">
   
    <title>WebServer</title>
<style>
    * {
    box-sizing: border-box;
  }
body{
    
    margin: 0;
    width: 100vw;
    height: 100vh;
    background-color: darkslategray;
    
}

/* Column container */
.row {  
    display: flex;
    flex-wrap: wrap;
  
    
  }
  
  /* Create two unequal columns that sits next to each other */
  /* Sidebar/left column */
  .side {
    flex: 30%;  
    background-color: lightlategray;
    padding: 20px;
    column-gap:5px ;
    
  }
  
  /* Main column */
  .main {
    flex: 70%;
    background-color:#ddd;
    padding: 20px;
    column-gap:5px ;
  }
  

  .footer {
    padding: 20px;
    text-align: center;
    background: #ddd;
  }






.button1{
    float: left;
    display:inline block;
  padding: 15px 25px;
  font-size: 16px;
  cursor: pointer;
  text-align: left;
  text-decoration: none;
  outline: none;
  color:black;
  background-color:lightgoldenrodyellow;
  border: none;
  border-radius: 12px;
  box-shadow: 0 9px #999;
  grid-auto-rows: auto;
  margin:20px;
  
  

}
.button1:hover {background-color: goldenrod}
.button1:active {
    background-color: goldenrod;
    box-shadow: 0 5px #666;
    transform: translateY(4px);
}




.button2{
    float: left;
    display:inline block;
  padding: 15px 25px;
  font-size: 16px;
  cursor: pointer;
  text-align: left;
  text-decoration: none;
  outline: none;
  color:black;
  background-color: lightgoldenrodyellow;
  border: none;
  border-radius: 12px;
  box-shadow: 0 9px #999;
  grid-auto-rows: auto;
  margin:20px;
  

}
.button2:hover {background-color: goldenrod}
.button2:active {
    background-color: goldenrod;
    box-shadow: 0 5px #666;
    transform: translateY(4px);
}
.button3{float: left;
  display:inline block;
padding: 15px 25px;
font-size: 16px;
cursor: pointer;
text-align: left;
text-decoration: none;
outline: none;
color:black;
background-color: lightgoldenrodyellow;
border: none;
border-radius: 12px;
box-shadow: 0 9px #999;
grid-auto-rows: auto;
margin:20px;
}
.button3:hover {background-color: goldenrod}
.button3:active {
    background-color: goldenrod;
    box-shadow: 0 5px #666;
    transform: translateY(4px);
}
h1{
    font: bold;
    font-size: 40px;
    font-family: Arial;
    color: white;  
    background-color: darkslategrey; 
    text-align: center;
}
p{
    font-size: 25px;
    font-family: Arial;
    color: white;
    text-align:center;
}
th,td{
    font-size:25px;
    padding:25px;
    text-align: left;
    border: 1px solid black;
    color:black;    
}
hr{
    color:whitesmoke;
    background-color: white;
    
}
.full{
  
  height: 280px;
}
.half{
  opacity: 0.2;
  height: 280px;
}
.empty{
  opacity: 0.2;
  height: 280px;
}
</style>
</head>
<body>
     <h1>Smart Pet Feeder</h1>
    <hr>
    <p>Welcome to my website displaying my data from my project</p>
   

    <div class="row">
        <div class="side"> 

            <button class="button3">Admin Login</button>
           
            <button class="button1" button onclick="handleTurnOn()">Toggle Servo</button>
            <script>
                function handleTurnOn() {
                    fetch('/turnon').then(response => response.text()).then(alert);
                }
            </script>
              ><img src="GreenCircle" class="full">
           
             <img src="YellowCircle"class="half">
            <img src="RedCircle2" class="empty">
            <p>Storage lamps go here if possible</p>
            <p>admin login panel</p>
        </div>
        <div class="main">
            <p>My video Stream</p>
             <button class="button2">Toggle Camera</button>
            <iframe width="560" height="460" src="http://172.20.10.3:81/stream"  frameborder="0" alt="Camera Stream currently unavailable" allowfullscreen></iframe>
            <p>Click the button to toggle the servo state</p>

            

    <table style="width: 100%;">
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

