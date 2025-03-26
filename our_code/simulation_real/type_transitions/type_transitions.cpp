#include "type_transitions.h"
#include <iostream>

void pacman_vertical(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
            const vector<vector<pair<float, float>>>& targetAngles) {
    float pacmanOpenHour;  // 2:20 -> Open mouth
    float pacmanOpenMinute = 45;

    float pacmanClosedHour = 0;  // 3:15 -> Closed mouth
    float pacmanClosedMinute = 0; 

    for (int row = 0; row < 3; row++) {  
    if (row % 2 == 0) {  // **Left to Right**
        pacmanOpenHour = 315;
        pacmanOpenMinute = 45;
        pacmanClosedHour = 0; 
        pacmanClosedMinute = 0;
        for (int col = 0; col < 8; col++) {
            Clock& currentClock = clocks[row][col];
            bool isTargetClock = (row == targetRow && col == targetCol);

            // Step 1: Open Mouth (2:20)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanOpenHour, pacmanOpenMinute, window, speed);
            } else {
                currentClock.update(pacmanOpenHour, pacmanOpenMinute, window);
            }

            // Step 2: Close Mouth (3:15)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanClosedHour, pacmanClosedMinute, window, speed);
            } else {
                currentClock.update(pacmanClosedHour, pacmanClosedMinute, window);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds((int)(speed)));

            // Step 3: Set to target angle
            float targetH = targetAngles[col][row].first;
            float targetM = targetAngles[col][row].second;

            if (isTargetClock) {
                currentClock.update_with_send(targetH, targetM, window, speed);
            } else {
                currentClock.update(targetH, targetM, window);
            }
        }
    } else {  // **Right to Left**
        pacmanOpenHour = 225;
        pacmanOpenMinute = 135;
        pacmanClosedHour = 180; 
        pacmanClosedMinute = 180;
        for (int col = 7; col >= 0; col--) { 
            Clock& currentClock = clocks[row][col];
            bool isTargetClock = (row == targetRow && col == targetCol);

            // Step 1: Open Mouth (2:20)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanOpenHour, pacmanOpenMinute, window, speed);
            } else {
                currentClock.update(pacmanOpenHour, pacmanOpenMinute, window);
            }

            // Step 2: Close Mouth (3:15)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanClosedHour, pacmanClosedMinute, window, speed);
            } else {
                currentClock.update(pacmanClosedHour, pacmanClosedMinute, window);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds((int)(speed)));

            // Step 3: Set to target angle
            float targetH = targetAngles[col][row].first;
            float targetM = targetAngles[col][row].second;

            if (isTargetClock) {
                currentClock.update_with_send(targetH, targetM, window, speed);
            } else {
                currentClock.update(targetH, targetM, window);
            }
        }
    }
    }
}


