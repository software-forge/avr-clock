#include <led_chars.h>

static const unsigned char cc_digits[] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
};

unsigned char cc_digit(unsigned char digit)
{
    if(digit >= 0 && digit < 10)
        return cc_digits[digit];

    return ERR_CHAR;
}

unsigned char ca_digit(unsigned char digit)
{
    if(digit >= 0 && digit < 10)
        return ~cc_digits[digit];

    return ERR_CHAR;
}