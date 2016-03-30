const int whiteButtonPin = 2;
const int redButtonPin = 3;
const int blueButtonPin = 4;

const int redLed = 9;
const int greenLed = 10;
const int blueLed = 11;

int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 20;

unsigned long previousScoreMillis = 0;
unsigned long previousLampMillis = 0;

const long scoreInterval = 500;

const long startSpeed = 7500;
const long endSpeed = 1000;
const int maxScore = 100;

int points = 0;

int currentColor = 0;
  // Colors: 
  //   - White: 0,
  //   - Red: 1,
  //   - Blue: 2
int whichButtonToListenTo;

void setup() {
  pinMode(redButtonPin, INPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

long lampInterval(int points) {
  int a = (endSpeed - startSpeed) / maxScore;
  int b = startSpeed;
  return a * points + b;
}

void rgb(int r, int g, int b) {
  analogWrite(redLed, (255 - r));
  analogWrite(greenLed, (255 - g));
  analogWrite(blueLed, (255 - b));
}

void setLampColor(int color) {
  switch(color){
    case 0:
      rgb(255,255,255);
      whichButtonToListenTo = whiteButtonPin;
      break;
    case 1:
      rgb(255, 0, 0);
      whichButtonToListenTo = redButtonPin;
      break;
    case 2:
      rgb(0, 0, 255);
      whichButtonToListenTo = blueButtonPin;
      break;
    default:
      rgb(0,0,0);
      break;
  }
  currentColor = 0;
}

void loop() {  
  unsigned long currentMillis = millis();

  if(points > 0) {
    // Score verminderen per interval
    if(currentMillis - previousScoreMillis >= scoreInterval) {
      previousScoreMillis = currentMillis;
      points--;
      Serial.println(points);
    }
  }

  if(currentMillis - previousLampMillis >= lampInterval(points)) {
    previousLampMillis = currentMillis;
    setLampColor(random(0, 3));
    Serial.println("verander lamp");
  }
  
  int reading = digitalRead(whichButtonToListenTo);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        points++;
        Serial.println(points);
      }
    }
  }

  lastButtonState = reading;
}

