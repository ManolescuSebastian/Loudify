#include <Arduino.h>

// Data pins
const int DIGITAL_PIN = 2;
const int ANALOG_PIN = 0;
const int LED_PIN = 10;

const int threshold = 450;

// Sound sample
const int SAMPLE_TIME = 10;
unsigned long currentTime = 0;
unsigned long passedTime = 0;
unsigned long elapsedTime = 0;

//Led notification
const int LED_DELAY = 3000;
unsigned long currentTimeLed = 0;
unsigned long passedTimeLed = 0;
unsigned long elapsedTimeLed = 0;

int sampleBufferValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  readDigitalSoundData();
  //readAnalogSoundData();
}

void readDigitalSoundData() {
  currentTime = millis();
  elapsedTime = currentTime - passedTime;

  if (digitalRead(DIGITAL_PIN) == LOW) {
    sampleBufferValue++;
  }

  if (elapsedTime > SAMPLE_TIME) {
    Serial.println(sampleBufferValue);

    if (sampleBufferValue > threshold) {
      notifyLedON();
    }

    sampleBufferValue = 0;
    passedTime = currentTime;
  }

  dismissLedNotify();
}

void notifyLedON() {
  digitalWrite(LED_PIN, HIGH);
}

void dismissLedNotify() {
  currentTimeLed = millis();
  elapsedTimeLed = currentTimeLed - passedTimeLed;

  if (elapsedTimeLed > LED_DELAY) {
    digitalWrite(LED_PIN, LOW);
    passedTimeLed = currentTimeLed;
  }
}

void readAnalogSoundData() {
  int analogReads = analogRead(ANALOG_PIN);
  Serial.println(analogReads);
}
