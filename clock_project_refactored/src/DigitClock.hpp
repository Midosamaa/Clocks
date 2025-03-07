#ifndef DIGITCLOCK_HPP
#define DIGITCLOCK_HPP

#include "Clock.hpp"

class DigitClock : public Clock {
public:
    DigitClock(float x, float y);
    void configure(int digit, int index);
};

#endif
