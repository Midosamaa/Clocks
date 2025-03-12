#ifndef TYPE_TRANSITIONS_H
#define TYPE_TRANSITIONS_H

#include "../features/Clock.h"
#include "../transitions/DigitConfiguration.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>

void pacman(sf::RenderWindow& window, std::vector<std::vector<Clock>>& clocks, 
            const std::vector<std::vector<std::pair<float, float>>>& targetAngles);

void slideTransition(sf::RenderWindow& window, std::vector<std::vector<Clock>>& clocks, 
                     const std::vector<std::vector<std::pair<float, float>>>& currentAngles,
                     const std::vector<std::vector<std::pair<float, float>>>& wordAngles,
                     const std::vector<std::vector<std::pair<float, float>>>& targetAngles);


#endif // TYPE_TRANSITIONS_H
