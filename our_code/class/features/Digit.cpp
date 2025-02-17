#include "Digit.h"

// Constructs a digit made up of six clocks at the given position
Digit::Digit(float x, float y) {
    clocks.reserve(6);  // Reserve space for 6 clocks
    for (int i = 0; i < 6; i++) {
        clocks.emplace_back(x + (i % 3) * 110, y + (i / 3) * 110);  // ✅ Use vector
    }
}

// Updates the digit by adjusting the clocks' hands
void Digit::changeDigit(int number) {
    // Define hand positions to display a specific number (to be implemented)
}

// Draws the digit on the SFML window
void Digit::draw(sf::RenderWindow& window) const{
    for (const auto& clock : clocks) {
        clock.draw(window);
    }
}
