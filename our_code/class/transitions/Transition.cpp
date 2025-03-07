#include "Transition.h"
#include <thread>  // Pour sleep

Transition::Transition() : currentHourAngle(0), currentMinuteAngle(0), targetHourAngle(0), targetMinuteAngle(0), duration(3.0f) {}

void Transition::startTransition(float currentH, float currentM, float targetH, float targetM, float transitionDuration) {
    startHourAngle = currentH;  // Save the starting hour angle
    startMinuteAngle = currentM;  // Save the starting minute angle
    currentHourAngle = currentH;
    currentMinuteAngle = currentM;
    targetHourAngle = targetH;
    targetMinuteAngle = targetM;
    duration = transitionDuration;  // Store transition duration
}

//Elapsed time: how much time has passed since the transition started.
void Transition::update(float elapsedTime) {
    // Normalize elapsed time, Increase it ot make it faster 
    float t = elapsedTime / duration;
    if (t > 1.0f) t = 1.0f;  // Ensure t never exceeds 1

    // Compute the exact position using linear interpolation (LERP)
    currentHourAngle = (1 - t) * startHourAngle + t * targetHourAngle;
    currentMinuteAngle = (1 - t) * startMinuteAngle + t * targetMinuteAngle;
}


bool Transition::isComplete() {
    return std::abs(currentHourAngle - targetHourAngle) < 0.1f && std::abs(currentMinuteAngle - targetMinuteAngle) < 0.1f;
}

// Récupérer l'angle actuel
float Transition::getHourAngle() { return currentHourAngle; }
float Transition::getMinuteAngle() { return currentMinuteAngle; }

void transitionToState(Clock& clock, float currentHourAngle, float currentMinuteAngle, 
                       float targetHourAngle, float targetMinuteAngle, float duration, sf::RenderWindow& window) {
    
    Transition hourTransition;
    Transition minuteTransition;

    hourTransition.startTransition(currentHourAngle, currentMinuteAngle, targetHourAngle, targetMinuteAngle, duration);
    minuteTransition.startTransition(currentHourAngle, currentMinuteAngle, targetHourAngle, targetMinuteAngle, duration);

    bool animationComplete = false;
    float elapsedTime = 0.0f;

    while (!animationComplete) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        hourTransition.update(elapsedTime);
        minuteTransition.update(elapsedTime);

        if (hourTransition.isComplete() && minuteTransition.isComplete()) {
            animationComplete = true;
        }

        // **Update the clock angles**
        clock.update(hourTransition.getHourAngle(), minuteTransition.getMinuteAngle());

        // **Clear and redraw the window while transitioning**
        window.clear(sf::Color::White);
        clock.draw(window);
        window.display();

        // **Wait a small time for smooth animation (~60 FPS)**
        std::this_thread::sleep_for(std::chrono::milliseconds(16));  
        elapsedTime += 0.016f;  // Simulate time passing in seconds
    }
}

