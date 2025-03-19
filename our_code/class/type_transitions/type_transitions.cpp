#include "type_transitions.h"
#include <iostream>

void pacman(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
            const vector<vector<pair<float, float>>>& targetAngles) {
    float pacmanOpenHour;  // 2:20 -> Open mouth
    float pacmanOpenMinute = 45;

    float pacmanClosedHour = 0;  // 3:15 -> Closed mouth
    float pacmanClosedMinute = 0; 

    float pacmanDelay = 0.5f;
    int animationspeed = 150;

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
            this_thread::sleep_for(chrono::milliseconds((int)(pacmanDelay * animationspeed)));

            // **Step 2: Close Mouth (3:15)**
            currentClock.update(pacmanClosedHour, pacmanClosedMinute);
            window.clear(sf::Color::White);
            for (const auto& rowVec : clocks) {
                for (const auto& clock : rowVec) {
                    clock.draw(window);
                }
            }
            window.display();
            this_thread::sleep_for(chrono::milliseconds((int)(pacmanDelay * animationspeed)));
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
            this_thread::sleep_for(chrono::milliseconds((int)(pacmanDelay * animationspeed)));

            // **Step 2: Close Mouth (3:15)**
            currentClock.update(pacmanClosedHour, pacmanClosedMinute);
            window.clear(sf::Color::White);
            for (const auto& rowVec : clocks) {
                for (const auto& clock : rowVec) {
                    clock.draw(window);
                }
            }
            window.display();
            this_thread::sleep_for(chrono::milliseconds((int)(pacmanDelay * animationspeed)));
            clocks[row][col].update(targetAngles[col][row].first,  targetAngles[col][row].second);
        }
    }
    }
}

void slideTransition_from_left(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles) {
    float slideDelay = 0.3f; // Delay per step

    // Compute total columns required for transition
    size_t timeCols = currentAngles.size();
    size_t wordCols = wordAngles.size();
    size_t targetCols = targetAngles.size();
    size_t totalCols = timeCols + wordCols + targetCols;

    // **Step 1: Create a transition buffer for all animations**
    vector<vector<pair<float, float>>> displayAngles(3, 
        vector<pair<float, float>>(totalCols, {-1, -1}));  // Initialize empty clocks

    // **Step 2: Fill `displayAngles` with Current Hour, Word, and Target Hour**
    // Fill the current hour first donc il ecrase pas 
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
            if (col >= step && col - step < 8) { 
                for (size_t row = 0; row < 3; row++) {
                    if (displayAngles[row][col].first != -1) { 
                        clocks[row][col - step].update(displayAngles[row][col].first, 
                                                       displayAngles[row][col].second);
                    }
            }
        }
        }

        for (const auto& rowVec : clocks) {
            for (const auto& clock : rowVec) {
                clock.draw(window);
            }
        }
        window.display();
        this_thread::sleep_for(chrono::milliseconds((int)(slideDelay * 500)));
    }
}


