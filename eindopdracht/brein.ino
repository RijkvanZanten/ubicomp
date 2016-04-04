/* 
 *  Eindopdracht Ubicomp "De Kop van Jut"
 *  Bart Oude Elferink, Danny de Vries & Rijk van Zanten
 *  Maart 2016
 */


// Libraries
// --------------------------------------------------
  #include <Wire.h>
  #include <VirtualWire.h>


// Constants
// --------------------------------------------------
  // Settings
  const int startSpeed = 7500;
  const int endSpeed = 3500;
  const int scoreInterval = 450;
  const int maxIdleTime = 50; // maxIdleTime * scoreInterval = waiting time
  
  // Pins
  const int rgbLED[3] = {9, 10, 11};
  const int receive_pin = 6;
  const int button = 4;


// Variables
// --------------------------------------------------
  int points = 0;
  int currentColor; // 0 = groen, 1 = rood, 2 = blauw
  int amountOfLedsOn;
  bool isStarted = false;
  int idleTime = 0;
  unsigned long previousScoreMillis = 0;
  unsigned long previousLampMillis = 0;
  unsigned long previousRGBMillis = 0;


// Functions
// --------------------------------------------------
  // Set RGB-led to specific color. Uses CSS style RGB rgb(255, 0, 0);
  void rgb(int r, int g, int b) {
    analogWrite(rgbLED[0], (255 - r));
    analogWrite(rgbLED[1], (255 - g));
    analogWrite(rgbLED[2], (255 - b));
  }

  // Sets RGB-led color. 0 = green, 1 = red, 2 = blue. No parameter = off
  void setRGBColor(int color) {
    switch(color){
      case 0:
        rgb(0,255,0);
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

  // Calculates and returns RGB interval speed based on amount of points
  long lampInterval(int points) {
    int a = (endSpeed - startSpeed) / 100;
    int b = startSpeed;
    return a * points + b;
  }

  // What to do when game is inactive
  void idle() {
    if(digitalRead(button) == HIGH) {
      isStarted = true;
    }
    rgb(255,255,255);
    
    Wire.beginTransmission(8);
    Wire.write(11);
    Wire.endTransmission();
  }

  // Main game logic
  void game() {
    unsigned long currentMillis = millis();

    if(points == 0) {
      Wire.beginTransmission(8);
      Wire.write(0);
      Wire.endTransmission();
      amountOfLedsOn = 0;
  
      if(currentMillis - previousScoreMillis >= scoreInterval) {
        previousScoreMillis = currentMillis;
        idleTime++;
        if(idleTime == maxIdleTime) {
          idleTime = 0;
          isStarted = false;
        }
      }
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
      previousLampMillis = currentMillis;
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

  // Win animation and reset scores
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


// Setup & Main Loop
// --------------------------------------------------
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
    if(isStarted) {
      game();
    } else {
      idle();
    }
  }
  