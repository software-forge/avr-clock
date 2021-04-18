#include <avr/io.h>

#define SWITCHES_DDR    DDRD
#define SWITCHES_PORT   PORTD
#define SWITCHES_PIN    PIND

#define SR_SWITCH       PD2

#define FLD_SWITCH      PD3
#define ADJ_SWITCH      PD4

#define DEBOUNCE_TIME   50

#define POLL_DELAY       10

#define SET_MODE        0
#define RUN_MODE        1

#define PRESSED         0
#define RELEASD         1

#define COUNT_MAX         5

void switches_init(void);

void sr_switch_toggle(volatile unsigned long long int*);
void sr_switch_debounce(volatile unsigned long long int*, void (*)(unsigned char));
unsigned char sr_switch_state(void);

unsigned char fld_state;
unsigned char adj_state;

unsigned char button_state(unsigned char);
void poll_button(volatile unsigned long long int*, unsigned char);

unsigned char fld_button_state();
void fld_button_poll(volatile unsigned long long int*);