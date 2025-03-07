#ifndef TIMEDISPLAY_HPP
#define TIMEDISPLAY_HPP

#include "DigitClock.hpp"
#include "AnimationController.hpp"
#include <vector>
#include <array>

class TimeDisplay {
private:
    std::vector<DigitClock> clocks;
    sf::Vector2f startPosition;
    float spacingX, spacingY;
    std::array<int, 4> currentDigits;  
    AnimationController& animationController; // Reference to animation controller

    void extractDigits(int hours, int minutes);
    void updateClocks();

public:
    TimeDisplay(AnimationController& animController, float startX, float startY, float spacingX, float spacingY);  
    void updateTime();
    void update();
    void draw(sf::RenderWindow& window);
    void setDigits(const std::array<int, 4>& digits);
    void updateClockHands();
};

#endif
