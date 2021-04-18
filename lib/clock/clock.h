struct Time
{
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
};

struct Time current_time;

void clock_tick(void);
void clock_reset(void);

void adjust_h(void);
void adjust_m(void);
void adjust_s(void);