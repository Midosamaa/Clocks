#ifndef HAND_H
#define HAND_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

// Represents a single hand (hour or minute) of a clock
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
    float getAngle() const;     // Returns the current rotation angle of the hand
    void erase(sf::RenderWindow& window, sf::Vector2f position, sf::Color backgroundColor) const; // Erases the hand by redrawing it in the background color
};

#endif //HAND_H
