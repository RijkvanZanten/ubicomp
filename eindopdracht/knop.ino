/* 
 *  Eindopdracht Ubicomp "De Kop van Jut"
 *  Bart Oude Elferink, Danny de Vries & Rijk van Zanten
 *  Maart 2016
 */
 

// Libraries
// --------------------------------------------------
  #include <VirtualWire.h>

 
// Constants
// --------------------------------------------------
  const int transmit_pin = 12;
  const int debounceDelay = 20;
  const int readingOffset = 750;

  
// Variables
// --------------------------------------------------
  int buttonState;
  int lastButtonState = LOW;
  long lastDebounceTime = 0;

  
// Setup & Main Loop
// --------------------------------------------------
  void setup() {
    // Enable wireless transmitting
    vw_set_tx_pin(transmit_pin);
    vw_set_ptt_inverted(true);
    vw_setup(2000);
  
    Serial.begin(9600);
  }
  
  void loop() {
    int reading = analogRead(A0);
  
    if(reading > readingOffset) {
      reading = HIGH;
    } else {
      reading = LOW;
    }
  
    if(reading != lastButtonState) {
      lastDebounceTime = millis();
    }
  
    if((millis() - lastDebounceTime) > debounceDelay) {
      if(reading != buttonState) {
        buttonState = reading;
  
        if(buttonState == HIGH) {
          Serial.println("Send 2");
          char msg[1] = {2}; // 0 = groen, 1 = rood, 2 = blauw
          vw_send((uint8_t *)msg, 1);
          vw_wait_tx();
        }
      }
    }
    lastButtonState = reading;
  }