#ifndef HAND_H
#define HAND_H

#include <SFML/Graphics.hpp>

class Hand {
private:
    mutable sf::RectangleShape shape;  // Represents the graphical shape of the clock hand, Use mutable to allow modification in const functions
    float angle;               // Current rotation angle of the hand (in degrees)
    sf::Color color;           // Color of the hand
    bool is_visible;           // Determines whether the hand should be drawn or not

public:
    explicit Hand(float length, sf::Color color);  // Constructor to initialize the hand
    void setAngle(float newAngle);  // Sets the rotation angle of the hand
    void draw(sf::RenderWindow& window, sf::Vector2f position) const;  // Draws the hand at the specified position
};

#endif //HAND_H