void pacman_horizontal(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
            const vector<vector<pair<float, float>>>& targetAngles) {
    
    float pacmanOpenHour, pacmanOpenMinute;
    float pacmanClosedHour, pacmanClosedMinute;

    // **Single Loop for All Columns**
    for (int col = 0; col < 8; col++) {  
        if (col % 2 == 0) {  // **Even column (Bottom to Top)**
            pacmanOpenHour = 225;
            pacmanOpenMinute = 315;
            pacmanClosedHour = 270;
            pacmanClosedMinute = 270;

            for (int row = 2; row >= 0; row--) { // Move Bottom to Top
                Clock& currentClock = clocks[row][col];
                bool isTargetClock = (row == targetRow && col == targetCol);

            // Step 1: Open Mouth (2:20)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanOpenHour, pacmanOpenMinute, window, speed);
            } else {
                currentClock.update(pacmanOpenHour, pacmanOpenMinute, window);
            }

            // Step 2: Close Mouth (3:15)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanClosedHour, pacmanClosedMinute, window, speed);
            } else {
                currentClock.update(pacmanClosedHour, pacmanClosedMinute, window);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds((int)(speed)));

            // Step 3: Set to target angle
            float targetH = targetAngles[col][row].first;
            float targetM = targetAngles[col][row].second;

            if (isTargetClock) {
                currentClock.update_with_send(targetH, targetM, window, speed);
            } else {
                currentClock.update(targetH, targetM, window);
            }  
            }

        } else {  // **Odd column (Top to Bottom)**
            pacmanOpenHour = 45;
            pacmanOpenMinute = 135;
            pacmanClosedHour = 90;
            pacmanClosedMinute = 90;

            for (int row = 0; row < 3; row++) {  // Move Top to Bottom
                Clock& currentClock = clocks[row][col];
                bool isTargetClock = (row == targetRow && col == targetCol);

            // Step 1: Open Mouth (2:20)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanOpenHour, pacmanOpenMinute, window, speed);
            } else {
                currentClock.update(pacmanOpenHour, pacmanOpenMinute, window);
            }

            // Step 2: Close Mouth (3:15)
            if (isTargetClock) {
                currentClock.update_with_send(pacmanClosedHour, pacmanClosedMinute, window, speed);
            } else {
                currentClock.update(pacmanClosedHour, pacmanClosedMinute, window);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds((int)(speed)));

            // Step 3: Set to target angle
            float targetH = targetAngles[col][row].first;
            float targetM = targetAngles[col][row].second;

            if (isTargetClock) {
                currentClock.update_with_send(targetH, targetM, window, speed);
            } else {
                currentClock.update(targetH, targetM, window);
            }  
            }
        }
    }
}


void slideTransition_to_left(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles) {

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
                        if (row == targetRow && col == targetCol) {
                            clocks[row][col - step].update_with_send(displayAngles[row][col].first, displayAngles[row][col].second, window, speed);
                        } else {
                            clocks[row][col - step].update(displayAngles[row][col].first, displayAngles[row][col].second, window);
                        }
                    }
            }
        }
        }
    }
}


void slideTransition_to_right(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles) {
    
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
                        if (row == targetRow && col == targetCol) {
                            clocks[row][col].update_with_send(displayAngles[row][sourceCol].first, displayAngles[row][sourceCol].second, window, speed);
                        } else {
                            clocks[row][col].update(displayAngles[row][sourceCol].first, displayAngles[row][sourceCol].second, window);
                        }
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
        this_thread::sleep_for(chrono::milliseconds((int)(150)));
    }
}


void slideTransition_to_top(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles) {
    
    size_t timeCols = currentAngles.size();
    size_t wordCols = wordAngles.size();
    size_t targetCols = targetAngles.size();
    size_t totalRows = 3;  // Always 3 rows for the clock grid
    
    vector<vector<pair<float, float>>> displayAngles;


    // **Fill Current Hour 
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
                    if (row == targetRow && col == targetCol) {
                            clocks[row][col].update_with_send(displayAngles[row + step][col].first, displayAngles[row + step][col].second, window, speed);
                        } else {
                            clocks[row][col].update(displayAngles[row + step][col].first, displayAngles[row + step][col].second, window);
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
        this_thread::sleep_for(chrono::milliseconds((int)(150)));
    }
}

void wave(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, int number_waves){
    std::string waves="";
    for (int i=0; i< number_waves; i++){
        waves+="^&^&";
    }
        if (direction==1){
            slideTransition_to_left(window, clocks, currentAngles, getTextAngles(waves), targetAngles);
        }

        if (direction==2){
            slideTransition_to_right(window, clocks, currentAngles, getTextAngles(waves), targetAngles);
        }
        if (direction==3){
            slideTransition_to_bottom(window, clocks, currentAngles, getTextAngles(waves), targetAngles);
        }
}

