#include "DigitConfiguration.h"
#include <iostream>

// Defines the hand angles for each digit (0-9)
const std::map<std::string, std::vector<std::pair<float, float>>> digitConfigurations = {
    // **Numbers (0-9)**
    { "0L", {{0, 90}, {270, 90}, {0, 270}} }, { "0R", {{180, 90}, {270, 90}, {180, 270}} },
    { "1L", {{225, 225}, {315, 315}, {225, 225}} }, { "1R", {{90, 135}, {90, 270}, {270, 270}} },
    { "2L", {{0, 0}, {90, 0}, {270, 0}} }, { "2R", {{90, 180}, {270, 180}, {180, 180}} },
    { "3L", {{0, 0}, {0, 0}, {0, 0}} }, { "3R", {{90, 180}, {270, 180}, {270, 180}} },
    { "4L", {{90, 90}, {270, 0}, {225, 225}} }, { "4R", {{90, 90}, {270, 90}, {270, 270}} },
    { "5L", {{90, 0}, {270, 0}, {0, 0}} }, { "5R", {{180, 180}, {90, 180}, {270, 180}} },
    { "6L", {{90, 0}, {270, 90}, {270, 0}} }, { "6R", {{180, 180}, {90, 180}, {270, 180}} },
    { "7L", {{90, 0}, {225, 225}, {225, 225}} }, { "7R", {{90, 180}, {90, 270}, {270, 270}} },
    { "8L", {{90, 0}, {270, 0}, {0, 270}} }, { "8R", {{90, 180}, {270, 180}, {180, 270}} },
    { "9L", {{90, 0}, {270, 0}, {0, 0}} }, { "9R", {{90, 180}, {270, 180}, {270, 180}} },

    // **Letters for "POLYTECH"**
    { "PL", {{90, 0}, {270, 0}, {270, 270}} }, { "PR", {{90, 180}, {270, 180}, {315, 315}} },
    { "OL", {{0, 90}, {270, 90}, {0, 270}} }, { "OR", {{180, 90}, {270, 90}, {180, 270}} },
    { "LL", {{90, 90}, {90, 270}, {0, 270}} }, { "LR", {{315, 315}, {315, 315}, {180, 180}} },
    { "YL", {{90, 90}, {0, 270}, {0, 0}} }, { "YR", {{90, 90}, {180, 270}, {180, 270}} },
    { "TL", {{90, 90}, {0, 270}, {0, 270}} }, { "TR", {{315, 315}, {180, 180}, {180, 180}} },
    { "EL", {{0, 90}, {0, 270}, {0, 270}} }, { "ER", {{180, 180}, {180, 180}, {180, 180}} },
    { "CL", {{0, 90}, {90, 270}, {0, 270}} }, { "CR", {{180, 180}, {315, 315}, {180, 180}} },
    { "HL", {{90, 90}, {0, 270}, {270, 270}} }, { "HR", {{90, 90}, {180, 270}, {270, 270}} }
};


vector<vector<pair<float, float>>> getTextAngles(const std::string& text) {
    vector<vector<pair<float, float>>> angles;

    for (size_t i = 0; i < text.size(); i++) {
        std::string leftKey = text[i] + std::string("L");  // Ex: "1L", "2L"
        std::string rightKey = text[i] + std::string("R"); // Ex: "1R", "2R"

        if (digitConfigurations.find(leftKey) == digitConfigurations.end() ||
            digitConfigurations.find(rightKey) == digitConfigurations.end()) {
            throw out_of_range("Invalid character: " + text[i]);
        }

        // Ajouter la colonne gauche et droite
        angles.push_back(digitConfigurations.at(leftKey));
        angles.push_back(digitConfigurations.at(rightKey));
    }

    return angles;
}

