#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SFML/Graphics.hpp>

class Clock {
protected:
    sf::CircleShape circle;
    sf::RectangleShape hourHand, minuteHand;
    sf::Vector2f position;
    float targetHourAngle, targetMinuteAngle;
    float currentHourAngle, currentMinuteAngle;
    bool animating;
    sf::Clock animationTimer;
    float animationDuration;

public:
    Clock(float x, float y, float radius = 40);
    
    void setTargetTime(float hourAngle, float minuteAngle);
    void update();
    void draw(sf::RenderWindow& window);
    void startAnimation(float duration);
    bool isAnimating() const;

};

#endif
