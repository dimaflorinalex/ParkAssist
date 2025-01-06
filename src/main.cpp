#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// #define DEBUG

// Aux
const unsigned long serialBaudRate = 115200;

// LCD
const uint8_t lcdRsPin = 12, lcdEnPin = 11, lcdD4Pin = 10, lcdD5Pin = 9, lcdD6Pin = 8, lcdD7Pin = 7;
LiquidCrystal lcd(lcdRsPin, lcdEnPin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);
const uint8_t lcdColumns = 16, lcdRows = 2;
const unsigned long lcdDebounceMilliseconds = 500;
unsigned long lcdLastUpdatedMilliseconds = 0;
const unsigned long lcdMaxSensorDistanceMillimeters = 700;

// Sensors (HC-SR04 Ultrasonic Sensors)
enum Sensor {
  FRONT = 0,
  BACK = 1
};

const uint8_t sensorTrigPins[2] = { 6, A1 };
const uint8_t sensorEchoPins[2] = { 5, A0 };
unsigned long sensorPulseDurations[2] = { 0, 0 };
unsigned long sensorDistanceMillimeters[2] = { UINT32_MAX, UINT32_MAX };

// Speaker
const uint8_t speakerPin = 13;
const unsigned int speakerToneFrequency = 2450;
const unsigned long speakerToneDurationMilliseconds = 50;
unsigned long speakerLastToneMilliseconds = 0;
bool speakerToneEnabled = true;

// Button
const uint8_t buttonPin = 2;
const unsigned long buttonDebounceMilliseconds = 100;
unsigned long buttonLastPressedMilliseconds = 0;
bool shouldHandleButton = false;

// LED
const int ledPin = 3;
const unsigned long ledDebounceMilliseconds = 500;
unsigned long ledLastUpdatedMilliseconds = 0;

// Alarm
enum Alarm {
  NONE = 0,
  LEVEL1 = 1,
  LEVEL2 = 2,
  LEVEL3 = 3
};

Alarm alarm = Alarm::NONE;
const unsigned long alarmSpeakerDebounceMilliseconds[4] = { UINT32_MAX, 450, 300, 200 };
const unsigned long alarmDistanceMillimeters[4] = { UINT32_MAX, 400, 250, 100 };
const unsigned long alarmLedValues[4] = { 0, 127, 127, 255 };

// Handles button interrupt
void handleButtonInterrupt() {
 	int buttonValue = digitalRead(buttonPin);
  
  if (buttonValue == LOW) {
    buttonLastPressedMilliseconds = millis();
  }
  else {
    if (millis() - buttonLastPressedMilliseconds >= buttonDebounceMilliseconds) {
      shouldHandleButton = true;
    }
    
    buttonLastPressedMilliseconds = 0;
  }
}

// Handles button
void handleButton() {
  shouldHandleButton = false;
  
  speakerToneEnabled = !speakerToneEnabled;

  char buffer[128] = "";
  sprintf(buffer, "%lu ms - Handle button - Speaker tone enabled: %d", millis(), speakerToneEnabled);
  Serial.println(buffer);
}

