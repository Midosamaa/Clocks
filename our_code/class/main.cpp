#include "type_transitions/type_transitions.h"  // Inclure le fichier d'animation Pac-Man
#include <ctime>


int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 400), "Clock Transition", sf::Style::Close);

    // Create Clocks
    vector<vector<Clock>> clocks(3, vector<Clock>(8, Clock(0, 0))); 
    float startX = 100, startY = 50;
    float spacingX = 120, spacingY = 120;

    for (int row = 0; row < 3; row++) {  
        for (int col = 0; col < 8; col++) {  
            clocks[row][col] = Clock(startX + col * spacingX, startY + row * spacingY);
        }
    }

    // Start Hour
    time_t now = time(0);
    struct tm *localTime = localtime(&now);

    int currentHour = localTime->tm_hour;  
    int currentMinute = localTime->tm_min; 

    string startText = (currentHour < 10 ? "0" : "") + to_string(currentHour) + (currentMinute < 10 ? "0" : "") + to_string(currentMinute);
    auto startAngles = getTextAngles(startText);

    //WORDS
    string word = "POLYTECH";
    auto wordAngles = getTextAngles(word);


    // Show Start Hour
    for (size_t col = 0; col < 8; col++) {  
        size_t digitIndex = col;  

        for (size_t row = 0; row < 3; row++) {  
            size_t clockIndex = row;  
            if (digitIndex < startAngles.size() && clockIndex < startAngles[digitIndex].size()) {
                clocks[row][col].update(startAngles[digitIndex][clockIndex].first, 
                                        startAngles[digitIndex][clockIndex].second);
            }
        }
    }

    //Update On Windows
    window.clear(sf::Color::White);
    for (const auto& rowVec : clocks) {
        for (const auto& clock : rowVec) {
            clock.draw(window);
        }
    }

    window.display();
    this_thread::sleep_for(chrono::seconds(1));

    //For Timeout
    window.display();
    sf::Clock delayTimer;
    while (delayTimer.getElapsedTime().asMilliseconds() < 500) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    } 

    int previousMinute = currentMinute;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check Real-Time Clock
        now = time(0);
        localTime = localtime(&now);
        currentHour = localTime->tm_hour;
        currentMinute = localTime->tm_min;

        // **When Minute Changes, Perform Transition**
        if (currentMinute == previousMinute) {
            previousMinute = currentMinute;

            // **Set New Target Hour**
            string targetText = (currentHour < 10 ? "0" : "") + to_string(currentHour) + 
                                (currentMinute < 10 ? "0" : "") + to_string(currentMinute);
            auto targetAngles = getTextAngles(targetText);

            // Transition
            //pacman(window, clocks, targetAngles);
            //slideTransition_from_left(window, clocks, startAngles, wordAngles, targetAngles);
            //slideTransition_from_right(window, clocks, targetAngles , wordAngles, startAngles);
            //slideTransition_from_bottom(window, clocks, startAngles , wordAngles, targetAngles);
            words(window, clocks, startAngles ,targetAngles, 1, "YEDAMntm");



            // **Update Start Hour for Next Transition**
            startText = targetText;
            startAngles = targetAngles;
        }

        // **Keep Displaying Current Time**
        window.clear(sf::Color::White);
        for (const auto& rowVec : clocks) {
            for (const auto& clock : rowVec) {
                clock.draw(window);
            }
        }
        window.display();
    }

    return 0;
}