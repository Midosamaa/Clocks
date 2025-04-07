#include "Transition.h"
#include <thread>  // Pour sleep

Transition::Transition() : currentHourAngle(0), currentMinuteAngle(0), targetHourAngle(0), targetMinuteAngle(0), duration(5.0f) {}

void Transition::startTransition(float currentH, float currentM, float targetH, float targetM, float transitionDuration) {
    startHourAngle = currentH;  // Save the starting hour angle
    startMinuteAngle = currentM;  // Save the starting minute angle
    currentHourAngle = currentH;
    currentMinuteAngle = currentM;
    targetHourAngle = targetH;
    targetMinuteAngle = targetM;
    duration = transitionDuration;  // Store transition duration
}

//Elapsed time: how much time has passed since the transition started.
void Transition::update(float elapsedTime) {
    // Normalize elapsed time, Increase it ot make it faster 
    float t = elapsedTime / duration;
    if (t > 1.0f) t = 1.0f;  // Ensure t never exceeds 1

    // Compute the exact position using linear interpolation (LERP)
    currentHourAngle = (1 - t) * startHourAngle + t * targetHourAngle;
    currentMinuteAngle = (1 - t) * startMinuteAngle + t * targetMinuteAngle;
}


bool Transition::isComplete() {
    return std::abs(currentHourAngle - targetHourAngle) < 0.1f && std::abs(currentMinuteAngle - targetMinuteAngle) < 0.1f;
}


float Transition::getHourAngle() { return currentHourAngle; }
float Transition::getMinuteAngle() { return currentMinuteAngle; }
