#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>
#include "features/Clock.h"
#include "transitions/DigitConfiguration.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 400), "Digital Clock Transition", sf::Style::Close);

    // Create 4 columns × 3 rows of clocks (Total: 12 clocks)
    std::vector<Clock> clocks;
    float startX = 100, startY = 50;
    float spacingX = 120, spacingY = 120;

    for (int i = 0; i < 8; ++i) {  
        for (int j = 0; j < 3; ++j) {  
            clocks.emplace_back(startX + i * spacingX, startY + j * spacingY);
        }
    }

    // Initial Time: 12:00
    int startHours = 12, startMinutes = 0;
    auto startAngles = getTimeAngles(startHours, startMinutes);

    // Target Time: 13:30
    int targetHours = 14, targetMinutes = 7;
    auto targetAngles = getTimeAngles(targetHours, targetMinutes);

    float transitionDuration = 1.8f;  // Adjust speed of transition, decrease to make it faster
    float elapsedTime = 0.0f;
    sf::Clock clockTimer;  // Timer to track transition progress

    // Display initial time
    for (size_t d = 0; d < 4; d++) {
        for (size_t c = 0; c < 6; c++) {
            size_t index = d * 6 + c;
            clocks[index].update(startAngles[d][c].first, startAngles[d][c].second);
        }
    }

    window.clear(sf::Color::White);
    for (auto& clock : clocks) {
        clock.draw(window);
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Pause before transition

    // Start Digital Transition
    bool animationComplete = false;
    while (!animationComplete) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        elapsedTime = clockTimer.getElapsedTime().asSeconds();
        float t = elapsedTime / transitionDuration;
        if (t > 1.0f) t = 1.0f;  // Clamp t to prevent overshooting

        window.clear(sf::Color::White);

        bool allCompleted = true;
        for (size_t d = 0; d < 4; d++) {
            for (size_t c = 0; c < 6; c++) {
                size_t index = d * 6 + c;

                // LERP transition for smooth digital movement
                float interpolatedHour = (1 - t) * startAngles[d][c].first + t * targetAngles[d][c].first;
                float interpolatedMinute = (1 - t) * startAngles[d][c].second + t * targetAngles[d][c].second;

                clocks[index].update(interpolatedHour, interpolatedMinute);
                clocks[index].draw(window);

                // Check if all clocks have reached target angles
                if (std::abs(interpolatedHour - targetAngles[d][c].first) > 0.1f ||
                    std::abs(interpolatedMinute - targetAngles[d][c].second) > 0.1f) {
                    allCompleted = false;
                }
            }
        }

        window.display();

        if (allCompleted) {
            animationComplete = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // Maintain ~60 FPS
    }

    // Keep final state displayed
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for (auto& clock : clocks) {
            clock.draw(window);
        }
        window.display();
    }

    return 0;
}
