// EBPR All Script for pHlogger
// Github: https://github.com/McMahonLab/EBPR_pH_logger
// Note: Remove SD Card from mayfly board prior to making adjustments. 

// Read EBPR_datalogger doc.
// Connect mayfly board to laptop using usb port. 
// Turn on mayfly board
// Upload this script. All libraries are now loaded, and you are ready to proceed.  

// Common Tasks  
    // To adjust time
        // Go to "initialize the RTC" section
    // To adjust pH range
        // Go to "pH Correlation..."
    // To calibrate new pH probe
        // Open EBPR pH scripts
        // Go to "pH Calibration Results"
    // To change sample interval/ test on serial monitor 
        // Go to "SD" and then "Sample Interval"
    // To change reactor name in datalogger output
        // Go to "Compile sensor values"
    // To change file name
        // Go to "SD". Must be < 8 characters. 
        
// Example Serial Monitor Output
  // w/o timestamp selected: Reactor Name, YYYY-MM-DD HH:MM:SS, pH, battery (V)
      //A, 2021-3-17 13:56:0,9.96,4.79 
    // w/timestamp selected: HH:MM:SS.SSS --> Reactor Name, YYYY-MM-DD HH:MM:SS, pH, battery (V)
      //13:56:21.466 -> A, 2021-3-17 13:56:0,9.96,4.79
    // NOTE: There is a ~21 second delay between the actual computer timestamp and the datalogger measured time. 

// Example Text File Output: Reactor Name, YYYY-MM-DD HH:MM:SS, pH, battery (V)
    // A, 2020-8-18 14:17:44,7.06,2.96



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
//Analog values were obtained from running the EBPR pH Script. Place analog values below.
//#define pH4 39. 
#define pH7 402.
#define pH10 814.

void setup() {
  Serial.begin(57600);

//initialize the SD card
  SD.begin(SD_SS_PIN);


//initialize the RTC
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__))); //comment out when adjusted
//KEEP in mind ~21 s delay

//battery 
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
}

void loop() {
//RTC
  DateTime now = rtc.now();
  String timeStamp = formatTimestamp(now);

//pH Correlation from analog reading applied to calibration curve to get pH.
    // There are two options: 1) pH range 4-7 and 2) pH range 7-10
  //Get the pH ADC output from pHpin
  float pHread = analogRead(pHpin);  
  //Convert ADC output to corrected pH using colibration results
  //corrVal = (((rawValue-rawLow)*(referenceRange))/(rawRange)) + referenceLow
  //float pHcorr = (((pHread-pH7)*(-3))/(pH4-pH7))+7; OLD pH range 4-7
  float pHcorr = (((pHread-pH7)*(-3))/(pH7-pH10))+7; // Current pH range 7-10

//batt
  batterysenseValue = analogRead(batteryPin); 
  battV = (3.3/1023.)*4.7*batterysenseValue;

//compile sensor values
  String dataSample = "B, "; //Reactor name for datalogger output
  dataSample+= timeStamp;
  dataSample+= ",";
  dataSample+= pHcorr;
  dataSample+= ",";
  dataSample+= battV;  // Max battery value is 4.82 V. 
//SD  
  //Open the output file for writing/appending
  //Serial.println("Opening SD");
  File dataFile = SD.open("pH_B.txt", FILE_WRITE);//LESS THAN 8 CHARACTERS for file name
  //Serial.println("Printing to SD");
  dataFile.println(dataSample);
  //Serial.println("Printed to SD");
  Serial.println(dataSample);
  delay(100); // Ask Krystyn what this delay does. 
  dataFile.close();
    // Sample Interval  
  delay(600000); //Sample interval (in mS). ex: 600000 ms = 10 min. To verify on serial monitor, 
  // set sample interval to 1000 ms = 1 s. 
}
// International time format for Serial Monitor. ex: YYYY-MM-DD HH:MM:SS
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
