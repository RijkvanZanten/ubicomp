#include <Wire.h>

int leds[9] = {12, 13, 10, 9, 8, 7, 6, 5, 4};

void setup() {
  for(int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  Wire.begin(8);
  Wire.onReceive(activateLights);
  Serial.begin(9600);
}

void loop() {
  delay(50);
}

void activateLights(int x) {
  int howMany = Wire.read();

  if(howMany < 10) {
    for(int a = 0; a < howMany; a++){
      digitalWrite(leds[a], HIGH);
    }
    
    for(int a = howMany; a < sizeof(leds); a++){
      digitalWrite(leds[a], LOW);
    }
  } 
  }