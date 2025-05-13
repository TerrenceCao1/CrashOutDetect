#include <arduino.h>
#include <LEDs.h>

void setPinRange(int a, int b, bool inOrOut)
{
    for (int i = a; i <= b; i++)
    {
        pinMode(i, inOrOut);
    }
}
 
//driving certain LEDS up to a point (e.g. first 4, or 5 leds in my array)
void driveLEDs(int a)
{
    for (int i = 0; i < a; i++)
    {
        digitalWrite(13-i, HIGH);
    }
}

void turnOffAll(void)
{
    for (int i = 6; i <= 13; i++)
    {
        digitalWrite(i, LOW);
    }
}