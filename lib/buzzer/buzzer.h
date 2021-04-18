#include <avr/io.h>

#define BUZZER_DDR      DDRD
#define BUZZER_PORT     PORTD
#define BUZZER          PD6

#define BUZZ_TIME       50

void buzzer_init(void);
void buzzer_on(volatile unsigned long long int*);
void buzzer_check(volatile unsigned long long int*);
