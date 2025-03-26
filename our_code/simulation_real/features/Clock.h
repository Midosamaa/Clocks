#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>
#include "Hand.h"
#include "../communication/communication.h"

class Clock {
private:
    sf::CircleShape dial;
    Hand hand_1, hand_2;

public:
    Clock(float x, float y);  // Constructor with position

    void update(float targetAngle1, float targetAngle2, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    void drawHands(sf::RenderWindow& window) const;

    void setInstant(float angle1, float angle2);
    void eraseHands(sf::RenderWindow& window, sf::Color backgroundColor) const;

    void update_with_send(float targetAngle1, float targetAngle2, sf::RenderWindow& window, float speed);


};


#endif // CLOCK_H