// Reads value from ultrasonic sensor
void readSensor(Sensor sensor)
{
  digitalWrite(sensorTrigPins[sensor], LOW);

  delayMicroseconds(2);

  digitalWrite(sensorTrigPins[sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPins[sensor], LOW);

  sensorPulseDurations[sensor] = pulseIn(sensorEchoPins[sensor], HIGH);
  sensorDistanceMillimeters[sensor] = sensorPulseDurations[sensor] * 340/2/1000; // Distance = Time * Speed of sound (340m/s). Conversion to millimeters

  if (sensorDistanceMillimeters[sensor] == 0) {
    sensorDistanceMillimeters[sensor] = UINT32_MAX;
  }

  #ifdef DEBUG
  char buffer[128] = "";
  sprintf(buffer, "%lu ms - Sensor %d - Distance: %d mm", millis(), sensor, sensorDistanceMillimeters[sensor]);
  Serial.println(buffer);
  #endif
}

// Reads values from all ultrasonic sensors
void readSensors() {
  for (int i = Sensor::FRONT; i <= Sensor::BACK; i++) {
    readSensor((Sensor)i);
  }
}

// Updates distances on LCD
void updateDistancesLCD() {
  unsigned long currentMilliseconds = millis();

  if (currentMilliseconds - lcdLastUpdatedMilliseconds >= lcdDebounceMilliseconds) {
    lcdLastUpdatedMilliseconds = currentMilliseconds;

    lcd.clear();
    char buffer[lcdColumns] = "";

    if (sensorDistanceMillimeters[Sensor::FRONT] <= lcdMaxSensorDistanceMillimeters) {
      sprintf(buffer, "Front: %lu mm", sensorDistanceMillimeters[Sensor::FRONT]);
      lcd.print(buffer);
    }
    else {
      lcd.print("Front: INF mm");
    }
    
    lcd.setCursor(0, 1);

    if (sensorDistanceMillimeters[Sensor::BACK] <= lcdMaxSensorDistanceMillimeters) {
      sprintf(buffer, "Back: %lu mm", sensorDistanceMillimeters[Sensor::BACK]);
      lcd.print(buffer);
    }
    else {
      lcd.print("Back: INF mm");
    }
  }
}

// Computes alarm level by interpreting sensor values
void interpretSensors() {
  unsigned long minSensorDistanceMillimeters = UINT32_MAX;

  for (int i = Sensor::FRONT; i <= Sensor::BACK; i++) {
  	if (sensorDistanceMillimeters[i] < minSensorDistanceMillimeters) {
      minSensorDistanceMillimeters = sensorDistanceMillimeters[i];
    }
  }

  for (int i = Alarm::LEVEL3; i >= Alarm::NONE; i--) {
    if (minSensorDistanceMillimeters <= alarmDistanceMillimeters[i]) {
      alarm = (Alarm)i;
      return;
    }
  }

  alarm = Alarm::NONE;
}

// Handles alarm
void handleAlarm() {
  #ifdef DEBUG
  char buffer[128] = "";
  sprintf(buffer, "%lu ms - Handle alarm - Alarm: %d - Speaker tone enabled: %d", millis(), alarm, speakerToneEnabled);
  Serial.println(buffer);
  #endif

  unsigned long currentMilliseconds = millis();

  // LED control
  if (currentMilliseconds - ledLastUpdatedMilliseconds >= ledDebounceMilliseconds) {
    ledLastUpdatedMilliseconds = currentMilliseconds;

    analogWrite(ledPin, alarmLedValues[alarm]);
  }

  // Speaker control
  if (alarm != Alarm::NONE) {
    if (speakerToneEnabled) {
      if (currentMilliseconds - speakerLastToneMilliseconds >= alarmSpeakerDebounceMilliseconds[alarm]) {
        speakerLastToneMilliseconds = currentMilliseconds;

        tone(speakerPin, speakerToneFrequency, speakerToneDurationMilliseconds);
      }
    }
  }
}

// Initializes system
void setup() {
  Serial.begin(serialBaudRate); // Initialize serial port
  
  #ifdef DEBUG
  char buffer[128] = "";
  sprintf(buffer, "%lu ms - Setup", millis());
  Serial.println(buffer);
  #endif
  
  // Initialize LCD
  lcd.begin(lcdColumns, lcdRows);
  lcd.print("Park Assist");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  lcdLastUpdatedMilliseconds = millis();
  
  // Initialize button
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, CHANGE);
  
  pinMode(speakerPin, OUTPUT); // Initialize Speaker
  
  pinMode(ledPin, OUTPUT); // Initialize LED

  // Initialize sensors
  for (int i = Sensor::FRONT; i <= Sensor::BACK; i++) {
  	pinMode(sensorTrigPins[i], OUTPUT);
    pinMode(sensorEchoPins[i], INPUT);
  }
}

// Main working loop
void loop() {
  if (shouldHandleButton) {
    handleButton();
  }

  readSensors();
  updateDistancesLCD();
  interpretSensors();
  handleAlarm();
}