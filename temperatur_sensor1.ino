
#include <Servo.h>

#define temperature A0 //analog pin for temperature sensor
#define ledIndicator 2  // WHITE LED

Servo mainServo;//create servo project
int position = 0;
int previousPosition;

void setup() {
  
  pinMode(temperature, INPUT);  // for reading the temperature
  pinMode(ledIndicator, OUTPUT);  // for lighting
  mainServo.attach(3);// digital pin for servo motor
  
  Serial.begin(9600);//initialize serial communication

}

void loop() {
  
  // Temperature analysis
  int tempReading = analogRead(temperature);
  // If using 5v input
  float voltage = tempReading * 5.0; 
  
  // Divided by 1024
  voltage /= 1024.0;
  //Converting from 10mv per degree
  float tempC = (voltage - 0.5) * 100;
  
  // This maps temperature to degrees open for the flap
  int position = map(tempC, 0, 45, 0, 90);  //the temp is greater than 30 and at 90
  Serial.println(position);
  if(previousPosition != position){
     mainServo.write(position);
  	 digitalWrite(ledIndicator, HIGH);// the led is lighting
     delay(1000); // it waits for 1 second and turns off
  }
     
  digitalWrite(ledIndicator, LOW);// this is when it will trun off
  previousPosition = position;
}


