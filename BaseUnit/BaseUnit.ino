#include "HX711.h"

#define DT 2
#define SCK 3

HX711 pressureSensor;

const long basePressure = 6000000;
const long frequentPressure = 7800000;
const long targetPressure = 8200000;

const int pumpPin = 11;
const int valvePin = 12;

void inflateToPressure(long target) {
  digitalWrite(pumpPin, HIGH);
  digitalWrite(valvePin, HIGH); // valve closed to allow inflation

  while (pressureSensor.read() < target) {
    long raw = pressureSensor.read();
    Serial.print("Inflating - Raw value: ");
    Serial.println(raw);
    delay(10);
  }

  digitalWrite(pumpPin, LOW);
}

void releaseUntilPressure(long target) {
  digitalWrite(pumpPin, LOW);
  digitalWrite(valvePin, LOW); // valve open to allow release

  while (pressureSensor.read() > target) {
    long raw = pressureSensor.read();
    Serial.print("Releasing - Raw value: ");
    Serial.println(raw);
    delay(10);
  }

  digitalWrite(valvePin, HIGH); // close valve again
}

void setup() {
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  pinMode(valvePin, OUTPUT);

  pressureSensor.begin(DT, SCK);

  // Initial inflation to base
  inflateToPressure(basePressure);
}

void loop() {
  // Step 1: Inflate to targetPressure
  inflateToPressure(targetPressure);

  // Step 2: Hold for 1 second
  delay(50);

  // Step 3: Release to frequentPressure
  releaseUntilPressure(frequentPressure);

  // Loop again
  delay(5); // Optional small pause
}
