#define pHpin A4

//#define pH4 39.00 //ADC values from calibration results
//#define pH7 402.00 

void setup() {
  Serial.begin(57600);
}

void loop() {
  //Get the pH ADC output from pHpin
  float pHread = analogRead(pHpin);
  Serial.println(pHread); //run this code uncommented to get cal vals
  
  //Convert ADC output to corrected pH using colibration results
  //corrVal = (((rawValue-rawLow)*(referenceRange))/(rawRange)) + referenceLow
  //float pHcorr = (((pHread-pH7)*(-3))/(pH4-pH7))+7;
  //Serial.println(pHcorr);
  delay(1000);
}
