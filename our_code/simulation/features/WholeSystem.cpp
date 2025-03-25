#include "WholeSystem.h"

// Constructs the whole clock system with four digits at predefined positions
WholeSystem::WholeSystem() : digits{ Digit(50, 50), Digit(250, 50), Digit(450, 50), Digit(650, 50) } {}

// Draws the full clock system on the SFML window
void WholeSystem::draw(sf::RenderWindow& window) const{
    for (const auto& digit : digits) {  
        digit.draw(window);  // Draw the digit on the window
    }
}
