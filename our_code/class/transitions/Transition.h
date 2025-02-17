#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics.hpp>
#include <cmath>

/**
 * @class Transition
 * @brief Handles smooth transitions of clock hands using interpolation.
 */
class Transition {
private:
    float startAngle;  // Starting angle of the hand
    float targetAngle;  // Target angle to reach
    float currentAngle;  // Current angle during transition
    float speed;  // Speed of transition (degrees per frame)

public:
    Transition();  // Default constructor
    void start(float startAngle, float targetAngle, float speed);  // Initialize transition
    bool update();  // Update the angle and return true when finished
    float getAngle() const;  // Get the current angle
    bool isTransitionComplete() const;  // Vérifie si la transition est terminée
};

#endif // TRANSITION_H
