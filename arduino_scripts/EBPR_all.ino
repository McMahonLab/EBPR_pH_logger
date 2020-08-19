//libraries
#include <SD.h>
#include <RTClib.h>
#include <Arduino.h>
#include <Wire.h>

//defining variables
#define SD_SS_PIN 12
#define pHpin A4
RTC_DS3231 rtc;
int batteryPin = A6;
int batterysenseValue = 0;
float battV;

//pH calibration results
#define pH4 39. //put values here
#define pH7 402.

void setup() {
  Serial.begin(57600);
//initialize the SD card
  SD.begin(SD_SS_PIN);
//initialize the RTC
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__))); //comment out when adjusted
//KEEP in mind 20 s delay
//battery 
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
}

void loop() {
//RTC
  DateTime now = rtc.now();
  String timeStamp = formatTimestamp(now);
//pH
  //Get the pH ADC output from pHpin
  float pHread = analogRead(pHpin);  
  //Convert ADC output to corrected pH using colibration results
  //corrVal = (((rawValue-rawLow)*(referenceRange))/(rawRange)) + referenceLow
  float pHcorr = (((pHread-pH7)*(-3))/(pH4-pH7))+7;
//batt
  batterysenseValue = analogRead(batteryPin); 
  battV = (3.3/1023.)*4.7*batterysenseValue;
//compile sensor values
  String dataSample = "A, ";
  dataSample+= timeStamp;
  dataSample+= ",";
  dataSample+= pHcorr;
  dataSample+= ",";
  dataSample+= battV;  
//SD  
  //Open the output file for writing/appending
  //Serial.println("Opening SD");
  File dataFile = SD.open("pH_A.txt", FILE_WRITE);//LESS THAN 8 CHARACTERS for file name
  //Serial.println("Printing to SD");
  dataFile.println(dataSample);
  //Serial.println("Printed to SD");
  Serial.println(dataSample);
  delay(100);
  dataFile.close();
  delay(600000); //delay another sample for 10 minutes (in mS)
}

String formatTimestamp(DateTime now) {
    String result = "";
    result += (String) now.year();
    result += "-" + (String) now.month() + "-";
    result += (String) now.day() + " ";
    result += (String) now.hour() + ":";
    result += (String) now.minute() + ":";
    result += (String) now.second();
    return(result);
}
