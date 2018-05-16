/* The Stove Network - Close Lighting Installation
  design, electronics and code by Kyle McAslan and Roy Shearer, Zero One
  This code counts passersby all day and night, and displays an animation routine during night hours.
  It also allows the control box to be used in a manual mode at any time.
  - Write your own evening animation routines in the 'animation' tab.
  - Call them from the sensorMode subroutine, below. ******** look for the asterisks ********.
  - If you don't want the sensor's count to continue increasing during evening hours, this can be commented out in the line just before those asterisks.
  - You can define daytime and night time hours in the lines below this.
*/

// NB. TIMES ARE GMT - THE CONTROL BOX DOES NOT ADUST FOR DAYLIGHT SAVINGS
int dayTimeBegin = 8; // hour at which daytime begins
int nightTimeBegin = 19; // hour at which night time begins

int PeopleCount;//counter for sensor triggers per day
boolean countResetFlag = true; // flag for resetting peopleCount

void setup() {
  Serial.begin(9600);
  setupStrips();
  setupLEDs();
  // calibrateSensor();
  // setupSD();
  clearStrips();
  delay(1000);
}

void loop() {
  // Serial.println(PeopleCount);


  //  mode select
  if (readButtonPin() == true) { //  check the button
    ManualMode(); // if button is pressed go to manual mode
  }
  else {
    SensorMode(); // otherwise go to sensor mode
  }
}

void ManualMode() {
  CheckSensor(); // check to see if someone is passing
  setButtonLED(); // set LEDs on the control box

  //read and map potentiometers (knobs)
  readPotsManual();

  //set the colours of the LED strips
  setStripsManual();
}

void SensorMode() {
  setLEDs(); // set LEDs on the control box
  CheckTime(); // check the time
  if (dayTime()) { // if it is daytime
    Serial.println("day");
    CheckSensor(); // check to see if someone is passing
    clearStrips(); // turn off the strips
    countResetCheck(); // check to see if PeopleCount needs to be reset
  }
  else { // otherwise if it is night time..
    CheckSensor(); // check to see if someone is passing - comment this out if you don't want the count to change during the evening time.
    // ********************** CALL AN ANIMATION ROUTINE HERE
    routine3();
    // **********************
  }
}

void countResetCheck() {
  if (newDay()) { // if its the first hour of a new day
    if (countResetFlag == true) { // and if the count has not already been reset
      {
        PeopleCount = 0; // reset the count
        countResetFlag = false; // flag that the count does not need to be reset again within this hour
        // writeSD();
      }
    }
  } else {
    countResetFlag = true; // flag to reset count when next day starts
  }
}
