#include <avr/io.h>

volatile unsigned long long int ms;  // miliseconds since power-up

void timer1_init(void);     // initializes timer1, which counts miliseconds since power-up

void timer2_init(void);     // initializes timer2, which is the clock's main timer used to count seconds

void timers_init(void);