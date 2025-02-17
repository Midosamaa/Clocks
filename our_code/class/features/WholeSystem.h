#ifndef WHOLESYSTEM_H
#define WHOLESYSTEM_H

#include <SFML/Graphics.hpp>
#include "Digit.h"

class WholeSystem {
private:
    Digit digits[4];  // Array of four digits representing the full time (HH:MM)

public:
    WholeSystem();  // Constructs the whole clock system with four digits
    void updateSystem(int hour, int minute);  // Updates the system to display the given time
    void draw(sf::RenderWindow& window) const;  // Draws the full clock system on the SFML window
};

#endif // WHOLESYSTEM_H
