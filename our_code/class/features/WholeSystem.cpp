#include "WholeSystem.h"

// Constructs the whole clock system with four digits at predefined positions
WholeSystem::WholeSystem() : digits{ Digit(50, 50), Digit(250, 50), Digit(450, 50), Digit(650, 50) } {}

// Updates the system to display the given time (HH:MM)
void WholeSystem::updateSystem(int hour, int minute) {
    digits[0].changeDigit(hour / 10);  // Update first digit with tens place of hour
    digits[1].changeDigit(hour % 10);  // Update second digit with ones place of hour
    digits[2].changeDigit(minute / 10);  // Update third digit with tens place of minute
    digits[3].changeDigit(minute % 10);  // Update fourth digit with ones place of minute
}

// Draws the full clock system on the SFML window
void WholeSystem::draw(sf::RenderWindow& window) const{
    for (const auto& digit : digits) {  
        digit.draw(window);  // Draw the digit on the window
    }
}
