#include <msp.h>
#include "stdio.h"
#include "math.h"

#define MAXFREQ 12000000
#define COUNT TIMER_A0->CCR[0]
#define ONEDEGREE TIMER_A0->CCR[0]/180

void setPWMFreq(uint8_t freq)
{
    float count;
    count = MAXFREQ/freq;
    count = roundf(count);
    TIMER_A0->CCR[0] = count;

}

void setPWMDC(uint8_t servo, float dc)
{
    float count;
    count =  roundf((30000*((float)dc/100)));
    TIMER_A0->CCR[servo] = count;
}



void setServoPosition(uint8_t servo, uint8_t degrees)
{
    //1040 gives full right position 0.69ms pulse
    //3620 gives full left position 2.41ms pulse

    //3740 gives full down position 2.5ms pulse
    //1120 gives full up position 0.76ms pulse
    float count;
    count =  roundf((30000*((float)degrees/100)));
    TIMER_A0->CCR[servo] = count;

}
