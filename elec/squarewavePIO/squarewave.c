#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "squarewave.pio.h"

#define GPIO_PIN0 10
#define GPIO_PIN1 12
#define GPIO_PIN2 13
#define GPIO_PIN3 11

#define GPIO_DIR_A 14
#define GPIO_RESET 15
// #define vid6606

// A square wave, period of around 1748us by using a clock div of 65535
#define CLOCK_DIVISOR 18750



int main() {

    #ifdef vid6606
        // Reset pin vid6606 to 0 for 1 ms
        gpio_init(GPIO_RESET);
        gpio_set_dir(GPIO_RESET, GPIO_OUT);
        gpio_put(GPIO_RESET, 0);  
        sleep_ms(10);              
        gpio_put(GPIO_RESET, 1);  
    #endif 

    // direction GPIO14
    gpio_init(GPIO_DIR_A);
    gpio_set_dir(GPIO_DIR_A, GPIO_OUT);
    gpio_put(GPIO_DIR_A, 1);  // CW

    PIO pio[4];
    uint sm[4];
    uint offset[4];
    bool success;

    // Load the program onto the first pio
    success = setup_pio(&squarewave_program, &pio[0], &sm[0], &offset[0], GPIO_PIN0, CLOCK_DIVISOR);
    hard_assert(success);
    assert(pio[0] == pio_get_instance(NUM_PIOS - 1)); 

    // Load the program onto the next state machine
    success = setup_pio(&squarewave_program, &pio[1], &sm[1], &offset[1], GPIO_PIN1, CLOCK_DIVISOR);
    hard_assert(success);
    assert(pio[1] == pio_get_instance(NUM_PIOS - 1)); 

    success = setup_pio(&squarewave_program, &pio[2], &sm[2], &offset[2], GPIO_PIN2, CLOCK_DIVISOR);
    hard_assert(success);
    assert(pio[2] == pio_get_instance(NUM_PIOS - 1)); 

    success = setup_pio(&squarewave_program, &pio[3], &sm[3], &offset[3], GPIO_PIN3, CLOCK_DIVISOR);
    hard_assert(success);
    assert(pio[3] == pio_get_instance(NUM_PIOS - 1)); 

    // cf restart programm
    // pio_clkdiv_restart_sm_multi_mask(pio[0], 1 << sm[2], (1 << sm[0]) | (1 << sm[1]), 0);

    // enable ALL state machines with the divisors all in sync
    pio_enable_sm_multi_mask_in_sync(pio[0], 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0);

    // run the programs for x ms
    sleep_ms(1000000);

    // stop all state machines
    pio_set_sm_multi_mask_enabled(pio[0], 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0, false);

    // free resources and unload the program
    assert(pio[0] == pio[1] && pio[1] == pio[2] && pio[2] == pio[3]);
    pio_remove_program_and_unclaim_sm(&squarewave_program, pio[0], sm[0], offset[0]);
    pio_remove_program_and_unclaim_sm(&squarewave_program, pio[1], sm[1], offset[1]);
    pio_remove_program_and_unclaim_sm(&squarewave_program, pio[2], sm[2], offset[2]);
    pio_remove_program_and_unclaim_sm(&squarewave_program, pio[3], sm[3], offset[3]);


    return 0;

}
