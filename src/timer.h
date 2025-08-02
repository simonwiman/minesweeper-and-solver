#include <raylib.h>
#include "observer.h"


class Timer : public Observer
{
public:
    Timer();
    void update_time();
    void reset_time();
    double get_current_time();
    void act_on_update();

private:
    double current_time;
    double reset_timestamp;

};
