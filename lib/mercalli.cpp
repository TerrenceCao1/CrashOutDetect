#include <arduino.h>
#include <mercalli.h>


//converting to Mercalli Scale (based upon local intensity) - we will subtract 0.15 for accelerometer error
/*thresholds: 
i: anything less 
ii/iii: 0.029
iv: 0.27
v: 0.61
vi: 1.2
vii: 2.2
viii: 3.9
ix: 7.4
x: 13.6  
*/
int accelToMercalli(float a)
{
    //we don't care about anything less than iii,
    if (a < 0.029)
    {
        return 0;
    }
    else if (a < 0.27)
    {
        return 3;
    }
    else if (a < 0.61)
    {
        return 4;
    }
    else if (a < 1.2)
    {
        return 5;
    }
    else if (a < 2.2)
    {
        return 6;
    }
    else if (a < 3.9)
    {
        return 7;
    }
    else if (a < 7.4)
    {
        return 8;
    }
    else if (a < 13.6)
    {
        return 9;
    }
    else
    {
        return 10;
    }
}