float sensorMax = 10;
float sensorMin = 10;
float sensorValue = 0;
float lastSensorValue = 0;
int threshold = 285;
unsigned long previousMillis = 0;

//Variables
int range = 200; //this is the sensor distance threshhold

void calibrateSensor() {
  //sensor calibration
  while (millis() < 5000) {
    sensorValue = analogRead(A7);

    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    if (sensorValue > sensorMin) {
      sensorMin = sensorValue;
    }
  }
}

void CheckSensor() {
  //sensor read function
  lastSensorValue = sensorValue;
  //  unsigned long currentMillis = millis();
  float sensorValueTemp = analogRead(A7);
  sensorValueTemp = map(sensorValueTemp, 0, 158, 0, 220);
  if (sensorValueTemp > 0) {
    sensorValue = ((0.98 * lastSensorValue) + (0.02 * sensorValueTemp)); // averaging/smoothing
  }
  //  Serial.println(sensorValue);

  //  if (currentMillis - previousMillis >= 200) {
  //    previousMillis = currentMillis;
  if (sensorValue < threshold && lastSensorValue >= threshold) { //<= (sensorMax - range)) {
    PeopleCount++;
    Serial.println(PeopleCount);
  }
  //  }
}
