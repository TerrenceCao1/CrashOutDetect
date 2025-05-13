#include <Arduino.h>
#include <LEDs.h>

void setup() {
    // setting pins 6 - 13 as output pins (my led pins) 
    setPinRange(6, 13, OUTPUT);
}

void loop() {
    driveLEDs(3);
    delay(1000);

    turnOffAll();
    delay(1000);

    driveLEDs(6);
    delay(1000);

    turnOffAll();
    delay(1000); 
}