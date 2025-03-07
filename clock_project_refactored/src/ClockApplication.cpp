#include "ClockApplication.hpp"

ClockApplication::ClockApplication()
    : window(sf::VideoMode(800, 400), "Clock Display"),
      animationController(),
      timeDisplay(animationController, 100.0f, 150.0f, 120.0f, 0.0f) {  // Proper initialization
          
    window.setFramerateLimit(60);
}

void ClockApplication::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update time every second
        if (updateClock.getElapsedTime().asSeconds() >= 1.0f) {
            timeDisplay.updateTime();
            updateClock.restart();
        }

        animationController.update();

        // Rendering
        window.clear(sf::Color::White);
        timeDisplay.draw(window);
        window.display();
    }
}
