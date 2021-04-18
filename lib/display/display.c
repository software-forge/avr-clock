#include "display.h"

static unsigned char* buffer;
static unsigned char buffer_ptr;
static unsigned char buffer_s;

// MUX and DATA port clearing bitmasks
static unsigned char mux_clear;
static unsigned char data_clear;

static unsigned long long int prev_sw;           // variable to store the value of ms during the last LED switch

static const unsigned char mux_pins[] = 
{
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20
};

void display_init(unsigned char* buff, unsigned char buff_s)
{
    buffer = buff;
    buffer_s = buff_s;
    buffer_ptr = 0;

    // initialize previous switch timestamp
    prev_sw = 0x0000000000000000;

    /*
        initialize port clearing bitmasks
    */

    // calculate LED_MUX_PORT clearing bitmask
    unsigned char mc = 0;

    unsigned char i;
    for(i = 0; i < buffer_s; i++)
        mc |= mux_pins[i];

    // initialize bitmask
    mux_clear = ~mc;

    // initialize LED_DATA_PORT clearing bitmask
    data_clear = 0x00;

    /*
        set initial values of DDRs and PORTs
    */

    LED_DATA_DDR |= 0xff;
    LED_DATA_PORT = 0x00;

    for(i = 0; i < buffer_s; i++)
        LED_MUX_DDR |= mux_pins[i];
    LED_MUX_PORT &= mux_clear;
}

void display_sw(volatile unsigned long long int* ms_ptr)
{
    if((*ms_ptr - prev_sw) > SW_INTERVAL)
    {
        buffer_ptr++;
        if(buffer_ptr == buffer_s)
            buffer_ptr = 0x00;

        LED_MUX_PORT &= mux_clear;
        LED_MUX_PORT |= mux_pins[buffer_ptr];

        LED_DATA_PORT &= data_clear;
        LED_DATA_PORT |= buffer[buffer_ptr];

        prev_sw = *ms_ptr;
    }
}