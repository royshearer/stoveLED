int LED[] = {3, 5, 6, 9, 10};
int PotVals[] = {0, 0, 0, 0};
float PotVals3 = 0;

void setupLEDs() {
  for (int i = 0; i < 5; i++) {
    pinMode(LED[i], OUTPUT);
  }
}

void setLEDs() {
  for (int i = 0; i < 4; i++) {
    analogWrite(LED[i], 0);
  }
  setButtonLED();
}

void setButtonLED() {
  if (readButtonPin()) {
    digitalWrite(LED[4], HIGH);
  }
  else {
    digitalWrite(LED[4], LOW);
  }
}
