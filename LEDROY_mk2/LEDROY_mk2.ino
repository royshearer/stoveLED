
#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//LED setup
#define NUMPIXELS 139
Adafruit_NeoPixel Strip1 = Adafruit_NeoPixel(150, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Strip2 = Adafruit_NeoPixel(150, 14, NEO_GRB + NEO_KHZ800);

//File myFile;

//Varibles
int range = 200; //this is the sensor distance threshhold

//none of this needs changed
int LED[] = {3, 5, 6, 9, 10};
int Pots[] = {A6, A1, A2, A3};
int PotVals[] = {0, 0, 0, 0};
int button = 2;
float PotVals3 = 0;
float PotVals3unMap = 0;
float lastPotVals3unMap = 0;
char rtc_datetime[17];
int PeopleCount;//counter for sensor triggers per day
float sensorMax = 10;
float sensorMin = 10;
float sensorValue = 0;
float lastSensorValue = 0;
unsigned long previousMillis = 0;
int threshold=285;

void setup() {
  //sensor calibration
  while (millis() < 000) {
    sensorValue = analogRead(A7);

    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    if (sensorValue > sensorMin) {
      sensorMin = sensorValue;
    }
  }

  //various setups
  Strip1.begin();
  delay(100);
  Strip2.begin();
  delay(100);
  for (int i = 0; i < 5; i++) {
    pinMode(LED[i], OUTPUT);
  }
  Wire.begin();
  Serial.begin(9600);

  //  if (!SD.begin(4)) {
  //    Serial.println("initialization failed!");
  //    return;
  //  }
  //  Serial.println("initialization done.");
  //  if (SD.exists("test.txt")) {
  //    SD.remove("test.txt");
  //  }
  for (int i = 0; i < 150; i++) {
    Strip1.setPixelColor(i, 0, 0, 0);
    Strip2.setPixelColor(i, 0, 0, 0);
  }
  Strip1.show();
  Strip2.show();
  delay(1000);
}


void loop() {
  // Serial.println(PeopleCount);

    CheckSensor();
//  mode select
  if (digitalRead(button) == HIGH) {
    digitalWrite(LED[4], digitalRead(button));
    ManualMode();
  }
  else {
    for (int i = 0; i < 4; i++) {
      analogWrite(LED[i], 0);
    }
    digitalWrite(LED[4], digitalRead(button));
    SensorMode();
  }
}



void ManualMode() {
  //read and map potentiometers
//  delay(10);
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

  //  Serial.println(PotVals3);
  //write to LEDs
  for (int i = 0; i < NUMPIXELS; i++) {
    Strip1.setPixelColor(i, Strip1.Color((PotVals[0] / PotVals3), (PotVals[1] / PotVals3), (PotVals[2] / PotVals3)));
    Strip2.setPixelColor(i, Strip2.Color((PotVals[0] / PotVals3), (PotVals[1] / PotVals3), (PotVals[2] / PotVals3)));
  }
  Strip1.show();
  Strip2.show();
  //  }
}

void SensorMode() {
    CheckTime();
  //  CheckSensor();

  int val1 = int(rtc_datetime[9] - 48);
  int val2 = int(rtc_datetime[10] - 48);

  //  ledsOff();

  //LEDs off if "daytime" val1 = hours tens, val2 = hours singles
  if (val1 == 0 && val2 == 8 || val1 == 0 && val2 == 9 || val1 == 1 && val2 == 0 || val1 == 1 && val2 == 1 || val1 == 1 && val2 == 2
      || val1 == 1 && val2 == 3 || val1 == 1 && val2 == 4 || val1 == 1 && val2 == 5 || val1 == 1 && val2 == 6 || val1 == 1 && val2 == 7 || val1 == 1 && val2 == 8) {
        Serial.println("day");
    ledsOff();
  }
  else {
    //if nighttime
    //    CheckSensor();
    if (PeopleCount == 0) {
      PeopleCount = random(150);
    }
    int animation = PeopleCount % 5;
    //    Serial.println(PeopleCount);
    //    Serial.println(animation);
    if (animation == 0) {
      for (int i = 0; i < NUMPIXELS; i++) {
        Strip1.setPixelColor(i, Strip1.Color(200, i, 0));
        Strip2.setPixelColor(i, Strip2.Color(200, i, 0));
        //        Strip1.show();
        //        Strip2.show();
      }
    }
    if (animation == 1) {
      for (int i = 0; i < NUMPIXELS; i++) {
        Strip1.setPixelColor(i, Strip1.Color(i, 200, 0));
        Strip2.setPixelColor(i, Strip2.Color(i, 200, 0));
        //        Strip1.show();
        //        Strip2.show();
      }
    }
    if (animation == 2) {
      for (int i = 0; i < NUMPIXELS; i++) {
        Strip1.setPixelColor(i, Strip1.Color(0, i, 200));
        Strip2.setPixelColor(i, Strip2.Color(0, i, 200));
        //        Strip1.show();
        //        Strip2.show();
      }
    }
    if (animation == 3) {
      for (int i = 0; i < NUMPIXELS; i++) {
        Strip1.setPixelColor(i, Strip1.Color(200, i, i));
        Strip2.setPixelColor(i, Strip2.Color(200, i, i));
        //        Strip1.show();
        //        Strip2.show();
      }
    }
    if (animation == 4) {
      for (int i = 0; i < NUMPIXELS; i++) {
        Strip1.setPixelColor(i, Strip1.Color(i, 200, i));
        Strip2.setPixelColor(i, Strip2.Color(i, 200, i));
        //        Strip1.show();
        //        Strip2.show();
      }
    }
    Strip1.show();
    Strip2.show();

    //    CheckSensor();
    if (val1 == 0 && val2 == 8)
    {
      PeopleCount = 0;
    }
  }
}
//  int SDWrite(int PeopleCount) {
//    //readDate(rtc_datetime);
//    myFile = SD.open("test.txt", FILE_WRITE);
//    if (myFile) {
//      Serial.print("Writing");
//      Serial.print(" ");
//      Serial.print(PeopleCount);
//      myFile.println(PeopleCount);
//      myFile.close();
//      Serial.println("done.");
//    } else {
//      Serial.println("error opening test.txt");
//    }
//  }

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
    if (sensorValue <threshold && lastSensorValue>=threshold){ //<= (sensorMax - range)) {
      PeopleCount++;
            Serial.println(PeopleCount);
    }
//  }
}


void CheckTime() {
  //time read function
  readDate(rtc_datetime);
//    Serial.println(rtc_datetime);
}

void ledsOff() {

  for (int i = 0; i < NUMPIXELS; i++) {
    Strip1.setPixelColor(i, Strip1.Color(0, 0, 0));
    Strip2.setPixelColor(i, Strip2.Color(0, 0, 0));

  }
  Strip1.show();
  Strip2.show();
}



