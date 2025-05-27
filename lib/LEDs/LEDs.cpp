#include <arduino.h>
#include <LEDs.h>

/*
function: setPinRange - basically a macro to set a ton of pins to either input or output
parameters: a - start of the pins 
            b - end of the pins
            inOrOut - whether to set them ins or outs (0 = in, 1 = out)
output: void
*/
void setPinRange(int a, int b, bool inOrOut)
{
    for (int i = a; i <= b; i++)
    {
        pinMode(i, inOrOut);
    }
}
 
/*
function: DriveLEDs - turn on LED's in a line starting from pin 13 
parameter: a - how many to turn on
output: void
*/
void driveLEDs(int a)
{
    for (int i = 0; i < a; i++)
    {
        digitalWrite(13-i, HIGH);
    }
}

/*
function: turnOffAll - turn all the LED's
parameter: void
output: void
*/
void turnOffAll(void)
{
    for (int i = 6; i <= 13; i++)
    {
        digitalWrite(i, LOW);
    }
}