#include "TimeDisplay.hpp"
#include <ctime>
#include <iostream>

TimeDisplay::TimeDisplay(AnimationController& animController, float startX, float startY, float spacingX, float spacingY)
    : animationController(animController), startPosition(startX, startY), spacingX(spacingX), spacingY(spacingY), currentDigits({0, 0, 0, 0}) {

    // Initialize the digit clocks
    for (int i = 0; i < 4; ++i) {
        clocks.emplace_back(startX + i * spacingX, startY);
    }
}

void TimeDisplay::updateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::array<int, 4> digits = {
        (localTime->tm_hour / 10),
        (localTime->tm_hour % 10),
        (localTime->tm_min / 10),
        (localTime->tm_min % 10)
    };

    setDigits(digits); 
}
void TimeDisplay::extractDigits(int hours, int minutes) {
    currentDigits = {hours / 10, hours % 10, minutes / 10, minutes % 10};
}

void TimeDisplay::updateClocks() {
    for (size_t i = 0; i < clocks.size(); ++i) {
        int digit = currentDigits[i];  
        float hourAngle = digit * 30.0f;  
        float minuteAngle = digit * 6.0f;  

        clocks[i].setTargetTime(hourAngle, minuteAngle);
    }
}

void TimeDisplay::setDigits(const std::array<int, 4>& digits) {
    currentDigits = digits;
    updateClockHands();
}

void TimeDisplay::updateClockHands() {
    for (size_t i = 0; i < clocks.size(); ++i) {
        int digit = currentDigits[i];  
        float hourAngle = digit * 30.0f;  
        float minuteAngle = digit * 6.0f; 

        clocks[i].setTargetTime(hourAngle, minuteAngle);
    }
}

void TimeDisplay::update() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    int hours = localTime->tm_hour;
    int minutes = localTime->tm_min;

    std::array<int, 4> newDigits = {hours / 10, hours % 10, minutes / 10, minutes % 10};

    if (newDigits != currentDigits) { 
        extractDigits(hours, minutes);
        updateClocks();
    }

    for (auto& clock : clocks) {
        clock.update();
    }
}

void TimeDisplay::draw(sf::RenderWindow& window) {
    for (auto& clock : clocks) {
        clock.draw(window);
    }
}
