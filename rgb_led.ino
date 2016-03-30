void setup() {}

int red = 11;
int green = 10;
int blue = 9;

void rgb(int r, int g, int b) {
  analogWrite(red, (255 - r));
  analogWrite(green, (255 - g));
  analogWrite(blue, (255 - b));
}

void loop() {
  rgb(0, 50, 0);
}
