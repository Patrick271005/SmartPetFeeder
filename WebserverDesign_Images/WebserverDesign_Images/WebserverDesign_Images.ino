#include <LittleFS.h>
 #include "LittleFS.h"
#include "SPIFFS.h"

#include <HX711.h>
#include <ESP32Servo.h> 
#include <Wire.h>
#include "rgb_lcd.h"

#define calibration_factor  -425.812 
#define LOADCELL_DOUT_PIN  15
#define LOADCELL_SCK_PIN   2

Servo s1;  // Servo object
int servoPosition = 0; // Closed position (need to combine this with weight check later)
int openPosition = 90;  // Open position 
bool isOpen = false;//need to update code to use this
float val = 0;

rgb_lcd lcd;

const int echo=35;
const int trig=33;
float  distance=0; 
long duration =0; //ultrasonic

const int full=16;
const int half=17;//leds
const int empty=18;

HX711 scale;

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "PatricksIphone";//     eir88963492
const char* password = "setting2000";//      8Mppau4ABJ

AsyncWebServer server(80);

// To create literal strings stored in flash memory enclose your HTML code between

//used actyal raw literal strings instead of previous webpage
const char homePagePart1[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
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
     <h1>Smart Pet Feeder Dashboard</h1>
    
   

    <div class="row">
        <div class="side"> 

            <button class="button3">Admin Login</button>
           
            <button class="button1" button onclick="handleTurnOn()">Toggle Servo</button>
            <script>
function handleTurnOn() {
  fetch('/turnon')
    .then(response => response.text())
    .then(alert);
}

function updateWeight() {
  fetch('/getWeight')
    .then(response => response.text())
    .then(weight => {
      let weigh = parseFloat(weight);
      document.getElementById("weightValue").innerText = weigh + " g";
    });
}

function updateCapacity() {
  fetch('/getCapacity') // requests value from server
    .then(response => response.text())
    .then(distance => {
      let dist = parseFloat(distance); // changes text to float

      // Updates capacityValue in table
      document.getElementById("capacityValue").innerText = dist + " cm";  

      // Update image opacity depending on distance
      document.querySelector(".full").style.opacity = dist <= 8 ? "1" : "0.2";
      document.querySelector(".half").style.opacity = (dist > 8 && dist <= 16) ? "1" : "0.2";
      document.querySelector(".empty").style.opacity = dist > 16 ? "1" : "0.2";
    });
}

// Start auto-updating values every second
setInterval(updateCapacity, 1000);
setInterval(updateWeight, 1000);
</script>
              <img src="GreenC" class="full" id="GreenC">
           
             <img src="YellowC"class="half" id="YellowC">
            <img src="RedC" class="empty" id="RedC">
            
        </div>
        <div class="main">
            <p>My video Stream</p>
             <button class="button2">Toggle Camera</button>
            <iframe width="860" height="460" src="http://172.20.10.3:81/stream"  frameborder="0" alt="Camera Stream currently unavailable" allowfullscreen></iframe>
          

    <table style="width: 100%;">
        <tr>
            <th>Sensor</th>
            <th>Value</th>
            <th>Unit</th>
        </tr>
        <tr>
            <td>Capacity</td>
            <td id="capacityValue">Loading...</td>
            <td>cm</td>
        </tr> 
        
         <tr>
            <td>Weight</td>
            <td id="weightValue">Loading...</td>
            <td>g</td>
        </tr>
       
    </table>
</div>
</body>
</html>)rawliteral";


//had to get rid of previous tabs and move all code into one file for async server

// Handle servo toggle------------------------------------------------------
//need to change this to websockets
void handleTurnOn()
{Serial.println("Servo Toggle Request Received"); // Debugging
  s1.write(0);
  servoPosition=0;//currently unused
  lcd.clear();
  lcd.print("Food Dispensing");
  lcd.setCursor(0,1);
  lcd.print("...");
  delay(3000);

  lcd.clear();
  s1.write(90);
  servoPosition=90;//currently unused
 


}

