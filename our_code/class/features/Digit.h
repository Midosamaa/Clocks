#ifndef DIGIT_H
#define DIGIT_H

#include <SFML/Graphics.hpp>
#include "Clock.h"

class Digit {
private:
    std::vector<Clock> clocks;  // Use dynamic vector instead of fixed array

public:
    Digit(float x, float y);  // Constructs a digit at the given position
    void changeDigit(int number);  // Updates the digit by adjusting the clocks' hands
    void draw(sf::RenderWindow& window) const;  // Draws the digit on the SFML window
};

#endif // DIGIT_H
