#include "HX711.h"

#define DT 2
#define SCK 3

HX711 pressureSensor;

const long basePressure = 6000000;    
const long frequentPressure = 7500000;
const long targetPressure = 8000000;

const int pumpPin = 11;
const int valvePin = 12;

void inflateToPressure(float target) {
    digitalWrite(pumpPin, HIGH);
    digitalWrite(valvePin, HIGH);
    while (pressureSensor.read() < target) {
      long raw = pressureSensor.read();
      Serial.print("Raw value: ");
      Serial.println(raw);
      delay(10);
    }
    digitalWrite(pumpPin, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(valvePin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pressureSensor.begin(DT, SCK);
  inflateToPressure(basePressure);
}

void loop() {
  // now inflateToPressure -> target and hold that pressure and delay 1s and release some pressure but not less then frequentPressure
  // this behave will continue loop
  // for release air pressure need to low the valve pin
  delay(100);
}
