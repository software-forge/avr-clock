#include <avr/io.h>

#define SW_INTERVAL     2

#define LED_DATA_DDR    DDRA
#define LED_DATA_PORT   PORTA

#define LED_MUX_DDR     DDRB
#define LED_MUX_PORT    PORTB

void display_init(unsigned char*, unsigned char);    // initialize display
void display_sw(volatile unsigned long long int*);   // switch to next display