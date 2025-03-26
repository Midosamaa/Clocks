#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "../../supervisor/ClockMotion.h"

using namespace std;

void sendClockMotionToSupervisor(const ClockMotion& motion);

#endif // COMMUNICATION_H
