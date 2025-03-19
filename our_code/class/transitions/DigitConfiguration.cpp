#include "DigitConfiguration.h"
#include <iostream>

#define BIG 17.5
// Defines the hand angles for each digit (0-9)
const map<string, vector<pair<float, float>>> digitConfigurations = {
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

    // **Letters of the alphabet**
    { "AL", {{0, 90}, {270, 0}, {270, 270}} }, { "AR", {{180, 90}, {270, 180}, {270, 270}} },
    { "BL", {{90, 90}, {270, 0}, {270, 0}} }, { "BR", {{315, 3150}, {90, 180}, {270, 180}} },
    { "CL", {{0, 90}, {90, 270}, {0, 270}} }, { "CR", {{180, 180}, {315, 315}, {180, 180}} },
    { "DL", {{315, 315}, {90, 0}, {0, 270}} }, { "DR", {{90, 90}, {270, 180}, {270, 180}} },
    { "EL", {{0, 90}, {0, 270}, {0, 270}} }, { "ER", {{180, 180}, {180, 180}, {180, 180}} },
    { "FL", {{0, 90}, {0, 270}, {270, 270}} }, { "FR", {{180, 180}, {180, 180}, {315, 315}} },
    { "GL", {{0, 90}, {270, 90}, {0, 270}} }, { "GR", {{180, 90}, {180, 90}, {180, 270}} },
    { "HL", {{90, 90}, {0, 270}, {270, 270}} }, { "HR", {{90, 90}, {180, 270}, {270, 270}} },
    { "IL", {{90, 90}, {90, 270}, {270, 270}} }, { "IR", {{315, 315}, {315, 315}, {315, 315}} },
    { "JL", {{315, 315}, {315, 315}, {270, 0}} }, { "JR", {{180, 90}, {270, 90}, {270, 180}} },
    { "KL", {{90, 90}, {315, 45}, {270, 270}} }, { "KR", {{135, 135}, {315, 315}, {225, 225}} },
    { "LL", {{90, 90}, {90, 270}, {0, 270}} }, { "LR", {{315, 315}, {315, 315}, {180, 180}} },
    { "ML", {{90, 45}, {90, 270}, {270, 270}} }, { "MR", {{90, 135}, {90, 270}, {270, 270}} },
    { "NL", {{90, 60}, {90, 270}, {270, 270}} }, { "NR", {{90, 90}, {90, 270}, {270, 240}} },
    { "OL", {{0, 90}, {270, 90}, {0, 270}} }, { "OR", {{180, 90}, {270, 90}, {180, 270}} },
    { "PL", {{90, 0}, {270, 0}, {270, 270}} }, { "PR", {{90, 180}, {270, 180}, {315, 315}} },
    { "QL", {{0, 90}, {270, 90}, {0, 270}} }, { "QR", {{180, 90}, {270, 90}, {180, 45}} },
    { "RL", {{90, 0}, {45, 90}, {270, 270}} }, { "RR", {{90, 180}, {270, 180}, {225, 225}} },
    { "SL", {{95, 355}, {265, 355}, {265, 5}} }, { "SR", {{185, 85}, {175, 85}, {275, 175}} },
    { "TL", {{90, 90}, {0, 270}, {0, 270}} }, { "TR", {{315, 315}, {180, 180}, {180, 180}} },
    { "UL", {{90, 90}, {270, 90}, {0, 270}} }, { "UR", {{90, 90}, {270, 90}, {180, 270}} },
    { "VL", {{90, 90}, {270, 90}, {270, 45}} }, { "VR", {{90, 90}, {270, 90}, {135, 270}} },
    { "WL", {{90, 90}, {90, 270}, {270, 315}} }, { "WR", {{90, 90}, {90, 270}, {270, 225}} },
    { "XL", {{315, 315}, {45, 45}, {315, 315}} }, { "XR", {{315, 315}, {135, 135}, {225, 225}} },
    { "YL", {{90, 90}, {0, 270}, {0, 0}} }, { "YR", {{90, 90}, {180, 270}, {180, 270}} },
    { "ZL", {{315, 315}, {0, 0}, {315, 0}} }, { "ZR", {{315, 315}, {180, 135}, {180, 180}} },


    // **For waves**

    // rest
    { "-L", {{0, 180}, {0, 180}, {0, 180}} }, { "-R", {{0, 180}, {0, 180}, {0, 180}} },

    // bird 
    { "^L", {{330, 330}, {330, 330}, {330, 330}} }, { "^R", {{210, 210}, {210, 210}, {210, 210}} },
    
    { "&L", {{30, 30}, {30, 30}, {30, 30}} }, { "&R", {{150, 150}, {150, 150}, {150, 150}} },

    //big wave
    { "!L", {{135, 315}, {135, 315}, {135, 315}} }, { "!R", {{45, 225}, {45, 225}, {45, 225}} },

    //star

    //star_left
    { "<L", {{45+BIG, 45-BIG}, {360-BIG, BIG}, {315-BIG, 315+BIG}} }, { "<R", {{90, 45}, {180, 180}, {270, 315}} },

    //star right
    { ">L", {{135, 90}, {0, 0}, {225, 270}} }, { ">R", {{135-BIG, 135+BIG}, {180-BIG, 180+BIG}, {225-BIG, 225+BIG}} },



};


vector<vector<pair<float, float>>> getTextAngles(const string& text) {
    vector<vector<pair<float, float>>> angles;

    for (size_t i = 0; i < text.size(); i++) {
        string leftKey = text[i] + string("L");  // Ex: "1L", "2L"
        string rightKey = text[i] + string("R"); // Ex: "1R", "2R"

        // Vérifier si les clés existent, sinon utiliser "-"
        if (digitConfigurations.find(leftKey) == digitConfigurations.end() ||
            digitConfigurations.find(rightKey) == digitConfigurations.end()) {
            std::cerr << " Caractère inconnu remplacé par '-': " << text[i] << std::endl;
            leftKey = "-L";
            rightKey = "-R";
        }

        // Ajouter la colonne gauche et droite
        angles.push_back(digitConfigurations.at(leftKey));
        angles.push_back(digitConfigurations.at(rightKey));
    }

    return angles;
}


