// this routine selects a static colour scheme based on the current PeopleCount
void routine1() {
  // generates a random count if needed
  if (PeopleCount == 0) {
    PeopleCount = random(150);
  }
  int animation = PeopleCount % 5; // keeps animation in the range 0-4

  //    Serial.println(PeopleCount);
  //    Serial.println(animation);

  if (animation == 0) {
    for (int i = 0; i < NUMPIXELS; i++) {
      Strip1.setPixelColor(i, Strip1.Color(200, i, 0));
      Strip2.setPixelColor(i, Strip2.Color(200, i, 0));
    }
  }
  if (animation == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      Strip1.setPixelColor(i, Strip1.Color(i, 200, 0));
      Strip2.setPixelColor(i, Strip2.Color(i, 200, 0));
    }
  }
  if (animation == 2) {
    for (int i = 0; i < NUMPIXELS; i++) {
      Strip1.setPixelColor(i, Strip1.Color(0, i, 200));
      Strip2.setPixelColor(i, Strip2.Color(0, i, 200));
    }
  }
  if (animation == 3) {
    for (int i = 0; i < NUMPIXELS; i++) {
      Strip1.setPixelColor(i, Strip1.Color(200, i, i));
      Strip2.setPixelColor(i, Strip2.Color(200, i, i));
    }
  }
  if (animation == 4) {
    for (int i = 0; i < NUMPIXELS; i++) {
      Strip1.setPixelColor(i, Strip1.Color(i, 200, i));
      Strip2.setPixelColor(i, Strip2.Color(i, 200, i));
    }
  }
  Strip1.show();  // update the strip
  Strip2.show();  // update the strip
}

// this routine displays a moving red dot. The higher PeopleCount is, the faster the dot moves.
void routine2() {
  // generates a random count if needed
  if (PeopleCount == 0) {
    PeopleCount = random(100, 255);
  }

  int val = 255-(PeopleCount % 255); // keeps val in the 0-254 range
  int R = 00; // background colours
  int G = 00; // background colours
  int B = 00; // background colours

  for (int i = 0; i < NUMPIXELS; i++) {  // step through each pixel in the strip
    int t = (millis() / val) % 139; // counts from 0-139, incrementing at a frequency dependant on val
    if (i == t) { // if the index of the pixel matches the count
      Strip1.setPixelColor(i, Strip1.Color(random(0, 200), random(0, 200), random(0, 200))); // give it a random colour
      Strip2.setPixelColor(i, Strip2.Color(random(0, 200), random(0, 200), random(0, 200))); // give it a random colour
    }
    else { // otherwise if it is any other pixel..
      Strip1.setPixelColor(i, Strip1.Color(R, G, B));  // give it the background colour
      Strip2.setPixelColor(i, Strip2.Color(R, G, B));  // give it the background colour
    }
    delay(100); // wait for 100ms
  }

  Strip1.show();  // update the strip
  Strip2.show();  // update the strip

}

