#ifndef SLAVE_I2C_HANDLER_H
#define SLAVE_I2C_HANDLER_H

#include <pico/stdlib.h>
#include <i2c_slave.h>

// Structure representing the rotation angles of a clock
struct ClockMotion {
    uint8_t clock_id;       // 0 <= x <= 23
    uint16_t hourAngle;     // Angle for the hour hand - 0<=X<=359
    uint16_t minAngle;      // Angle for the minute hand - 0<=X<=359
    bool hourDir;           // 0, 1 
    bool minDir;            // 0, 1 
};

// frame i2c to inform slaves of their next positions
struct i2c_frame {
    struct ClockMotion clocksPosition[4];
    float delta_t; // time to reach the positions entered in clocksPosition
};

extern struct i2c_frame frame;

// Extern declaration of the flag indicating frame reception
extern volatile bool receivedTrame;

// Functions exported by the I2C module
void setup_slaveI2C(void);
void printFrame(void);



#endif // SLAVE_I2C_HANDLER_H
