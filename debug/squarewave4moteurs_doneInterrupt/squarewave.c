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

#define N_PASx2 720 // N_PULSES = N_PAS*2

// follow finished sm
volatile uint8_t sm_completed = 0;


void pio_irq_handler0() {
    pio_interrupt_clear(pio0, 0); // acquit interrupt
    sm_completed |= (1 << 0); // SM0 finished
}

void pio_irq_handler1() {
    pio_interrupt_clear(pio0, 1);
    sm_completed |= (1 << 1);
}

void pio_irq_handler2() {
    pio_interrupt_clear(pio0, 2);
    sm_completed |= (1 << 2);
}

void pio_irq_handler3() {
    pio_interrupt_clear(pio0, 3);
    sm_completed |= (1 << 3);
}





int main() {

    stdio_init_all();
    sleep_ms(1000);  
    
    printf("Démarrage du programme\n");
    sleep_ms(2000);
    
    // initialize sm_completed
    sm_completed = 0;

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
    gpio_put(GPIO_DIR_A, 0);  // CCW - Essayer l'autre direction

    PIO pio[4];
    uint sm[4];
    uint offset[4];
    bool success;

    irq_handler_t handlers[4] = {pio_irq_handler0, pio_irq_handler1, pio_irq_handler2, pio_irq_handler3};

    for(int i = 0; i < 4; i++) {
        uint pin = 0;
        switch (i){
            case 0: 
                pin = GPIO_PIN0; 
                break;
            case 1: 
                pin = GPIO_PIN1; 
                break;
            case 2: 
                pin = GPIO_PIN2; 
                break;
            case 3: 
                pin = GPIO_PIN3; 
                break;
        }

        // Load the program onto the first pio
        success = setup_pio(&squarewave_program, &pio[i], &sm[i], &offset[i], GPIO_PIN0, CLOCK_DIVISOR, i, handlers[i]);
        hard_assert(success);
        assert(pio[0] == pio_get_instance(NUM_PIOS - 1)); 
    }
    

    // Send N_pulses to each state machine
    for (int i = 0; i < 4; i++) {
        pio_sm_put_blocking(pio[i], sm[i], N_PASx2);
    }

    printf("State machines configured\n");

    // enable ALL state machines with the divisors all in sync
    pio_enable_sm_multi_mask_in_sync(pio[0], 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0);


    sleep_ms(1000); // wait sart sm

    while (sm_completed != 0x0F) {  // 0x0F = 0b1111
       
        sleep_ms(100);    
    }

    printf("motors finished\n");

    // stop all state machines
    pio_set_sm_multi_mask_enabled(pio[0], 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0, false);

    // free resources and unload the program
    assert(pio[0] == pio[1] && pio[1] == pio[2] && pio[2] == pio[3]);
    
    for (int i = 0; i < 4; i++) {
        pio_set_irq0_source_enabled(pio[i], pis_sm0_rx_fifo_not_empty + sm[i], false); // deactivate IRQ from SMi
        pio_remove_program_and_unclaim_sm(&squarewave_program, pio[i], sm[i], offset[i]);
    }
    
    return 0;

}