int leds[5] = {12, 11, 10, 9, 8};
int trigPin = 4;
int echoPin = 3;

void ledsActive(int aantal) {
  switch(aantal){
    case 0:
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      break;
    case 1:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      break;
    case 2:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      break;
    case 3:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      break;
    case 4:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[3], HIGH);
      digitalWrite(leds[4], LOW);
      break;
    case 5:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[3], HIGH);
      digitalWrite(leds[4], HIGH);
      break;
    case 10:
      for(int i = 0; i < sizeof(leds); i++) {
        digitalWrite(leds[i], HIGH);
      }
      delay(100);
      for(int i = 0; i < sizeof(leds); i++) {
        digitalWrite(leds[i], LOW);
      }
    break;
  }
}

void setup() {
  for(int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  delay(60);

  // http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/

  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, 75);
  
  distance = (duration / 2) / 29.1;

  if(distance < 5) {
    ledsActive(10);
  } else if (distance >= 5 && distance < 8) {
    ledsActive(5);
  } else if (distance >= 8 && distance < 11) {
    ledsActive(4);
  } else if (distance >= 11 && distance < 14) {
    ledsActive(3);
  } else if (distance >= 14 && distance < 17) {
    ledsActive(2);
  } else if (distance >= 17 && distance < 20) {
    ledsActive(1);
  } else if (distance >= 20) {
    ledsActive(0);
  }

  Serial.println(distance);
}

