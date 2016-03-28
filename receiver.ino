#include <VirtualWire.h>

const int led_pin = 13;
const int receive_pin = 11;

void setup() {
    Serial.begin(9600);
    Serial.println("setup");
    
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_inverted(true);
    vw_setup(2000);

    vw_rx_start();

    pinMode(led_pin, OUTPUT);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen)) {
    digitalWrite(led_pin, HIGH);
    
    Serial.print("Got: ");

    int i;
    for (i = 0; i < buflen; i++){
	    Serial.print(char(buf[i]));
	  }
	  
	  Serial.println();
	  digitalWrite(led_pin, LOW);
	}
}
