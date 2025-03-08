#include <LittleFS.h>
 #include "LittleFS.h"
#include "SPIFFS.h"

#include <HX711.h>
#include <ESP32Servo.h> 
#include <Wire.h>
#include "rgb_lcd.h"

#define calibration_factor  -211.765 //Calibrated for kg (3196.6) need to change this figure later //-16   -61=can direct   -45=csn direct
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
#include "homepage.h"

const char* ssid = "PatricksIphone";//     eir88963492
const char* password = "setting2000";//      8Mppau4ABJ

WebServer server(80);



void handleRoot() {
  String message =  homePagePart1  +CapacityCheck() +homePagePart2 + WeightCheck()+ homePagePart3;
  server.send(200, "text/html", message);
}
// Handle servo toggle

void handleTurnOn()//need to change this to a toggle not just close and then open
{
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
  server.send(200,"text/plain","Servo Triggered:");


}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
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
  scale.set_scale(calibration_factor);  // Set the calibration factor for kilograms
  scale.tare();  // Reset the scale to 0, assuming no weight on it
  Serial.begin(115200);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
  }

  server.on("/", handleRoot);
  server.on("/turnon", handleTurnOn);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.on("/GreenCircle-removebg-preview", [](){
    server.send(LittleFS, "/GreenCircle-removebg-preview.png", "image/png");
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
//