#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "ClockMotion.h"

const int targetRow = 0;
const int targetCol = 0;

using namespace std;

void sendClockMotionToReceptor(const ClockMotion& motion);

#endif // COMMUNICATION_H
