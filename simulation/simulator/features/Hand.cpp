#include "Hand.h"


Hand::Hand(float length, sf::Color color) 
    : angle(0), color(color), is_visible(true) { 
    shape.setSize(sf::Vector2f(length, 3)); // Set the size of the hand 
    shape.setOrigin(0, 1.5); // Set the rotation pivot at the base of the hand
    shape.setFillColor(this->color); 
}

float Hand::getAngle() const {
    return angle;
}

void Hand::setAngle(float newAngle) {
    angle = newAngle;  
    shape.setRotation(angle);  
}

void Hand::draw(sf::RenderWindow& window, sf::Vector2f position) const {
    if (is_visible) {
        shape.setPosition(position);
        window.draw(shape);
    }
}

void Hand::erase(sf::RenderWindow& window, sf::Vector2f position, sf::Color backgroundColor) const {
    if (is_visible) {
        sf::RectangleShape temp = shape; // copy current hand
        temp.setPosition(position);
        temp.setFillColor(backgroundColor);  // use background color to "erase"
        window.draw(temp);
    }
}



