#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "./squarewavePIO/squarewave.h"
#include "./i2c_slave/slave_i2c_handler.h"




int main() {

    stdio_init_all();
    sleep_ms(5000);  
    
    printf("Démarrage du programme\n");
    
    // initialize sm_completed
    sm_completed = 0;

    PIO pio[4];
    uint sm[4];
    uint offset[4];

    uint nb_pas = 720;

    // initilisation I2C
    setup_slaveI2C();

    // wait for a complete frame
    while (true) {  
        if (receivedTrame) {
            receivedTrame = false;
            printFrame();
            
            break;
        }
        sleep_ms(100);    
    }
    
    // motors configuration
    setup_pin_direction14();

    setup_sm_programm(pio ,sm , offset);
    send_pulses(pio, sm, nb_pas);
    
    printf("State machines configured\n");

    start_all_sm(pio, sm);
    
    sleep_ms(1000); // wait sart sm

    while (sm_completed != 0x0F) {  // 0x0F = 0b1111
       
        sleep_ms(100);    
    }

    printf("motors finished\n");

    unload_program(pio,sm,offset);

    return 0;

}