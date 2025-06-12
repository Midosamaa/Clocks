#ifndef HAND_H
#define HAND_H

// #include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

// Represents a single hand (hour or minute) of a clock
class Hand {
private:

    float angle;                       // Current angle (in degrees)
    bool is_visible;                   // Flag to control visibility

public:
    // Constructor: initializes hand with given length and color
    explicit Hand(float length);

    // Sets the hand's angle (rotation)
    void setAngle(float newAngle);

    // Returns the current angle of the hand
    float getAngle() const;
};

#endif // HAND_H
