#ifndef CLOCK_H
#define CLOCK_H

#include "Hand.h"
#include "../../receptor/communication.h"

#define MAXSTEP 2 // Max number of steps for smooth motion interpolation for motors **Change the steps which depends on your motors**

// Represents a graphical clock with two moving hands
class Clock {
private:

    Hand hand_1, hand_2;       // Clock hands (e.g., hour and minute)

public:
    // Constructor: set clock at position (x, y)
    Clock(float x, float y);

    void update(float targetAngle1, float targetAngle2);

    void update_with_send(float targetAngle1, float targetAngle2);

    // Instantly set hand positions without animation
    void setInstant(float angle1, float angle2);
};

float interpolateAngle(float start, float end, float t);

float angularDistance(float a, float b);

float normalize (float angle);

#endif // CLOCK_H
