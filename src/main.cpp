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

    //Test code for checking the accel
    // Serial.print("X: "); Serial.print(event.acceleration.x + 0.3); Serial.print("  ");
    // Serial.print("Y: "); Serial.print(event.acceleration.y + 1.1); Serial.print("  ");
    // Serial.print("Z: "); Serial.print(event.acceleration.z + -7.3); Serial.print("  ");Serial.println("m/s^2 ");
    // delay(100);

    

    //find the magnitue of accel:
    float Mag = sqrt(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel);
    Serial.print("Acceleration Magnitude: "); Serial.print(Mag); Serial.println("m/s^2 ");
    delay(500);
}
