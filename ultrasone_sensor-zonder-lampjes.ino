int trigPin = 4;
int echoPin = 3;

void setup() {
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

  Serial.println(distance);
}

