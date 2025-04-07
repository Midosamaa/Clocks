#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>
#include "Hand.h"
#include "../../supervisor/supervisor_send_angles.cpp"

#define MAXSTEP 12

// Represents a clock
class Clock {
private:
    sf::CircleShape dial;
    Hand hand_1, hand_2;

public:
    Clock(float x, float y);  // Constructor with position
    void update(float targetAngle1, float targetAngle2, sf::RenderWindow& window); //Update on the Window 
    void update_with_send(float targetAngle1, float targetAngle2, sf::RenderWindow& window); //Update on Window with the real time motor
    void eraseHands(sf::RenderWindow& window, sf::Color backgroundColor) const; //Put Hands on invisible or not if not used
    void draw(sf::RenderWindow& window) const; // Draw the Clock Face
    void drawHands(sf::RenderWindow& window) const; // Draw only the Hands
    void setInstant(float angle1, float angle2); // Initialisation Clock
};


#endif // CLOCK_H
