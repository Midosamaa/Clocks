#include "DigitConfiguration.h"
#include <iostream>

// Defines the hand angles for each digit (0-9)
const map<int, vector<pair<float, float>>> digitConfigurations ={
    {0, {{0, 90}, {270, 90}, {0, 270}, {180, 90}, {270, 90}, {180, 270}}},
    {1, {{225, 225}, {315, 315}, {225, 225}, {90, 135}, {90, 270}, {270, 270}}},
    {2, {{0, 0}, {90, 0}, {270, 0}, {90, 180}, {270, 180}, {180, 180}}},
    {3, {{0, 0}, {0, 0}, {0, 0}, {90, 180}, {270, 180}, {270, 180}}},
    {4, {{90, 90}, {270, 0}, {225, 225}, {90, 90}, {270, 90}, {270, 270}}},
    {5, {{90, 0}, {270, 0}, {0, 0}, {180, 180}, {90, 180}, {270, 180}}},
    {6, {{90, 0}, {270, 90}, {270, 0}, {180, 180}, {90, 180}, {270, 180}}},
    {7, {{90, 0}, {225, 225}, {225, 225}, {90, 180}, {90, 270}, {270, 270}}},
    {8, {{90, 0}, {270, 0}, {0, 270}, {90, 180}, {270, 180}, {180, 270}}},
    {9, {{90, 0}, {270, 0}, {0, 0}, {90, 180}, {270, 180}, {270, 180}}}
};


vector<pair<float, float>> getDigitAngles(int digit) {
    if (digitConfigurations.find(digit) == digitConfigurations.end()) {
        throw out_of_range("Invalid digit: must be between 0-9.");
    }
    return digitConfigurations.at(digit);
}


vector<vector<pair<float, float>>> getTimeAngles(int hours, int minutes) {
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        throw out_of_range("Invalid time: hours must be 0-23, minutes 0-59.");
    }

    int h1 = hours / 10;
    int h2 = hours % 10;
    int m1 = minutes / 10;
    int m2 = minutes % 10;

    return { getDigitAngles(h1), getDigitAngles(h2), getDigitAngles(m1), getDigitAngles(m2) };
}
