int buttonPin = 2;
int Pots[] = {A6, A1, A2, A3};
float PotVals3unMap = 0;
float lastPotVals3unMap = 0;

void readPotsManual() {
  for (int i = 0; i < 4; i++) {
    int val = map(analogRead(Pots[i]), 1024, 0, 0, 255);
    analogWrite(LED[i], val);
    if (val > 190) {
      val = 250;
    }
    if (val < 30) {
      val = 0;
    }
    //    Serial.println(Pots[1]);
    lastPotVals3unMap = PotVals3unMap;
    PotVals[i] = val;
    PotVals3unMap = ((0.96 * lastPotVals3unMap) + (0.04 * analogRead(Pots[3]))); // averaging/smoothing

    PotVals3 = map(PotVals3unMap, 1024, 0, 50, 2);
  }
}

boolean readButtonPin() {
  if (digitalRead(buttonPin) == HIGH) {
    return true;
  } else {
    return false;
  }
}

