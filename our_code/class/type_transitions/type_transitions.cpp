#include "type_transitions.h"


void pacman(sf::RenderWindow& window, std::vector<std::vector<Clock>>& clocks, 
            const std::vector<std::vector<std::pair<float, float>>>& targetAngles) {
    float pacmanOpenHour;  // 2:20 -> Open mouth
    float pacmanOpenMinute = 45;

    float pacmanClosedHour = 0;  // 3:15 -> Closed mouth
    float pacmanClosedMinute = 0; 

    float pacmanDelay = 0.3f;
    float animationDuration = 0.5f;

    for (int row = 0; row < 3; row++) {  
    if (row % 2 == 0) {  // **Left to Right**
        pacmanOpenHour = 315;
        pacmanOpenMinute = 45;
        pacmanClosedHour = 0; 
        pacmanClosedMinute = 0;
        for (int col = 0; col < 8; col++) {  
            Clock& currentClock = clocks[row][col];  

            // **Step 1: Open Mouth (2:20)**
            currentClock.update(pacmanOpenHour, pacmanOpenMinute);
            window.clear(sf::Color::White);
            for (const auto& rowVec : clocks) {
                for (const auto& clock : rowVec) {
                    clock.draw(window);
                }
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(pacmanDelay * 100)));

            // **Step 2: Close Mouth (3:15)**
            currentClock.update(pacmanClosedHour, pacmanClosedMinute);
            window.clear(sf::Color::White);
            for (const auto& rowVec : clocks) {
                for (const auto& clock : rowVec) {
                    clock.draw(window);
                }
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(animationDuration * 100)));
            //Direct Display to TargetHour
            clocks[row][col].update(targetAngles[col][row].first,  targetAngles[col][row].second);
        }
    } else {  // **Right to Left**
        pacmanOpenHour = 225;
        pacmanOpenMinute = 135;
        pacmanClosedHour = 180; 
        pacmanClosedMinute = 180;
        for (int col = 7; col >= 0; col--) {  
            Clock& currentClock = clocks[row][col];

            // **Step 1: Open Mouth (2:20)**
            currentClock.update(pacmanOpenHour, pacmanOpenMinute);
            window.clear(sf::Color::White);
            for (const auto& rowVec : clocks) {
                for (const auto& clock : rowVec) {
                    clock.draw(window);
                }
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(pacmanDelay * 100)));

            // **Step 2: Close Mouth (3:15)**
            currentClock.update(pacmanClosedHour, pacmanClosedMinute);
            window.clear(sf::Color::White);
            for (const auto& rowVec : clocks) {
                for (const auto& clock : rowVec) {
                    clock.draw(window);
                }
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(animationDuration * 100)));
            clocks[row][col].update(targetAngles[col][row].first,  targetAngles[col][row].second);
        }
    }
    }
}

void slideTransition(sf::RenderWindow& window, std::vector<std::vector<Clock>>& clocks, 
                     const std::vector<std::vector<std::pair<float, float>>>& currentAngles,
                     const std::vector<std::vector<std::pair<float, float>>>& wordAngles,
                     const std::vector<std::vector<std::pair<float, float>>>& targetAngles) {
    
    float slideDelay = 0.3f; // Delay per step

    // Compute total columns required for transition
    size_t timeCols = currentAngles.size();
    size_t wordCols = wordAngles.size();
    size_t targetCols = targetAngles.size();
    size_t totalCols = timeCols + wordCols + targetCols;

    // **Step 1: Create a transition buffer for all animations**
    std::vector<std::vector<std::pair<float, float>>> displayAngles(3, 
        std::vector<std::pair<float, float>>(totalCols, {-1, -1}));  // Initialize empty clocks

    // **Step 2: Fill `displayAngles` with Current Hour, Word, and Target Hour**
    
    // Fill the current hour into `displayAngles`
    for (size_t col = 0; col < timeCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            displayAngles[row][col] = currentAngles[col][row];
        }
    }

    // Fill the word (POLYTECH) after the current hour
    for (size_t col = 0; col < wordCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            displayAngles[row][timeCols + col] = wordAngles[col][row];
        }
    }

    // Fill the target hour after the word
    for (size_t col = 0; col < targetCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            displayAngles[row][timeCols + wordCols + col] = targetAngles[col][row];
        }
    }

    // **Step 3: Animate the Transition Using `displayAngles`**
    for (size_t step = 0; step <= totalCols - 8; step++) {
        window.clear(sf::Color::White);

        for (size_t col = 0; col < totalCols; col++) {
            if (col >= step && col - step < 8) {  // Ensure within visible area
                for (size_t row = 0; row < 3; row++) {
                    if (displayAngles[row][col].first != -1) { // Ensure valid clock angles
                        clocks[row][col - step].update(displayAngles[row][col].first, 
                                                       displayAngles[row][col].second);
                    }
            }
        }
        }
        // **Draw Everything**
        for (const auto& rowVec : clocks) {
            for (const auto& clock : rowVec) {
                clock.draw(window);
            }
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(slideDelay * 500)));
    }

    // **Step 4: Display Final Target Hour (Ensures Last Step is Stable)**
    window.clear(sf::Color::White);
    for (size_t col = 0; col < 8; col++) {  // Ensure only final 8 columns are drawn
        for (size_t row = 0; row < 3; row++) {
            clocks[row][col].update(displayAngles[row][col + totalCols - 8].first, 
                                    displayAngles[row][col + totalCols - 8].second);
        }
    }
    for (const auto& rowVec : clocks) {
        for (const auto& clock : rowVec) {
            clock.draw(window);
        }
    }
    window.display();
}