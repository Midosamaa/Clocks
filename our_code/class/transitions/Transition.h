#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "../features/Clock.h"  // Inclure Clock.h uniquement ici, pas dans Transition.h

class Transition {
private:
    float currentHourAngle;
    float currentMinuteAngle;
    float targetHourAngle;
    float targetMinuteAngle;
    float startHourAngle;  // Stores the initial hour angle
    float startMinuteAngle; // Stores the initial minute angle
    float duration;

public:
    Transition();
    void startTransition(float currentH, float currentM, float targetH, float targetM, float duration);

    void update(float);

    float getHourAngle();
    float getMinuteAngle();

    bool isComplete();
};

void transitionToState(Clock& clock, float currentHourAngle, float currentMinuteAngle, 
                       float targetHourAngle, float targetMinuteAngle, float speed, sf::RenderWindow& window);


#endif // TRANSITION_H
