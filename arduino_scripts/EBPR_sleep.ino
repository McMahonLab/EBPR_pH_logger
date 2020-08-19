#include <LoggerBase.h>

const int8_t greenLED = 8;        //pin for the green LED
const int8_t redLED = 9;          //pin for the red LED
const int8_t buttonpin = 21;      //button pin
const int8_t wakePin = A7;        //MCU alarm to wake mayfly from sleep
const int8_t sdCardPwerPin = -1;  //MCU SD card power pin
const int8_t sdCardSSPin = 12;    //SD card chip select pin
const int8_t senserPowerPin = 22; //MCU pin controlling main sensor power



Logger dataLogger;


void setup() {
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  pinMode(redLED, OUTPUT);
  digitalWrite(redLED, LOW);
  // Blink the LEDs to show the board is on and starting up
  greenredflash();

}

void loop() {
  // attempt at making mayfly sleep inbettwen samples

  // Set Information Pins
  dataLogger.setLoggerPins(wakePin, sdCardSSPin, sdCardPwerPin, buttonPin, greenLED);

//code in between

 // Call the processor sleep
  dataLogger.systemSleep();
}
