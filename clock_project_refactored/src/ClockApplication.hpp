#ifndef CLOCKAPPLICATION_HPP
#define CLOCKAPPLICATION_HPP

#include <SFML/Graphics.hpp>
#include "TimeDisplay.hpp"
#include "AnimationController.hpp"

class ClockApplication {
private:
    sf::RenderWindow window;
    TimeDisplay timeDisplay;
    AnimationController animationController;
    sf::Clock updateClock; // Used for periodic updates

public:
    ClockApplication();
    void run();
};

#endif
