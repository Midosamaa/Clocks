#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>
#include "Hand.h"

class Clock {
private:
    sf::CircleShape dial;
    Hand hand_1, hand_2;

public:
    Clock(float x, float y);  // Constructor with position

    void update(float angle1, float angle2);
    void draw(sf::RenderWindow& window) const;
};


#endif // CLOCK_H
