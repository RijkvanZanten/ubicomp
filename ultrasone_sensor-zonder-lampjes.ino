int trigPin = 4;
int echoPin = 3;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void distance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, 75);
  distance = (duration / 2) / 29.1;
  return distance;
}

void loop() {
  long distance = distance();
  
  Serial.println(distance);
  delay(60);
}

