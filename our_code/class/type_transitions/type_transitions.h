#ifndef TYPE_TRANSITIONS_H
#define TYPE_TRANSITIONS_H

#include "../features/Clock.h"
#include "../transitions/DigitConfiguration.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>

void pacman(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles);

void slideTransition_from_left(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles);

void slideTransition_from_right(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles);


void slideTransition_from_bottom(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles);


#endif // TYPE_TRANSITIONS_H
