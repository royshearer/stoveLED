# stoveLED
A reactive lighting installation for the close next to The Stove in Dumfries.

# Reprogramming
The controller is based on an Arduino Nano microcontroller and can easily be reprogrammed using a Mini B USB cable and laptop running Arduino IDE (or equivalent) software (available from http://arduino.cc).  The current code can be downloaded from this repository.

## What it currently does
The controller can operate in two modes: manual and automatic. These are selected by pushing the mode button inside the control box. I have left the system in automatic mode.
Beneath the shelf in the close is an ultrasonic proximity sensor pointing downwards. The system uses this to count how many people pass under the sensor every day. It does this constantly regardless of what mode it is in, and resets the count at 8am GMT every morning.
Automatic mode:
This mode is active when the mode switch inside the control box is unlit. During the day (0800 – 1900 GMT) the LED strips are off, but the system continues to count people passing under the sensor. During the night (1900 – 0800 GMT) the system chooses a lighting scheme based on the current number of people counted over that day. As it continues to add to this count throughout the evening, the colour scheme should change every time someone passes under the sensor.
Manual mode:
This mode is active when the mode switch inside the control box is lit. In this mode the user can select a colour for the LED strips to display statically at all times. The colour (in terms of red, green and blue) and overall brightness are set using the knobs in the control box. The system will stay in manual mode until it is turned off by the user pushing the mode button.
