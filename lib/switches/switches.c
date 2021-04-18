#include "switches.h"

static unsigned long long int sr_toggle;
static unsigned char sr_ignore;

static unsigned long long int last_fld_poll;
static unsigned char fld_count;

static unsigned long long int last_adj_poll;
static unsigned char adj_count;

void switches_init()
{
    SWITCHES_DDR |= ((1 << SR_SWITCH) | (1 << FLD_SWITCH) | (1 << ADJ_SWITCH));
    SWITCHES_PORT |= ((1 << SR_SWITCH) | (1 << FLD_SWITCH) | (1 << ADJ_SWITCH));

    GICR |= (1 << INT0);        // enable external interrupts on INT0
    MCUCR |= (1 << ISC00);      // interrupt triggered by any logical change on INT0

    sr_toggle = 0x0000000000000000;
    sr_ignore = 0x00;

    last_fld_poll = 0x0000000000000000;
    fld_count = 0x00;
    fld_state = button_state(FLD_SWITCH);
    
    last_adj_poll = 0x0000000000000000;
    adj_count = 0x00;
    adj_state = button_state(ADJ_SWITCH);
}

void sr_switch_toggle(volatile unsigned long long int* ms_ptr)
{
    if(!sr_ignore)
    {
        sr_toggle = *ms_ptr;
        sr_ignore = 0x01;
    }
}

void sr_switch_debounce(volatile unsigned long long int* ms_ptr, void (*action_ptr)(unsigned char))
{
    if(sr_ignore && (*ms_ptr - sr_toggle > DEBOUNCE_TIME))
    {
        sr_ignore = 0x00;

        (*action_ptr)(sr_switch_state());
    }
}

unsigned char sr_switch_state()
{
    if(SWITCHES_PIN & (1 << SR_SWITCH))
        return RUN_MODE;

    return SET_MODE;
}

unsigned char button_state(unsigned char btn)
{
    if(SWITCHES_PIN & (1 << btn))
        return RELEASD;

    return PRESSED;
}

void poll_button(volatile unsigned long long int* ms_ptr, unsigned char btn)
{
    unsigned char btn_state;
    unsigned char* last_btn_state;
    unsigned long long int* last_btn_poll;
    unsigned char* btn_counter;

    switch(btn)
    {
        case FLD_SWITCH:
            btn_state = button_state(FLD_SWITCH);
            last_btn_state = &fld_state;
            last_btn_poll = &last_fld_poll;
            btn_counter = &fld_count;
            break;
        case ADJ_SWITCH:
            btn_state = button_state(ADJ_SWITCH);
            last_btn_state = &adj_state;
            last_btn_poll = &last_adj_poll;
            btn_counter = &adj_count;
            break;
    }

    if((*ms_ptr - *last_btn_poll) > POLL_DELAY)
    {
        if(btn_state != *last_btn_state)
        {
            *btn_counter += 1;

            if(*btn_counter >= COUNT_MAX)
            {
                *last_btn_state = btn_state;
                *btn_counter = 0;
            }
        }
        else
            *btn_counter = 0;
    }
}