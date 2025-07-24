#include <i2c_fifo.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slave_i2c_handler.h"


static const uint I2C_SLAVE_ADDRESS = 0x17;
static const uint I2C_BAUDRATE = 100000; // 100 kHz

static const uint I2C_SLAVE_SDA_PIN = PICO_DEFAULT_I2C_SDA_PIN; // 4
static const uint I2C_SLAVE_SCL_PIN = PICO_DEFAULT_I2C_SCL_PIN; // 5

// variables
uint8_t buf[32];
int n = 0; // nième bit received from master (0 à 31)
volatile bool receivedTrame = false;

// Export the frame structure
struct i2c_frame frame;


void printFrame(void) {
    // print tab clocksPostion
    for (int i = 0; i < 4; i++) {
        printf("Clock %d:\n", i);
        printf("  ID: %u\n", frame.clocksPosition[i].clock_id);
        printf("  Hour Angle: %u degrees\n", frame.clocksPosition[i].hourAngle);
        printf("  Minute Angle: %u degrees\n", frame.clocksPosition[i].minAngle);
        printf("  Hour Direction: %d\n", frame.clocksPosition[i].hourDir);
        printf("  Minute Direction: %d\n", frame.clocksPosition[i].minDir);
        printf("\n");
    }
    
    // Print delta_t
    printf("Time to reach positions: %.3f seconds\n", frame.delta_t);
}


// Handler called from the I2C ISR
static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {

    case I2C_SLAVE_RECEIVE: // master has written some data
        while (i2c_get_read_available(i2c) && n < sizeof(buf)) {
            buf[n++] = i2c_read_byte(i2c);
        }
        break;

    case I2C_SLAVE_REQUEST: // master is requesting data
        // i2c_write_byte(i2c, frame.mem[context.mem_address]);
        break;

    case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
        if(n == 32){
            int offset = 0;
            for(int i = 0; i < 4; i++){
                frame.clocksPosition[i].clock_id = buf[offset++];
                // read hourAngle 
                frame.clocksPosition[i].hourAngle = (buf[offset] | ((uint16_t)buf[offset+1] << 8));
                offset += 2;
                // read minAngle
                frame.clocksPosition[i].minAngle = (buf[offset] | ((uint16_t)buf[offset+1] << 8));
                offset += 2;
                frame.clocksPosition[i].hourDir = buf[offset++];
                frame.clocksPosition[i].minDir = buf[offset++];
            }

            // copy last 4 bytes from buf to delta_t
            memcpy(&frame.delta_t, &buf[offset], sizeof(float));

            receivedTrame = true;

        } else {
            printf("Trame non complète, à redemander au master\n");
            // else ?? demander au master de renvoyer dernière trame
        }
        n = 0; 
        break;

    default:
        break;
    }
}


void setup_slaveI2C(void) { 
    gpio_init(I2C_SLAVE_SDA_PIN);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);

    gpio_init(I2C_SLAVE_SCL_PIN);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);

    i2c_init(i2c0, I2C_BAUDRATE);
    // configure I2C0 for slave mode
    i2c_slave_init(i2c0, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
}
