/* 
 *  Eindopdracht Ubicomp "De Kop van Jut"
 *  Bart Oude Elferink, Danny de Vries & Rijk van Zanten
 *  Maart 2016
 */

 
// Libraries
// --------------------------------------------------
  #include <AlaLed.h>
  #include <Wire.h>

  AlaLed leds;
  

// Constants
// --------------------------------------------------
  byte pwmLEDs[] = {5, 6, 9, 10, 11};
  byte allLeds[] = {5, 4, 6, 7, 9, 8, 10, 12, 11};

  AlaSeq seq[] = {
    { ALA_FADEIN, 1000, 1000 },
    { ALA_ON, 1000, 1000 },
    { ALA_FADEOUT, 1000, 1000 },
    { ALA_BARSHIFTRIGHT, 1000, 1000 },
    { ALA_BARSHIFTLEFT, 1000, 1000 },
    { ALA_OFF, 1000, 1000 },
    { ALA_PIXELSHIFTRIGHT, 700, 1400 },
    { ALA_PIXELSHIFTLEFT, 700, 1400 },
    { ALA_BLINKALT, 500, 3000 },
    { ALA_PIXELSMOOTHSHIFTRIGHT, 1000, 4000 },
    { ALA_PIXELSMOOTHSHIFTLEFT, 1000, 4000 },
    { ALA_FADEINOUT, 1000, 4000 },
    { ALA_COMET, 1000, 4000 },
    { ALA_GLOW, 1000, 4000 },
    { ALA_STROBO, 200, 4000 },
    { ALA_ENDSEQ, 0, 0 }
  };


// Functions
// --------------------------------------------------
  void activateLights(int x) {
    int howMany = Wire.read();
  
    Serial.println(howMany);
  
    switch(howMany) {
      case 0:
        digitalWrite(allLeds[0], LOW);
        digitalWrite(allLeds[1], LOW);
        digitalWrite(allLeds[2], LOW);
        digitalWrite(allLeds[3], LOW);
        digitalWrite(allLeds[4], LOW);
        digitalWrite(allLeds[5], LOW);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 1:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], LOW);
        digitalWrite(allLeds[2], LOW);
        digitalWrite(allLeds[3], LOW);
        digitalWrite(allLeds[4], LOW);
        digitalWrite(allLeds[5], LOW);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 2:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], LOW);
        digitalWrite(allLeds[3], LOW);
        digitalWrite(allLeds[4], LOW);
        digitalWrite(allLeds[5], LOW);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 3:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], LOW);
        digitalWrite(allLeds[4], LOW);
        digitalWrite(allLeds[5], LOW);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 4:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], LOW);
        digitalWrite(allLeds[5], LOW);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 5:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], HIGH);
        digitalWrite(allLeds[5], LOW);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 6:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], HIGH);
        digitalWrite(allLeds[5], HIGH);
        digitalWrite(allLeds[6], LOW);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 7:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], HIGH);
        digitalWrite(allLeds[5], HIGH);
        digitalWrite(allLeds[6], HIGH);
        digitalWrite(allLeds[7], LOW);
        digitalWrite(allLeds[8], LOW);
        break;
      case 8:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], HIGH);
        digitalWrite(allLeds[5], HIGH);
        digitalWrite(allLeds[6], HIGH);
        digitalWrite(allLeds[7], HIGH);
        digitalWrite(allLeds[8], LOW);
        break;
      case 9:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], HIGH);
        digitalWrite(allLeds[5], HIGH);
        digitalWrite(allLeds[6], HIGH);
        digitalWrite(allLeds[7], HIGH);
        digitalWrite(allLeds[8], HIGH);
        break;
      case 10:
        digitalWrite(allLeds[0], HIGH);
        digitalWrite(allLeds[1], HIGH);
        digitalWrite(allLeds[2], HIGH);
        digitalWrite(allLeds[3], HIGH);
        digitalWrite(allLeds[4], HIGH);
        digitalWrite(allLeds[5], HIGH);
        digitalWrite(allLeds[6], HIGH);
        digitalWrite(allLeds[7], HIGH);
        digitalWrite(allLeds[8], HIGH);
        break;
      case 11:
        leds.runAnimation();
        break;
    }
  }


// Setup & Main Loop
// --------------------------------------------------
  void setup() {
    for(int i = 0; i < sizeof(leds); i++) {
      pinMode(allLeds[i], OUTPUT);
    }
  
    leds.initPWM(9, pwmLEDs);
    leds.setAnimation(seq);
  
    Wire.begin(8);
    Wire.onReceive(activateLights);
    Serial.begin(9600);
  }
  
  void loop() {
    delay(50);
  }