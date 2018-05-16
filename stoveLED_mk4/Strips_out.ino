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

void setupStrips() {
  //various setups
  Strip1.begin();
  delay(100);
  Strip2.begin();
  delay(100);
  Wire.begin();
}

void clearStrips() {
  for (int i = 0; i < 150; i++) {
    Strip1.setPixelColor(i, 0, 0, 0);
    Strip2.setPixelColor(i, 0, 0, 0);
  }
  Strip1.show();
  Strip2.show();
}


void setStripsManual() {
  for (int i = 0; i < NUMPIXELS; i++) {
    Strip1.setPixelColor(i, Strip1.Color((PotVals[0] / PotVals3), (PotVals[1] / PotVals3), (PotVals[2] / PotVals3)));
    Strip2.setPixelColor(i, Strip2.Color((PotVals[0] / PotVals3), (PotVals[1] / PotVals3), (PotVals[2] / PotVals3)));
  }
  Strip1.show();
  Strip2.show();
}

