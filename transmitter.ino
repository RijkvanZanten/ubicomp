#include <VirtualWire.h>

const int transmit_pin = 12;
const int button = 4;

int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  pinMode(button, INPUT);
}

void loop() {
  int reading = digitalRead(button);

  if(reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > debounceDelay) {
    if(reading != buttonState) {
      buttonState = reading;

      if(buttonState == HIGH) {
        char msg[5] = {'b', 'l', 'a', 'u', 'w'};
        vw_send((uint8_t *)msg, 4);
        vw_wait_tx();
      }
    }
  }
  lastButtonState = reading;
}
