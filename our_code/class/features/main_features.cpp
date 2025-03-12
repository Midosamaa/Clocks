#include <SFML/Graphics.hpp>
#include <ctime>
#include "Clock.h"

//ONlY USED TO TEST OUR CLASS

int main() {
    // Create an SFML window with dimensions 400x400 and title "Single Clock Display"
    sf::RenderWindow window(sf::VideoMode(400, 400), "Single Clock Display");

    // Initialize a single clock at the center of the window
    Clock singleClock(200, 200);

    // Main loop to keep the window running
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the close button is clicked
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the current system time
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        // int hour = (localTime->tm_hour -1 + 24) % 24;  // Convert to 12-hour format, adjust by 1 hour
        // int minute = localTime->tm_min;  
        int hour = 4;
        int minute = 0;
        // Corrected angle calculations
        float hourAngle = (hour % 12)*30 + (minute * 0.2f)- 90;  // 30° per hour + minute influence and shift by -90 degrees
        float minuteAngle = minute * 6 - 90;  // 6° per minute
        // float hourAngle = 90;
        // float minuteAngle = 180;

        // Update clock with real-time values
        singleClock.update(hourAngle, minuteAngle);


        // Clear the window and set background color to white
        window.clear(sf::Color::White);

        // Draw the single clock
        singleClock.draw(window);

        // Display the updated frame
        window.display();
    }

    return 0;
}
