#include <Wire.h>
#include <mercalli.h>
#include <LEDs.h>
#include <adxl345.h>
#include <Arduino.h>

//calibration values array
float calArray[3];

void setup(void)
{
    Serial.begin(9600);

    //checking that john is connected:
    if(!checkForSensor())
    {
        while(1);
    }
    
    //turning sensor on and setting range
    //we use 2G range (since we care much less about range, since i cant slam my desk that hard and more about the precision)
    turnOn();
    setParams(2);

    //setting digital pins 6-13 to output;
    DDRB |= B00111111; // 8 - 13
    DDRD |= B11000000; // 6 and 7

    //Calibrating the sensor - taking 100 samples over a second to find average offset when sensor is sitting still.
    calibrate(calArray);
}

void loop(void)
{
    float accelArr[3];

    //sample for 1/4 a second (25 iterations * 10ms) - find the peak magnitude of acceleration during that second
    float maxMag = 0;
    uint8_t count = 0;
    while (count < 25)
    {
        getAccel(accelArr, calArray);
        float xAccel = accelArr[0];
        float yAccel = accelArr[1];
        float zAccel = 0.4* accelArr[2];
        float compare = 0.4 * sqrt(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel);
        if (maxMag < compare)
        {
            maxMag = compare;
        }
        count++;
        delay(10);
    }
    Serial.print("Max Magnitude: "); Serial.println(maxMag);

    //converting to Mercalli Scale (based upon local intensity) - we will subtract 0.15 for accelerometer error
    int mercalli = accelToMercalli(maxMag - 0.15);
    Serial.print("Mercalli: "); Serial.println(mercalli);

    
    //Light up LED's according to it
    driveLEDs(mercalli-2);
 
    //Hookup a CTRL-S and restart PC macro to the slamming your desk at a certain point
    if (mercalli == 10)
    {
        Serial.println("RESTART");
    }
}