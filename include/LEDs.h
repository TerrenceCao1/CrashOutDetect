#ifndef LEDS_h_
#define LEDS_h_

//setting all the digital pins for the LED's
void setPinRange(int a, int b, bool inOrOut);

//driving certain LEDS up to a point (e.g. first 4, or 5 leds for the array)
void driveLEDs(int a);

//turning all the LEDs off
void turnOffAll(void);

#endif //LEDS_h_