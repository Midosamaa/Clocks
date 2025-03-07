#include "Clock.hpp"

Clock::Clock(float x, float y, float radius) 
    : position(x, y), animating(false), animationDuration(1.5f) {
    
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);

    hourHand.setSize(sf::Vector2f(4, radius * 0.6f));
    hourHand.setOrigin(2, hourHand.getSize().y * 0.8f);
    hourHand.setPosition(position);

    minuteHand.setSize(sf::Vector2f(2, radius * 0.9f));
    minuteHand.setOrigin(1, minuteHand.getSize().y * 0.85f);
    minuteHand.setPosition(position);
}

void Clock::setTargetTime(float hourAngle, float minuteAngle) {
    targetHourAngle = hourAngle;
    targetMinuteAngle = minuteAngle;
    currentHourAngle = hourHand.getRotation();
    currentMinuteAngle = minuteHand.getRotation();
    animating = true;
    animationTimer.restart();

    // Hide hands if set to {315, 315}
    if (hourAngle == 315 && minuteAngle == 315) {
        hourHand.setFillColor(sf::Color::White);
        minuteHand.setFillColor(sf::Color::White);
    } else {
        hourHand.setFillColor(sf::Color::Red);
        minuteHand.setFillColor(sf::Color::Red);
    }
}

void Clock::update() {
    if (animating) {
        float t = animationTimer.getElapsedTime().asSeconds() / animationDuration;
        if (t >= 1.0f) {
            animating = false;
            hourHand.setRotation(targetHourAngle);
            minuteHand.setRotation(targetMinuteAngle);
        } else {
            hourHand.setRotation(currentHourAngle + 360 * t + (targetHourAngle - currentHourAngle) * t);
            minuteHand.setRotation(currentMinuteAngle + 360 * t + (targetMinuteAngle - currentMinuteAngle) * t);
        }
    }
}

void Clock::draw(sf::RenderWindow& window) {
    window.draw(circle);
    window.draw(hourHand);
    window.draw(minuteHand);
}

void Clock::startAnimation(float duration) {
    animationDuration = duration;
    animating = true;
    animationTimer.restart();
}

bool Clock::isAnimating() const {
    return animating;
}