void slideTransition_from_right(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles) {
    
    float slideDelay = 0.3f; // Delay per step
    size_t timeCols = currentAngles.size();
    size_t wordCols = wordAngles.size();
    size_t targetCols = targetAngles.size();
    size_t totalCols = timeCols + wordCols + targetCols;

    // **Step 1: Create a transition buffer for all animations**
    vector<vector<pair<float, float>>> displayAngles(3,vector<pair<float, float>>(totalCols, {-1, -1}));  // Initialize empty clocks

    // **Step 2: Fill `displayAngles` with Current Hour, Word, and Target Hour**
    // Fill the target hour at first
    for (size_t col = 0; col < targetCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            displayAngles[row][col] = targetAngles[col][row];
        }
    }
    
    // Fill the word (POLYTECH) after the target hour
    for (size_t col = 0; col < wordCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            displayAngles[row][timeCols + col] = wordAngles[col][row];
        }
    }

    // Fill the Current hour at last
    for (size_t col = 0; col < timeCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            displayAngles[row][timeCols + wordCols + col] = currentAngles[col][row];
        }
    }

    for (int step = totalCols - 8; step >= 0; step--) {  // Moves Left to Right
        window.clear(sf::Color::White);

        for (int col = 0; col < 8; col++) { // Iterate over only the visible area
            size_t sourceCol = col + step;  // Get the source column

            if (sourceCol < totalCols) {  // Ensure it's within bounds
                for (size_t row = 0; row < 3; row++) {
                    if (displayAngles[row][sourceCol].first != -1) {  
                        clocks[row][col].update(displayAngles[row][sourceCol].first, 
                                                displayAngles[row][sourceCol].second);
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
        this_thread::sleep_for(chrono::milliseconds((int)(slideDelay * 500)));
    }
}


void slideTransition_from_bottom(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles) {
    
    float slideDelay = 0.3f; // Delay per step
    size_t timeCols = currentAngles.size();
    size_t wordCols = wordAngles.size();
    size_t targetCols = targetAngles.size();
    size_t totalRows = 3;  // Always 3 rows for the clock grid
    
    vector<vector<pair<float, float>>> displayAngles;


    // **Fill Current Hour at the TOPs
    vector<vector<pair<float, float>>> currentBuffer(totalRows);
    for (size_t col = 0; col < timeCols; col++) {
        for (size_t row = 0; row < totalRows; row++) {
            currentBuffer[row].push_back(currentAngles[col][row]);
        }
    }

    displayAngles.insert(displayAngles.end(), currentBuffer.begin(), currentBuffer.end());

    // Fill Words in the middle 
    vector<vector<pair<float, float>>> wordBuffer;
    size_t chunkSize = 4;  // Each chunk is 4 letters
    size_t wordChunks = ((wordCols / 2) + chunkSize - 1) / chunkSize; 
    size_t wordRows = wordChunks *3;

    for (size_t chunk = 0; chunk < wordChunks; chunk++) {
        size_t startCol = chunk * chunkSize*2;
        for (size_t row = 0; row < totalRows; row++) {
            vector<pair<float, float>> rowData;
            for (size_t col = startCol; col < startCol + (chunkSize*2) && col < wordCols; col++) {
                rowData.push_back(wordAngles[col][row]);
            }
            if (wordBuffer.size() < wordRows) {
                wordBuffer.push_back(rowData);
            }
        }
    }

    // **Insert into Display Buffer**
    displayAngles.insert(displayAngles.end(), wordBuffer.begin(), wordBuffer.end());

    //Fill Target Hour at BOTTOM
    vector<vector<pair<float, float>>> targetBuffer(totalRows);
    for (size_t col = 0; col < targetCols; col++) {
        for (size_t row = 0; row < totalRows; row++) {
            targetBuffer[row].push_back(targetAngles[col][row]);
        }
    }

    displayAngles.insert(displayAngles.end(), targetBuffer.begin(), targetBuffer.end());

    // Animate the Transition
    size_t totalSteps = displayAngles.size() - totalRows;
    for (size_t step = 0; step <= totalSteps; step++) {  // Moves rows up
        window.clear(sf::Color::White);
        
        // **Move visible rows upwards**
        for (size_t row = 0; row < totalRows; row++) {  // Only shift visible rows
            if (row + step < displayAngles.size()) {  // Ensure within bounds
                for (size_t col = 0; col < min(displayAngles[row + step].size(), (size_t)8); col++) {
                    clocks[row][col].update(displayAngles[row + step][col].first, 
                                            displayAngles[row + step][col].second);
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
        this_thread::sleep_for(chrono::milliseconds((int)(slideDelay * 500)));
    }
}

void wave(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
    const vector<vector<pair<float, float>>>& currentAngles,
    const vector<vector<pair<float, float>>>& targetAngles,
    int direction){

        if (direction==1){
            slideTransition_from_left(window, clocks, currentAngles, getTextAngles("^&^&"), targetAngles);
        }

            if (direction==2){
                slideTransition_from_right(window, clocks, currentAngles, getTextAngles("^&^&"), targetAngles);
            }
    
            
    }