//capacity----------------------------------------------------------------------------------------------------------------
String CapacityCheck()
{
  String test;//used to print on webpage
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);//set up unltrasonic sensor
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);//how long sound wave travels
  distance = (duration/2) / 29.1; //divide by 2 echo and back ,29.1=converts to cm

  Serial.print(distance);
  Serial.print("cms");
  Serial.println();
  delay(250);

 if(distance <= 8)//Placeholder value for dist will change when i know how big my stoarge will be 
    {
      digitalWrite(full, HIGH);
      digitalWrite(half, LOW);
      digitalWrite(empty, LOW);

      lcd.clear();
      lcd.setCursor(0, 0); // start to print at the first row
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.setCursor(0, 1);
      lcd.print("Storage is full");
      delay(1000);

    }

   else if(distance <= 16)
    {
      digitalWrite(half, HIGH);
      digitalWrite(empty, LOW);
      digitalWrite(full, LOW);

      lcd.clear();
      lcd.setCursor(0, 0); // start to print at the first row
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.setCursor(0, 1);
      lcd.print("Storage is half");
      delay(1000);
    }
  

  else if(distance <= 25.26)
    {
      digitalWrite(empty, HIGH);
      digitalWrite(half, LOW);
      digitalWrite(full, LOW);

      lcd.clear();
      lcd.setCursor(0, 0); // start to print at the first row
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.setCursor(0, 1);
      lcd.print("Storage is empty");
      delay(1000);
    }
  else
  {
    digitalWrite(empty, LOW);
    digitalWrite(half, LOW);
    digitalWrite(full, LOW);

      lcd.clear();
      lcd.setCursor(0, 1); // start to print at the first row
      lcd.print("Unable to measure capacity: ");
      delay(1000);
  }

  test = String(distance);//calculates distance and then returns it to webserver
  return test;
}

//Weight-------------------------------------------------------------------------------------------
String  WeightCheck(){
  String test;
  
   Serial.print("read: \t\t");
  Serial.println(scale.get_units(5),1); 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reading: ");
  val = scale.get_units(5),1;
  if (val<0)//prevents negative values when i have no weight on loadcell
  {val=0;} // Get the weight in grams
  lcd.print(val);
  lcd.print(" g");
  lcd.println();
  delay(250);
  //all values in if statements need to be changed when the loadcell is calibrated correctly
  
      if (val < 100) {
          s1.write(90);  // Dispense food
      } else {
          s1.write(0);  // Stop food from falling out

  }

  test = String(val);
  scale.power_down();
  delay(2000); 
  
  scale.power_up();
  return test;
}


//void handle
void setup(void) {
  lcd.begin(16, 2);
    delay(1000);

  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
  pinMode(full,OUTPUT);
  pinMode(half,OUTPUT);
  pinMode(empty,OUTPUT);

   s1.attach(19); //placing servo to pin 19
  s1.write(90);  // Move the servo to the initial  closed position (********************************need to change this with closedPosition and test*********************************************)

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-425.812);  // Set the calibration factor for kilograms
  scale.tare();  // Reset the scale to 0, assuming no weight on it
  Serial.begin(115200);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
  }
  File root = LittleFS.open("/");
File file = root.openNextFile();//prints what files currently stored from littlefs
while (file) {
    Serial.println(file.name());
    file = root.openNextFile();
}
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  server.on("/",HTTP_GET,[](AsyncWebServerRequest*request){//sends homepage with all of its CSs
    request->send_P(200,"text/html",homePagePart1);
  });
  server.on("/turnon", HTTP_GET, [](AsyncWebServerRequest *request){//curently used for servo button need to change to use websockets
    handleTurnOn();
    request->send(200, "text/plain", "Servo Toggled");
});
  server.on("/getCapacity", HTTP_GET,[](AsyncWebServerRequest *request){//used to update distance table
    String capacityValue= CapacityCheck();  // Call function and get distance
    request->send(200, "text/plain", capacityValue);  // Send response
});
server.on("/getWeight", HTTP_GET,[](AsyncWebServerRequest *request){//usesd to update weight table
  String weightValue= WeightCheck();
  request->send(200, "text/plain", weightValue);
});
  server.on("/GreenC",HTTP_GET, [](AsyncWebServerRequest*request){//prints green lamp on webpage
    Serial.println("Serving GreenC.png");
    request->send(LittleFS, "/GreenC.png", "image/png");
  });
  server.on("/YellowC",HTTP_GET, [](AsyncWebServerRequest*request){//prints yellow lamp on webpage
    Serial.println("Serving YellowC.png");
    request->send(LittleFS, "/YellowC.png", "image/png");
  });
  server.on("/RedC",HTTP_GET, [](AsyncWebServerRequest*request){//prints red lamp on webpage
    Serial.println("Serving RedC.png");
    request->send(LittleFS, "/RedC.png", "image/png");
  });
  
  //server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void loop(void) {
  delay(1000);
}
//