#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "./squarewavePIO/squarewave.h"




int main() {

    stdio_init_all();
    sleep_ms(1000);  
    
    printf("Démarrage du programme\n");
    sleep_ms(2000);
    
    // initialize sm_completed
    sm_completed = 0;



    PIO pio[4];
    uint sm[4];
    uint offset[4];

    uint nb_pas = 720;

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