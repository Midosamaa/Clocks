#include "Transition.h"

// Default constructor
Transition::Transition() : startAngle(0), targetAngle(0), currentAngle(0), speed(1.0f) {}

// Initialize a transition from `startAngle` to `targetAngle` at a given `speed`
void Transition::start(float startAngle, float targetAngle, float speed) {
    this->startAngle = startAngle;
    this->targetAngle = targetAngle;
    this->currentAngle = startAngle;
    this->speed = speed;
}

// Updates the angle smoothly towards the target
bool Transition::update() {
    if (std::fabs(currentAngle - targetAngle) < speed) {
        currentAngle = targetAngle;  // Stop when close enough
        return true;  // Transition completed
    }

    if (currentAngle < targetAngle)
        currentAngle += speed;
    else
        currentAngle -= speed;

    return false;  // Transition still ongoing
}

// Returns the current interpolated angle
float Transition::getAngle() const {
    return currentAngle;
}

// Vérifie si l'angle est égal à l'angle cible (transition terminée)
bool Transition::isTransitionComplete() const {
    return std::fabs(currentAngle - targetAngle) < 0.1f;  // Tolérance pour éviter les erreurs flottantes
}

