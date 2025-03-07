#include "DigitClock.hpp"
#include <map>

std::map<int, std::vector<std::pair<float, float>>> digitConfigurations = {
    {0, {{90, 180}, {0, 180}, {90, 0}, {270, 180}, {0, 180}, {270, 0}}},
    {1, {{315, 315}, {45, 45}, {315, 315}, {180, 225}, {180, 0}, {0, 0}}},
    {2, {{90, 90}, {180, 90}, {0, 90}, {180, 270}, {0, 270}, {270, 270}}},
    {3, {{90, 90}, {90, 90}, {90, 90}, {180, 270}, {0, 270}, {0, 270}}},
    {4, {{180, 180}, {0, 90}, {315, 315}, {180, 180}, {0, 180}, {0, 0}}},
    {5, {{180, 90}, {0, 90}, {90, 90}, {270, 270}, {180, 270}, {0, 270}}},
    {6, {{180, 90}, {0, 180}, {0, 90}, {270, 270}, {180, 270}, {0, 270}}},
    {7, {{180, 90}, {315, 315}, {315, 315}, {180, 270}, {180, 0}, {0, 0}}},
    {8, {{180, 90}, {0, 90}, {90, 0}, {180, 270}, {0, 270}, {270, 0}}},
    {9, {{180, 90}, {0, 90}, {90, 90}, {180, 270}, {0, 270}, {0, 270}}}
};

DigitClock::DigitClock(float x, float y) : Clock(x, y) {}

void DigitClock::configure(int digit, int index) {
    if (digitConfigurations.find(digit) != digitConfigurations.end()) {
        setTargetTime(digitConfigurations[digit][index].first,
                      digitConfigurations[digit][index].second);
    }
}
