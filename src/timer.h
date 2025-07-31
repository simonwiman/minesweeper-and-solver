#include <raylib.h>


class Timer
{
public:
    Timer();
    void update_time();
    void reset_time();
    double get_current_time();

private:
    double current_time;
    double reset_timestamp;

};
