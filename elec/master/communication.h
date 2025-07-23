#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;


// Structure representing the rotation angles of a clock - 7 bytes
static struct ClockMotion {
    uint8_t clock_id;       // 0 <= x <= 23
    uint16_t hourAngle;     // Angle for the hour hand - 0<=X<=359
    uint16_t minuteAngle;   // Angle for the minute hand - 0<=X<=359
    bool hourDir;        // 0, 1 
    bool minuteDir;      // 0, 1 
}  ;


// frame i2c to inform slaves of their next positions - 28 bytes
static struct frame{
    ClockMotion clocksPosition; // Tableau de 4 ou envoyer 4 fois la trame ?
    float delta_t; // time to reach the positions entered in clocksPosition
} ;


#endif // COMMUNICATION_H
