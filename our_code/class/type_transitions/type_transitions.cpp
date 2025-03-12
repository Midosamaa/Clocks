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
    
    float slideDelay = 0.3f; // Temps entre chaque déplacement

    size_t totalCols = 8;
    size_t wordCols = wordAngles.size();
    size_t timeCols = currentAngles.size();

    // **Étape 2: Décaler l'heure vers la gauche et introduire POLY**
    for (size_t step = 0; step <= wordCols; step++) {
        window.clear(sf::Color::White);

        // Décaler l'heure vers la gauche
        for (size_t col = 0; col < timeCols; col++) {
            if (col >= step) {
                for (size_t row = 0; row < 3; row++) {
                    clocks[row][col - step].update(currentAngles[col][row].first, 
                                                   currentAngles[col][row].second);
                }
            }
        }

        // Afficher POLY à droite
        for (size_t col = 0; col < step && col < wordCols; col++) {
            if (totalCols - step + col < totalCols) {
                for (size_t row = 0; row < 3; row++) {
                    clocks[row][totalCols - step + col].update(wordAngles[col][row].first, 
                                                               wordAngles[col][row].second);
                }
            }
        }

        // Dessiner l'animation
        for (const auto& rowVec : clocks) {
            for (const auto& clock : rowVec) {
                clock.draw(window);
            }
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(slideDelay * 500)));
    }


    // **Étape 3: Décaler POLY vers la gauche et introduire la nouvelle heure**
    for (size_t step = 0; step <= timeCols; step++) {
        window.clear(sf::Color::White);

        // Décaler POLY vers la gauche
        for (size_t col = 0; col < wordCols; col++) {
            if (col >= step) {
                for (size_t row = 0; row < 3; row++) {
                    clocks[row][col - step].update(wordAngles[col][row].first, 
                                                   wordAngles[col][row].second);
                }
            }
        }

        // Introduce the New Time from the Right
        for (size_t col = 0; col < step && col < timeCols; col++) {
            for (size_t row = 0; row < 3; row++) {
                clocks[row][totalCols - step + col].update(targetAngles[col][row].first, 
                                                           targetAngles[col][row].second);
            }
        }

        // Dessiner l'animation
        for (const auto& rowVec : clocks) {
            for (const auto& clock : rowVec) {
                clock.draw(window);
            }
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(slideDelay * 500)));
    }

    // **Affichage final avec la nouvelle heure**
    window.clear(sf::Color::White);
    for (size_t col = 0; col < timeCols; col++) {
        for (size_t row = 0; row < 3; row++) {
            clocks[row][col].update(targetAngles[col][row].first, 
                                    targetAngles[col][row].second);
        }
    }
    for (const auto& rowVec : clocks) {
        for (const auto& clock : rowVec) {
            clock.draw(window);
        }
    }
    window.display();
}