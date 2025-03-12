#include "Digit.h"

// Constructor
Digit::Digit(float x, float y) {
    clocks.reserve(6);  // Reserve space for 6 clocks for test
    for (int i = 0; i < 6; i++) {
        clocks.emplace_back(x + (i % 3) * 110, y + (i / 3) * 110);  
    }
}

// Draws the digit on the SFML window
void Digit::draw(sf::RenderWindow& window) const{
    for (const auto& clock : clocks) {
        clock.draw(window);
    }
}
