#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <accelFunctions.h>


void calibrate(float xOff, float yOff, float zOff)
{
    Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
    Serial.println("Starting Calibration");
    //taking 100 samples over 1 second;
    for (uint8_t i = 0; i < 100; i++)
    {
        //get event
        sensors_event_t event; 
        accel.getEvent(&event);
        Serial.println(i);

        //summing the tries
        xOff += event.acceleration.x;
        yOff += event.acceleration.y;
        zOff += event.acceleration.z;
        delay(10);
    }
    //getting the averages
    xOff /= 100; yOff /= 100; zOff /= 100;
    Serial.println("Calibration Complete!");
    return;
}