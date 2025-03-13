#include "type_transitions/type_transitions.h"  // Inclure le fichier d'animation Pac-Man

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
    string startText = "0844";  
    auto startAngles = getTextAngles(startText);

    // Target Hour
    string targetWord = "1245";  
    auto targetAngles = getTextAngles(targetWord);

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
    
    // Pacman
    //pacman(window, clocks, targetAngles);

    //slide
    slideTransition_from_left(window, clocks, startAngles, wordAngles, targetAngles);
    slideTransition_from_right(window, clocks, targetAngles , wordAngles, startAngles);
    slideTransition_from_bottom(window, clocks, startAngles , wordAngles, targetAngles);

    // For the program not to finish quick
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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
