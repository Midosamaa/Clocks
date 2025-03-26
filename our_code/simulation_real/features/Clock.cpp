#include "Clock.h"
#include <math.h>

// Constructor
Clock::Clock(float x, float y) : hand_1(45, sf::Color::Black), hand_2(45, sf::Color::Black) {
    dial.setRadius(60); 
    dial.setFillColor(sf::Color::White);  
    dial.setOutlineThickness(2);  
    dial.setOutlineColor(sf::Color::Black); 
    dial.setOrigin(60, 60);  
    dial.setPosition(x, y);  
}

float interpolateAngle(float start, float end, float t) {
    float delta = fmod((end - start + 540.0f), 360.0f) - 180.0f;
    return start + delta * t;
}


void Clock::update(float targetAngle1, float targetAngle2, sf::RenderWindow& window) {
    float startAngle1 = hand_1.getAngle();
    float startAngle2 = hand_2.getAngle();

    // Swap target angles if it's more efficient
    float originalCost = std::abs(targetAngle1 - startAngle1) + std::abs(targetAngle2 - startAngle2);
    float swappedCost = std::abs(targetAngle2 - startAngle1) + std::abs(targetAngle1 - startAngle2);

    if (swappedCost < originalCost) {
        std::swap(targetAngle1, targetAngle2);
    }

    // Determine how many steps based on movement distance
    // float diff1 = std::abs(targetAngle1 - startAngle1);
    // float diff2 = std::abs(targetAngle2 - startAngle2);
    // float maxDiff = std::max(diff1, diff2);

    // int steps = static_cast<int>(maxDiff * 1.0f);  // 2 steps per degree difference
    // steps = std::max(steps, 1); // Ensure at least 1 step

    int steps = 150;

    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;

        // Interpolate with shortest angular distance
        float interpolated1 = interpolateAngle(startAngle1, targetAngle1, t);
        float interpolated2 = interpolateAngle(startAngle2, targetAngle2, t);

        this->eraseHands(window, sf::Color::White);  // erase old hand positions
        hand_1.setAngle(interpolated1);
        hand_2.setAngle(interpolated2);
        this->drawHands(window);
        window.display();

        // Delay while processing events (no freeze)
        sf::Clock delayTimer;
        while (delayTimer.getElapsedTime().asMilliseconds() < 8) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
    }
}


void Clock::update_with_send(float targetAngle1, float targetAngle2, sf::RenderWindow& window, float speed) {
    float startAngle1 = hand_1.getAngle();
    float startAngle2 = hand_2.getAngle();

    // Smart swap of targets if more efficient
    float originalCost = std::abs(targetAngle1 - startAngle1) + std::abs(targetAngle2 - startAngle2);
    float swappedCost = std::abs(targetAngle2 - startAngle1) + std::abs(targetAngle1 - startAngle2);

    if (swappedCost < originalCost) {
        std::swap(targetAngle1, targetAngle2);
    }

    // float diff1 = std::abs(targetAngle1 - startAngle1);
    // float diff2 = std::abs(targetAngle2 - startAngle2);
    // float maxDiff = std::max(diff1, diff2);

    // int steps = static_cast<int>(maxDiff * 1.0f);  // 2 steps per degree difference
    // steps = std::max(steps, 1); // Ensure at least 1 step

    int steps = 150;

    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;

        float interpolated1 = interpolateAngle(startAngle1, targetAngle1, t);
        float interpolated2 = interpolateAngle(startAngle2, targetAngle2, t);

        // Send to supervisor
        ClockMotion motion;
        motion.hourAngle = interpolated1;
        motion.minuteAngle = interpolated2;
        motion.speed = speed;
        sendClockMotionToSupervisor(motion);

        // Animate
        this->eraseHands(window, sf::Color::White);
        hand_1.setAngle(interpolated1);
        hand_2.setAngle(interpolated2);
        this->drawHands(window);
        window.display();

        // Delay and keep window responsive
        sf::Clock delayTimer;
        while (delayTimer.getElapsedTime().asMilliseconds() < 8) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
    }
}


void Clock::eraseHands(sf::RenderWindow& window, sf::Color backgroundColor) const {
    sf::Vector2f pos = dial.getPosition();
    hand_1.erase(window, pos, backgroundColor);
    hand_2.erase(window, pos, backgroundColor);
}


// On the SFML window
void Clock::draw(sf::RenderWindow& window) const{
    window.draw(dial);  // Draw the clock face
    hand_1.draw(window, dial.getPosition());  
    hand_2.draw(window, dial.getPosition()); 
}

void Clock::drawHands(sf::RenderWindow& window) const {
    sf::Vector2f pos = dial.getPosition();
    hand_1.draw(window, pos);
    hand_2.draw(window, pos);
}

void Clock::setInstant(float angle1, float angle2) {
    hand_1.setAngle(angle1);
    hand_2.setAngle(angle2);
}



