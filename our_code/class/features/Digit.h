#ifndef DIGIT_H
#define DIGIT_H

#include <SFML/Graphics.hpp>
#include "Clock.h"

class Digit {
private:
    std::vector<Clock> clocks; 

public:
    Digit(float x, float y); 
    void draw(sf::RenderWindow& window) const; 
};

#endif // DIGIT_H
