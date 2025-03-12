#include "Clock.h"

// Constructs a clock with a given position
Clock::Clock(float x, float y) : hand_1(45, sf::Color::Black), hand_2(50, sf::Color::Black) {
    dial.setRadius(60);  // Set the radius of the clock face
    dial.setFillColor(sf::Color::White);  // Set the clock face color
    dial.setOutlineThickness(2);  // Define the thickness of the clock border
    dial.setOutlineColor(sf::Color::Black);  // Set the border color
    dial.setOrigin(60, 60);  // Set the origin to the center of the circle
    dial.setPosition(x, y);  // Place the clock at the specified position
}

// Updates the hand positions based on the given angles
void Clock::update(float angle1, float angle2) {
    hand_1.setAngle(angle1);
    hand_2.setAngle(angle2);
}

// Draws the clock and its hands on the SFML window
void Clock::draw(sf::RenderWindow& window) const{
    window.draw(dial);  // Draw the clock face
    hand_1.draw(window, dial.getPosition());  // Draw the first hand
    hand_2.draw(window, dial.getPosition());  // Draw the second hand
}

