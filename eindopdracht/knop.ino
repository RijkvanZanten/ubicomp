#include <VirtualWire.h>

const int transmit_pin = 12;

int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 20;

const int readingOffset = 750;

void setup() {
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(A0);

  Serial.println(reading);

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
        Serial.println("STUUR");
        char msg[1] = {2};
        vw_send((uint8_t *)msg, 1);
        vw_wait_tx();
      }
    }
  }
  lastButtonState = reading;
}


