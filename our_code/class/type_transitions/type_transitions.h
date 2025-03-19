#ifndef TYPE_TRANSITIONS_H
#define TYPE_TRANSITIONS_H

#include "../features/Clock.h"
#include "../transitions/DigitConfiguration.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>

//transitions
void pacman_vertical(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles);

void pacman_horizontal(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles);

void wave(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, int number_waves);

void stars(sf::RenderWindow& window, vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, int number_stars);

void words(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
    const vector<vector<pair<float, float>>>& currentAngles,
    const vector<vector<pair<float, float>>>& targetAngles,
    int direction, string word);

    
//helpful methods
void slideTransition_to_left(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles);

void slideTransition_to_right(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles);


void slideTransition_to_top(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                     const vector<vector<pair<float, float>>>& currentAngles,
                     const vector<vector<pair<float, float>>>& wordAngles,
                     const vector<vector<pair<float, float>>>& targetAngles);


void slideTransition_to_bottom(sf::RenderWindow& window, vector<vector<Clock>>& clocks, 
                                const vector<vector<pair<float, float>>>& currentAngles,
                                const vector<vector<pair<float, float>>>& wordAngles,
                                const vector<vector<pair<float, float>>>& targetAngles);


#endif // TYPE_TRANSITIONS_H