void slideTransition_to_bottom(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                                const vector<vector<pair<float, float>>>& currentAngles,
                                const vector<vector<pair<float, float>>>& wordAngles,
                                const vector<vector<pair<float, float>>>& targetAngles) {
    size_t timeCols = currentAngles.size();
    size_t wordCols = wordAngles.size();
    size_t targetCols = targetAngles.size();
    size_t totalRows = 3;  // Always 3 rows for the clock grid
    
    vector<vector<pair<float, float>>> displayAngles;



    // Fill Target Hour
    vector<vector<pair<float, float>>> targetBuffer(totalRows);
    for (size_t col = 0; col < targetCols; col++) {
        for (size_t row = 0; row < totalRows; row++) {
            targetBuffer[row].push_back(targetAngles[col][row]);
        }
    }

    displayAngles.insert(displayAngles.end(), targetBuffer.begin(), targetBuffer.end());

    // Fill Words in the middle 
    vector<vector<pair<float, float>>> wordBuffer;
    size_t chunkSize = 4;  // Each chunk is 4 letters
    size_t wordChunks = ((wordCols / 2) + chunkSize - 1) / chunkSize; 
    size_t wordRows = wordChunks * 3;

    for (size_t chunk = 0; chunk < wordChunks; chunk++) {
        size_t startCol = chunk * chunkSize * 2;
        for (size_t row = 0; row < totalRows; row++) {
            vector<pair<float, float>> rowData;
            for (size_t col = startCol; col < startCol + (chunkSize * 2) && col < wordCols; col++) {
                rowData.push_back(wordAngles[col][row]);
            }
            if (wordBuffer.size() < wordRows) {
                wordBuffer.push_back(rowData);
            }
        }
    }

    // **Insert into Display Buffer**
    displayAngles.insert(displayAngles.end(), wordBuffer.begin(), wordBuffer.end());


    // **Fill Current Hour 
    vector<vector<pair<float, float>>> currentBuffer(totalRows);
    for (size_t col = 0; col < timeCols; col++) {
        for (size_t row = 0; row < totalRows; row++) {
            currentBuffer[row].push_back(currentAngles[col][row]);
        }
    }

    displayAngles.insert(displayAngles.end(), currentBuffer.begin(), currentBuffer.end());



    // Animate the Transition (Reverse: From Bottom to Top)
    size_t totalSteps = displayAngles.size() - totalRows;

    for (size_t step = totalSteps; step >= 0; step--) {  // Ensure smooth transition and stop correctly
        window.clear(sf::Color::White);
        // **Move visible rows downwards**
        for (size_t row = 0; row < totalRows; row++) {  
            if (step + row < displayAngles.size()) {  // Ensure within bounds
                for (size_t col = 0; col < min(displayAngles[row + step].size(), (size_t)8); col++) {
                    if (row == targetRow && col == targetCol) {
                            clocks[row][col].update_with_send(displayAngles[row + step][col].first, displayAngles[row + step][col].second, window, speed);
                        } else {
                            clocks[row][col].update(displayAngles[row + step][col].first, displayAngles[row + step][col].second, window);
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
        this_thread::sleep_for(chrono::milliseconds((300)));

        // Stop exactly when the last three rows are visible at the bottom and it goes 18446744073709551615 max value
        if (step == 0) break; 
    }
}


void stars(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, int number_stars){
        
    std::string stars="";

    for (int i=0; i< number_stars; i++){
        stars+="<>";
    }
        if (direction==1){
            slideTransition_to_left(window, clocks, currentAngles, getTextAngles(stars), targetAngles);
        }

        if (direction==2){
            slideTransition_to_right(window, clocks, currentAngles, getTextAngles(stars), targetAngles);
        }

        if (direction==3){
            slideTransition_to_top(window, clocks, currentAngles, getTextAngles(stars), targetAngles);
        }
         
}

void words(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, string word){

    if (direction==1){
        slideTransition_to_left(window, clocks, currentAngles, getTextAngles(word), targetAngles);
    }

    if (direction==2){
        slideTransition_to_right(window, clocks, currentAngles, getTextAngles(word), targetAngles);
    }

    if (direction==3){
        slideTransition_to_top(window, clocks, currentAngles, getTextAngles(word), targetAngles);
    }
    
}

void pacman(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles, int direction){
    if (direction == 2){
        pacman_horizontal(window, clocks, targetAngles);
    }
    if (direction == 1){
        pacman_vertical(window, clocks, targetAngles);
    }
}
