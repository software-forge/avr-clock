#include "buzzer.h"

static unsigned long long int buzz_start;
static unsigned char buzzing;

void buzzer_init()
{
    BUZZER_DDR |= (1 << BUZZER);
    BUZZER_PORT &= ~(1 << BUZZER);

    buzz_start = 0x0000000000000000;
    buzzing = 0x00;
}

void buzzer_on(volatile unsigned long long int* ms_ptr)
{
    BUZZER_PORT |= (1 << BUZZER);
    buzz_start = *ms_ptr;
    buzzing = 0x01;
}

void buzzer_check(volatile unsigned long long int* ms_ptr)
{
    if(buzzing && ((*ms_ptr - buzz_start) > BUZZ_TIME))
    {
        BUZZER_PORT &= ~(1 << BUZZER);
        buzzing = 0x00;
    }
}
