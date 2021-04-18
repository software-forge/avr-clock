#include "clock.h"

void clock_tick()
{
    current_time.seconds++;
    if(current_time.seconds == 60)
    {
        current_time.seconds = 0;

        current_time.minutes++;
        if(current_time.minutes == 60)
        {
            current_time.minutes = 0;

            current_time.hours++;
            if(current_time.hours == 24)
                current_time.hours = 0;
        }
    }
}

void clock_reset()
{
    current_time.seconds = 0;
    current_time.minutes = 0;
    current_time.hours = 0;
}

void adjust_h()
{
    current_time.hours++;
    if(current_time.hours == 24)
        current_time.hours = 0;
}

void adjust_m()
{
    current_time.minutes++;
    if(current_time.minutes == 60)
        current_time.minutes = 0;
}

void adjust_s()
{
    current_time.seconds++;
    if(current_time.seconds == 60)
        current_time.seconds = 0;
}