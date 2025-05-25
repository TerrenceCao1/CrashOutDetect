//for crashout detector:
//sample and get reading from accelerometer every 0.1s
//calculate the magnitude of the acceleration vector
//translate to the mercalli chart for earthquake magnitude
//display the result on leds
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

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

    //calibration stuff (taking 10 samples while the sensor is staying still then averaging the xyz)
    for (int i = 0; i < 10; i++)
    {
        //get event
        sensors_event_t event; 
        accel.getEvent(&event);

        //summing the tries
        xOffset += event.acceleration.x;
        yOffset += event.acceleration.y;
        zOffset += event.acceleration.z;
        delay(100);
    }
    //getting the averages
    xOffset /= 10; yOffset /= 10; zOffset /= 10;

    
    Serial.println(" ");
}

void loop(void)
{
    sensors_event_t event; 
    accel.getEvent(&event);
    float xAccel = event.acceleration.x - xOffset;
    float yAccel = event.acceleration.y - yOffset;
    float zAccel = event.acceleration.z - zOffset;

    //sample for 1/4 a second - find the peak magnitude of acceleration during that second
    float Mag = sqrt(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel);
    float maxMag = Mag;
    int count = 0;
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

    //Light up LED's according to it
    //Hookup a CTRL-S and restart PC macro to the slamming your desk at a certain point
    //3D model a casing for the leds (potentially solder it to a protoboard...)
        //try to make it look pretty 
    //profit
}
