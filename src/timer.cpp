#include "timer.h"


Timer::Timer() : current_time(0), reset_timestamp(0) {}

void Timer::update_time()
{
    current_time = GetTime() - reset_timestamp;
}

void Timer::reset_time()
{
    reset_timestamp = GetTime();
    current_time = 0;
}

double Timer::get_current_time()
{
    return current_time;
}

void Timer::act_on_update()
{
    reset_time();
}
