#include "timers.h"

// initializes timer1, which counts miliseconds since power-up
void timer1_init()
{
    ms = 0;

    // select clock source
    TCCR1B |= (1 << CS10); // 16 MHz system clock without prescaling

    // set mode of operation
    TCCR1B |= (1 << WGM12); // clear timer on compare match (CTC) mode

    // set counter resolution
    OCR1A |= 0x3e80;    // resolution = 16000 => oferflow every 1ms with 16 MHz clock

    // enable interrupts on compare match
    TIMSK |= (1 << OCIE1A);
}

// initializes timer2, which is the clock's main timer used to count seconds
void timer2_init()
{
    // select clock source
    ASSR |= (1 << AS2); // 32.768 kHz oscillator on TOSC1/2

    // set prescaler value
    //TCCR2 |= (1 << CS20) | (1 << CS22); // prescaler = 128 => 8-bit counter overflow every 1s.
    TCCR2 |= (1 << CS22); // prescaler = 64 => 8-bit counter overflow every 0.5s.

    // enable interrupts on counter overflow
    TIMSK |= (1 << TOIE2);
}

void timers_init()
{
    timer1_init();
    timer2_init();
}