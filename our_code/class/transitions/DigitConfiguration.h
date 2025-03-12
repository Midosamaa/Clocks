#ifndef DIGITCONFIGURATION_H
#define DIGITCONFIGURATION_H

#include <map>
#include <vector>
#include <utility>
#include "Transition.h"

/*
 * Defines clock hand positions for digits 0-9.
 * 
 * Each digit consists of 3 rows × 2 columns of small clocks.
 * Each clock has two hand angles: hour and minute.
*/

using namespace std;

extern const map<string, vector<pair<float, float>>> digitConfigurations;

/**
 * Retrieves the corresponding clock hand angles for a given digit.
 * 
 * A vector of pairs, where each pair represents (hour angle, minute angle).
 */
vector<pair<float, float>> getDigitAngles(const string& key);

/**
 * Retrieves the angles for an entire HH:MM time format.
 * return: A vector containing the hand angles for all 4 digits.
 */
vector<vector<pair<float, float>>> getTextAngles(const std::string& text);

#endif // DIGITCONFIGURATION_H
