#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 


#include <WiFi.h>
#include "time.h"

const char* ssid     = "Red";
const char* password = "killer123";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;
char timemy[20];
char date[20];
void printLocalTime();
void printlcdtime();
void setup(){
  
  Wire.setPins(9, 6);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
   
    Serial.print(".");
    lcd.setCursor(3,0);
    lcd.print("no wifi");
    delay(500);
    lcd.clear();
  }
  lcd.clear();
  Serial.println("");
  Serial.println("WiFi connected.");
  lcd.setCursor(0,0);
  lcd.print(" wifi conneced");

  delay(500);
  lcd.clear();
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}


void loop(){
  
  printLocalTime();
  printlcdtime();
  delay(200);
  lcd.clear();
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S %p");
   strftime(timemy,20," %r",&timeinfo) ;
   strftime(date,20," %a %h %d",&timeinfo) ;

}


void printlcdtime(){

  lcd.print(timemy);
  lcd.setCursor(0,1);
 lcd.print(date);


}