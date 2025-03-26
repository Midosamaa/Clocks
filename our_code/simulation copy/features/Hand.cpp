#include "Hand.h"

// Constructor
Hand::Hand(float length, sf::Color color) 
    : angle(0), color(color), is_visible(true) { 
    shape.setSize(sf::Vector2f(length, 3)); // Set the size of the hand 
    shape.setOrigin(0, 1.5); // Set the rotation pivot at the base of the hand
    shape.setFillColor(this->color); 
}

// Set the rotation angle of the hand
void Hand::setAngle(float newAngle) {
    angle = newAngle;  
    shape.setRotation(angle);  
}

// Draw the hand at the specified position in the SFML window
void Hand::draw(sf::RenderWindow& window, sf::Vector2f position) const{
    if (is_visible) {  // Only draw the hand if it is visible
        shape.setPosition(position);  
        window.draw(shape);  
    }
}
