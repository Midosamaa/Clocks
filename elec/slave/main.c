#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "./squarewavePIO/squarewave.h"
#include "./i2c_slave/slave_i2c_handler.h"


static uint state = 0; // goes 0 to 5


int main() {

    stdio_init_all();
    sleep_ms(5000);  
    
    printf("Démarrage du programme\n");
    
    // initialize sm_completed
    sm_completed = 0;

    PIO pio[8];
    uint sm[8];
    uint offset[8];

    uint16_t currentPosition[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}; // current position of each clock hand {hourAngle, minAngle}
    uint16_t nb_pas[4][2]; // number of steps for each clock hand  {{PasClock1Hour, PasClock1min}...}
    uint16_t divf[4][2]; // frequency divisor for each clock hand {{divfClock1Hour, divfClock1min}...}
    bool direction[4][2]; // direction for each clock hand 

    // initilisation I2C
    setup_slaveI2C();

    // motors configuration
    setup_pin_direction();
    setup_sm_programm(pio ,sm , offset, divf);

    // wait for a complete frame
    while (true) {  

        switch (state){
            case 0 : 
                // wait for a new frame
                if(receivedTrame) {
                    state = 1; 
                    receivedTrame = false; // reset flag
                }
                break;

            case 1 : 
                // i2c frame received
                printFrame();

                // update structures
                for(int i = 0; i < 2; i+2) {
                    nb_pas[i][0] = calculate_nbPas(frame.clocksPosition[i].hourAngle, currentPosition[i][0]); // calculate number of steps for each clock hand
                    nb_pas[i][1] = calculate_nbPas(frame.clocksPosition[i].minAngle, currentPosition[i][1]); 
                    divf[i][0] = calculate_divf(nb_pas[i][0], frame.delta_t);  // calculate frequency divisor for each clock hand
                    divf[i][1] = calculate_divf(nb_pas[i][1], frame.delta_t);
                    direction[i][0] = frame.clocksPosition[i].hourDir; // update direction
                    direction[i][1] = frame.clocksPosition[i].minDir;
                    currentPosition[i][0] = frame.clocksPosition[i].hourAngle; // update current position
                    currentPosition[i][1] = frame.clocksPosition[i].minAngle;
                }
                
                state = 2;
                break;
            
            case 2 : 
                    // Send received data to motors
                    send_pulses(pio, sm, nb_pas);
                    send_direction(direction); /*TODO : add direction via pio*/
                    printf("State machines configured\n");
                    state = 3;
                break;

            case 3 :
                // start all state machines
                start_all_sm(pio, sm);
                state = 4;
                break;
            
            case 4:
                // wait for all state machines to complete
                if (sm_completed == 0x0FF) { // 0x0FF = 0b1111 1111 - 8 sm completed
                    printf("All state machines completed\n");
                    stop_all_sm(pio, sm);
                    unload_program(pio, sm, offset);
                    state = 5; 
                }
                break;   
            
            case 5 : 
                // stop all state machines
                stop_all_sm(pio, sm);
                state = 0;
                break;
                            
        }
        sleep_ms(100);    
    }
    
    printf("Program over\n");

    return 0;

}