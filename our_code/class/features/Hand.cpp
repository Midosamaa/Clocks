#include "Hand.h"

// Constructor: Initializes the clock hand with a given length and color
Hand::Hand(float length, sf::Color color) 
    : angle(0), color(color), is_visible(true) {  // Initialize member variables
    shape.setSize(sf::Vector2f(length, 3)); // Set the size of the hand (length, thickness)
    shape.setOrigin(0, 1.5); // Set the rotation pivot at the base of the hand
    shape.setFillColor(this->color); // Apply the given color to the hand
}

// Set the rotation angle of the hand
void Hand::setAngle(float newAngle) {
    angle = newAngle;  // Update the angle variable
    shape.setRotation(angle);  // Apply the rotation to the graphical shape
}

// Draw the hand at the specified position in the SFML window
void Hand::draw(sf::RenderWindow& window, sf::Vector2f position) const{
    if (is_visible) {  // Only draw the hand if it is visible
        shape.setPosition(position);  // Position the hand at the given coordinates
        window.draw(shape);  // Render the hand on the window
    }
}
