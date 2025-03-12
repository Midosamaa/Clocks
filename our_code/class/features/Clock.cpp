#include "Clock.h"

// Constructor
Clock::Clock(float x, float y) : hand_1(45, sf::Color::Black), hand_2(50, sf::Color::Black) {
    dial.setRadius(60); 
    dial.setFillColor(sf::Color::White);  
    dial.setOutlineThickness(2);  
    dial.setOutlineColor(sf::Color::Black); 
    dial.setOrigin(60, 60);  
    dial.setPosition(x, y);  
}

// Updates the hand positions based on the given angles
void Clock::update(float angle1, float angle2) {
    hand_1.setAngle(angle1);
    hand_2.setAngle(angle2);
}

// On the SFML window
void Clock::draw(sf::RenderWindow& window) const{
    window.draw(dial);  // Draw the clock face
    hand_1.draw(window, dial.getPosition());  
    hand_2.draw(window, dial.getPosition()); 
}

