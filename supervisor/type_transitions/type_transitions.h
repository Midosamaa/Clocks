#ifndef TYPE_TRANSITIONS_H
#define TYPE_TRANSITIONS_H

#include "../features/Clock.h"
#include "../transitions/DigitConfiguration.h"
#include "../../receptor/communication.h"


const int speed = 1;  // Default transition speed for animations

// ----- Main transition effects -----

// Pac-Man effect: clocks are "eaten" in a chosen direction

void pacman(vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles, int direction);




// Pac-Man eating vertically (down or up)

void pacman_vertical(vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles);




// Pac-Man eating horizontally (left or right)

void pacman_horizontal(vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& targetAngles);



// Wavy animation between two time states

void wave(vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, int number_waves);


// Star-like burst effect between states

void stars(vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles, int direction, int number_stars);


// Temporary word transition 

void words(vector<vector<Clock>>& clocks, const vector<vector<pair<float, float>>>& currentAngles, const vector<vector<pair<float, float>>>& targetAngles,int direction, string word);


// ----- Slide helper functions used by word transition -----

void slideTransition_to_left(vector<vector<Clock>>& clocks, 
    const vector<vector<pair<float, float>>>& currentAngles,
    const vector<vector<pair<float, float>>>& wordAngles,
    const vector<vector<pair<float, float>>>& targetAngles);


void slideTransition_to_right(vector<vector<Clock>>& clocks, 
    const vector<vector<pair<float, float>>>& currentAngles,
    const vector<vector<pair<float, float>>>& wordAngles,
    const vector<vector<pair<float, float>>>& targetAngles);


void slideTransition_to_top(vector<vector<Clock>>& clocks, 
    const vector<vector<pair<float, float>>>& currentAngles,
    const vector<vector<pair<float, float>>>& wordAngles,
    const vector<vector<pair<float, float>>>& targetAngles);


void slideTransition_to_bottom(vector<vector<Clock>>& clocks, 
    const vector<vector<pair<float, float>>>& currentAngles,
    const vector<vector<pair<float, float>>>& wordAngles,
    const vector<vector<pair<float, float>>>& targetAngles);



void smoothSpinRevealTextThenTime(
    std::vector<std::vector<Clock>>& clocks,
    const std::vector<std::vector<std::pair<float, float>>>& startAngles,
    const std::vector<std::vector<std::pair<float, float>>>& wordAngles,
    const std::vector<std::vector<std::pair<float, float>>>& targetAngles);

#endif // TYPE_TRANSITIONS_H
