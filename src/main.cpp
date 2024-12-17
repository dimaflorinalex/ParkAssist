#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// LCD
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensors (HC-SR04 Ultrasonic Sensors)
enum Sensor {
  FRONT = 0,
  BACK = 1
};

const int trigPins[2] = { 13, 11 };
const int echoPins[2] = { 12, 10 };
uint32_t pulseDurations[2] = { 0, 0 };
uint32_t spaceMillimeters[2] = { 0, 0 };

// Speaker
const int speakerPin = 3;

// Button
const int buttonPin = 2;
const int buttonDebounceMilliseconds = 100;
unsigned long buttonLastPressedMilliseconds = 0;

void checkSensor(Sensor sensor)
{
  // Clear PIN_TRIGGER
  digitalWrite(trigPins[sensor], LOW);
  delayMicroseconds(2);
  // Set PIN_TRIGGER for 10 micro seconds then clear
  digitalWrite(trigPins[sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[sensor], LOW);
  // Reads PIN_ECHO in micro
  pulseDurations[sensor] = pulseIn(echoPins[sensor], HIGH);
  // Calculate distance in mm s = v*t conversion from m to mm and s to us
  spaceMillimeters[sensor] = pulseDurations[sensor]*340/2/1000;
}

void handleButtonInterrupt() {
 	int buttonValue = digitalRead(buttonPin);
  
  if (buttonValue == LOW) {
    buttonLastPressedMilliseconds = millis();
  }
  else {
    if (millis() - buttonLastPressedMilliseconds >= buttonDebounceMilliseconds) {
      Serial.println("Button pressed");
    }
    
    buttonLastPressedMilliseconds = 0;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Debug");
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Hello, World!");
  
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, CHANGE);
  
  // pinMode(speakerPin, OUTPUT);
  // digitalWrite(speakerPin, LOW);
  
  for (int i = Sensor::FRONT; i <= Sensor::BACK; i++) {
  	pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  
  // //tone(speakerPin, 820, 300);
  
  // delay(1000);
  
  // noTone(speakerPin);
  
  checkSensor(Sensor::FRONT);
  checkSensor(Sensor::BACK);
  
  for (int i = Sensor::FRONT; i <= Sensor::BACK; i++) {
    char buffer[50] = "";
    sprintf(buffer, "Sensor %d: %d mm", i, spaceMillimeters[i]);
  	Serial.println(buffer);
  }
  
  delay(2000);
}