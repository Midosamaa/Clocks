#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "features/Clock.h"
#include "transitions/Transition.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Clock Transition");

    Clock singleClock(200, 200);

    float currentHourAngle = ((2 % 12) * 30 + (15 * 0.5f)) - 90;
    float currentMinuteAngle = (15 * 6) - 90;

    float targetHourAngle = ((5 % 12) * 30 + (45 * 0.5f)) - 90;
    float targetMinuteAngle = (45 * 6) - 90;

    float transitionDuration = 1.5f;  // controls how long the entire transition takes in seconds.

    // **Initial Display**
    window.clear(sf::Color::White);
    singleClock.draw(window);
    window.display();

    // **Now the transition will update the window**
    transitionToState(singleClock, currentHourAngle, currentMinuteAngle, targetHourAngle, targetMinuteAngle, transitionDuration, window);

    // **Final loop to keep the window open after transition**
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        singleClock.draw(window);
        window.display();
    }

    return 0;
}
