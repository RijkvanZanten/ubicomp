#include <Wire.h>
#include <VirtualWire.h>

const int rgbLED[3] = {9, 10, 11}; // pins: r, g, b
const int receive_pin = 6;

unsigned long previousScoreMillis = 0;
unsigned long previousLampMillis = 0;

const long scoreInterval = 1000;

const long startSpeed = 7500;
const long endSpeed = 3500;
const int maxPoints = 100;

long points = 0;

int currentColor; // 0 = wit, 1 = rood, 2 = blauw
int amountOfLedsOn;

void rgb(int r, int g, int b) {
  analogWrite(rgbLED[0], (255 - r));
  analogWrite(rgbLED[1], (255 - g));
  analogWrite(rgbLED[2], (255 - b));
}

void setRGBColor(int color) {
  switch(color){
    case 0:
      rgb(255,125,45);
      currentColor = 0;
      break;
    case 1:
      rgb(255, 0, 0);
      currentColor = 1;
      break;
    case 2:
      rgb(0, 0, 255);
      currentColor = 2;
      break;
    default:
      rgb(0,0,0);
      break;
  }
}

long lampInterval(int points) {
  int a = (endSpeed - startSpeed) / maxPoints;
  int b = startSpeed;
  return a * points + b;
}

void win() {
  for(int i = 0; i < 15; i++) {
    rgb(255, 0, 0);
    delay(50);
    rgb(0, 255, 0);
    delay(50);
    rgb(0, 0, 255);
    delay(50);
  }
  points = 0;
}

void setup() {
  Wire.begin(); // Master-slave

  randomSeed(analogRead(0)); // For random color

  // Wireless receiver
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_rx_start();

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if(points == 0) {
    Wire.beginTransmission(8);
    Wire.write(0);
    Wire.endTransmission();
    amountOfLedsOn = 0;
  }
  
  if(points > 0) {
    if(currentMillis - previousScoreMillis >= scoreInterval) {
      previousScoreMillis = currentMillis;
      points--;
      Serial.println(points);
    }
  }

  if(currentMillis - previousLampMillis >= lampInterval(points)) {
    int randomColor = random(0, 3);
    if(randomColor == currentColor) {
      while(randomColor == currentColor) {
        randomColor = random(0, 3);
      }
    } else {
      setRGBColor(randomColor);
      previousLampMillis = currentMillis;
    }
  }

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen)) {
    if(buf[0] == currentColor) {
      points++; 
      Serial.println(points);
    }
  }

  if(points % 10 == 0 && points != 0 && points / 10 != amountOfLedsOn) {
    Wire.beginTransmission(8);
    Wire.write(points / 10);
    Wire.endTransmission();
    amountOfLedsOn = points / 10;
  }

  if(points == 100) {
    win();
  }
}

