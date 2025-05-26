#include <arduino.h>
#include <mercalli.h>
#include <stdio.h>


//converting to Mercalli Scale (based upon local intensity) all values in m/s^2
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
int accelToMercalli(float acceleration)
{
    //offset (to make it less sensitive)
    acceleration -= 1.5f;
    
    //we don't care about anything less than iii
    if (acceleration < 0.029f)
    {
        return 0;
    }

    static const struct 
    {
        float max_accel;
        int mercalli_level;
    } mercalli_thresholds[] = 
    {
        { 0.27f,  3 },
        { 0.61f,  4 },
        { 1.2f,   5 },
        { 2.2f,   6 },
        { 3.9f,   7 },
        { 7.4f,   8 },
        { 13.6f,  9 },
        { 9999999999.0f, 10 } 
    };

    for (size_t i = 0; i < sizeof(mercalli_thresholds)/sizeof(mercalli_thresholds[0]); i++)
    {
        if (acceleration < mercalli_thresholds[i].max_accel)
        {
            return mercalli_thresholds[i].mercalli_level;
        }
    }
    return 10;
}