#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define method1

static const uint I2C_SLAVE_ADDRESS = 0x17;
static const uint I2C_BAUDRATE = 100000; // 100 kHz

static const uint I2C_MASTER_SDA_PIN = 6;
static const uint I2C_MASTER_SCL_PIN = 7;


// Structure representing the rotation angles of a clock - 7 bytes
static struct ClockMotion {
    uint8_t clock_id;       // 0 <= x <= 23
    uint16_t hourAngle;     // Angle for the hour hand - 0<=X<=359
    uint16_t minAngle;   // Angle for the minute hand - 0<=X<=359
    bool hourDir;        // 0, 1 
    bool minDir;      // 0, 1 
}ClockMotion;


// frame i2c to inform slaves of their next positions - 28 bytes -> 29 with written
static struct frame {
    struct ClockMotion clocksPosition[4];
    float delta_t; // time to reach the positions entered in clocksPosition
} frame; 


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

void remplirTrame(void) {
    uint8_t i = 0;
    uint16_t hAngle = 0, mAngle = 0;
    // bool hdir = 0, mdir = 0;

    for (i = 0; i < 4; i++) {
        frame.clocksPosition[i].clock_id = i;
        frame.clocksPosition[i].hourAngle = hAngle + 45;
        frame.clocksPosition[i].minAngle = mAngle + 45;
        frame.clocksPosition[i].hourDir = 1;
        frame.clocksPosition[i].minDir = 0;
    }
    
    frame.delta_t = (float) 5.0;
    printFrame();
}


static void run_master() {
    gpio_init(I2C_MASTER_SDA_PIN);
    gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    // pull-ups are already active on slave side, this is just a fail-safe in case the wiring is faulty
    gpio_pull_up(I2C_MASTER_SDA_PIN);

    gpio_init(I2C_MASTER_SCL_PIN);
    gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_MASTER_SCL_PIN);

    i2c_init(i2c1, I2C_BAUDRATE);

    #ifdef method1

        uint8_t buf[32]; // 1o for address + 29o data
            
        // manual serialisation in the announced struct order
        int offset = 0;

        // copy of clocksPosition
        for (int i = 0; i < 4; i++) {
            buf[offset++] = frame.clocksPosition[i].clock_id;
            
            // hourAngle - 16 bits
            buf[offset++] = frame.clocksPosition[i].hourAngle & 0xFF; // lSb first
            buf[offset++] = (frame.clocksPosition[i].hourAngle >> 8) & 0xFF; // then msb
            
            // minAngle - 16 bits
            buf[offset++] = frame.clocksPosition[i].minAngle & 0xFF;
            buf[offset++] = (frame.clocksPosition[i].minAngle >> 8) & 0xFF;
            
            buf[offset++] = frame.clocksPosition[i].hourDir;
            buf[offset++] = frame.clocksPosition[i].minDir;
        }

        // Copier delta_t (4 bytes)
        memcpy(&buf[offset], &frame.delta_t, sizeof(float));
        offset += sizeof(float);

        // Vérificaiton buffer 32 octets
        printf("Taille du buffer rempli: %d octets\n", offset);
        while (offset < 32) {
            buf[offset++] = 0;  // Padding with zeros
        }

        int count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, offset, false);

        #ifdef DEBUG
            printf("\nBuffer POst envoi\n");
            for (int i = 0; i < 32; i++) {
                printf("%d ", buf[i]);  // %3d pour aligner les nombres jusqu'à 255
                if ((i + 1) % 8 == 0) 
                    printf("\n");
            }
        #endif

    # else // try and add __attribute__((packed)) in the structs declaration -> avoid automatic padding
        
        int count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, &frame, 29, false); // size of frame

    #endif
    if (count < 0) {
        printf("count négatif\n");
        puts("Couldn't write to slave, please check your wiring!");
        return;
    }else{
        printf("count positif\n");
    }
    hard_assert(count == offset);

    puts("");
    sleep_ms(2000);

}


int main() {
    stdio_init_all();
    puts("\nI2C master");

    sleep_ms(5000);
    printf("Starting I2C master...\n");

    remplirTrame();
    run_master();
    printf("fin programme\n");
}








// char msg[32];
// snprintf(msg, sizeof(msg), "Hello, I2C slave! - 0x%02X", mem_address);
// uint8_t msg_len = strlen(msg);


// request info from the slave
// // seek to mem_address
// count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, 1, true);
// hard_assert(count == 1);
// // partial read
// uint8_t split = 5;
// count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, split, true);
// hard_assert(count == split);
// buf[count] = '\0';
// printf("Read  at 0x%02X: '%s'\n", mem_address, buf);
// hard_assert(memcmp(buf, msg, split) == 0);
// // read the remaining bytes, continuing from last address
// count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, msg_len - split, false);
// hard_assert(count == msg_len - split);
// buf[count] = '\0';
// printf("Read  at 0x%02X: '%s'\n", mem_address + split, buf);
// hard_assert(memcmp(buf, msg + split, msg_len - split) == 0);
