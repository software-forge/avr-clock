#include <avr/io.h>
#include <avr/interrupt.h>

#include <display.h>
#include <timers.h>
#include <clock.h>
#include <switches.h>
#include <buzzer.h>
#include <led_chars.h>

volatile unsigned char tick;

unsigned char mode;
unsigned char field;

#define NUM_DISPLAYS    6                   // number of seven segment displays to switch between

unsigned char display_buffer[NUM_DISPLAYS]; // character buffer for the 7-segment LED displays