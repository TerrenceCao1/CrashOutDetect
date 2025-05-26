#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <mercalli.h>
#include <LEDs.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

float xOffset = 0, yOffset = 0, zOffset = 0;

void setup(void)
{
    Serial.begin(9600);

    //checking that john works:
    if(!accel.begin())
    {
        Serial.println("No sensor detected - check that john.");
        while(1);
    }
    
    accel.setRange(ADXL345_RANGE_2_G); 
    //we use 2G since slamming your desk doesn't cause that much accel
    //sensitivity matters more than range of measurements

    //calibration stuff (taking 100 samples over a second while the sensor is staying still then averaging the xyz)
    for (uint8_t i = 0; i < 100; i++)
    {
        //get event
        sensors_event_t event; 
        accel.getEvent(&event);

        //summing the tries
        xOffset += event.acceleration.x;
        yOffset += event.acceleration.y;
        zOffset += event.acceleration.z;
        delay(10);
    }
    //getting the averages
    xOffset /= 100; yOffset /= 100; zOffset /= 100;

    Serial.println(" ");
}

void loop(void)
{
    sensors_event_t event; 
    accel.getEvent(&event);

    //sample for 1/4 a second (25 iterations * 10ms) - find the peak magnitude of acceleration during that second
    float maxMag = 0;
    uint8_t count = 0;
    while (count < 25)
    {
        accel.getEvent(&event);
        float xAccel = event.acceleration.x - xOffset;
        float yAccel = event.acceleration.y - yOffset;
        float zAccel = event.acceleration.z - zOffset;
        float compare = sqrt(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel);
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

    //lowkey may need to reoptimize the mercalli cause it's too sensitive

    //Light up LED's according to it
    //Hookup a CTRL-S and restart PC macro to the slamming your desk at a certain point
    //3D model a casing for the leds (potentially solder it to a protoboard...)
        //try to make it look pretty 
    //profit
}
