#include "main.h"

void set_mode(unsigned char m)
{
    mode = m;
    buzzer_on(&ms);

    if(mode == RUN_MODE)
        field = 0x00;
}

void next_field()
{
    field += 2;
    if(field == NUM_DISPLAYS)
        field = 0x00;
}

void adjust_field()
{
    switch(field)
    {
        case 0:
            adjust_h();
            break;
        case 2:
            adjust_m();
            break;
        case 4:
            adjust_s();
            break;
    }
}

void update_buffer()
{
    unsigned char* str_member_ptr;

    unsigned char i;
    for(i = 0; i < NUM_DISPLAYS; i += 2)
    {
        switch(i)
        {
            case 0:
                str_member_ptr = &current_time.hours;
                break;
            case 2:
                str_member_ptr = &current_time.minutes;
                break;
            case 4:
                str_member_ptr = &current_time.seconds; 
                break;
        }

        if(mode == SET_MODE && i == field && !tick)
        {
            display_buffer[i] = NULL_CHAR;
            display_buffer[i + 1] = NULL_CHAR;
        }
        else
        {
            display_buffer[i] = cc_digit((*str_member_ptr / 10) % 10);
            display_buffer[i + 1] = cc_digit(*str_member_ptr % 10);
        }
    }
}

unsigned char last_fld_st = RELEASD;
unsigned char last_adj_st = RELEASD;

int main(void)
{
    tick = 0x01;

    display_init(display_buffer, NUM_DISPLAYS);

    buzzer_init();

    switches_init();

    clock_reset();

    update_buffer();

    field = 0x00;
    set_mode(sr_switch_state());

    timers_init();
    
    sei();

    while(1)
    {   
        sr_switch_debounce(&ms, &set_mode);

        display_sw(&ms);
        buzzer_check(&ms);

        if(mode == SET_MODE)
        {
            poll_button(&ms, FLD_SWITCH);

            if(fld_state == PRESSED)
            {
                if(last_fld_st == RELEASD)
                {
                    next_field();
                    buzzer_on(&ms);
                    last_fld_st = PRESSED;
                }
            }
            else
                if(last_fld_st == PRESSED)
                    last_fld_st = RELEASD;

            poll_button(&ms, ADJ_SWITCH);

            if(adj_state == PRESSED)
            {
                if(last_adj_st == RELEASD)
                {
                    adjust_field();
                    buzzer_on(&ms);
                    last_adj_st = PRESSED;
                }
            }
            else
                if(last_adj_st == PRESSED)
                    last_adj_st = RELEASD;
        }    
    }

    return 0;
}

ISR(TIMER2_OVF_vect)
{
    tick ^= 0x01;

    if(tick && (mode == RUN_MODE))
        clock_tick();

    update_buffer();
}

ISR(TIMER1_COMPA_vect)
{
    ms++;
}

ISR(INT0_vect)
{
    sr_switch_toggle(&ms);
}