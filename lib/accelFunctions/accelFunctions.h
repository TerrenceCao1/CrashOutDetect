#ifndef ACCELFUNCTIONS_H_
#define ACCELFUNCTIONS_H_

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


/*
function: calibrate - gets the offsets for accelerometer when not accelerating
parameters: floats -  xOff, yOff, zOff; 
output: void
*/
void calibrate(float xOff, float yOff, float zOff);




#endif