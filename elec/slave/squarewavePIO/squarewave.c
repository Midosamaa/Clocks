#include "squarewave.pio.h" // header from pico_generate_pio_header in cmakelists.txt
#include "squarewave.h"

#define GPIO_PIN0 10
#define GPIO_PIN1 12
#define GPIO_PIN2 13
#define GPIO_PIN3 11

#define GPIO_DIR_A 14

// A square wave, period of around 1748us by using a clock div of 65535
#define CLOCK_DIVISOR 18750

volatile uint8_t sm_completed;


/*TODO : send direcions and different clock divisor too*/


/*Handlers for irq*/
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

irq_handler_t handlers[4] = {pio_irq_handler0, pio_irq_handler1, pio_irq_handler2, pio_irq_handler3};


/*sm functions*/
void setup_sm_programm(PIO *pio, uint *sm, uint *offset){
    bool success;

    for(int i = 0; i < 4; i++) {
        uint pin = 0;
        success = false;
        
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
    success = setup_pio(&squarewave_irq_program, &pio[i], &sm[i], &offset[i], pin, CLOCK_DIVISOR, i, handlers[i]);
    hard_assert(success);
    assert(pio[0] == pio_get_instance(NUM_PIOS - 1)); 
    }

    assert(pio[0] == pio[1] && pio[1] == pio[2] && pio[2] == pio[3]);
}

void setup_pin_direction14(){
    // direction GPIO14
    gpio_init(GPIO_DIR_A);
    gpio_set_dir(GPIO_DIR_A, GPIO_OUT);
    gpio_put(GPIO_DIR_A, 0);  // CCW 

}

void send_pulses(PIO *pio, uint *sm, uint nb_pas) {
    // Send N_pulses to each state machine
        for (int i = 0; i < 4; i++) {
            pio_sm_put_blocking(pio[i], sm[i], nb_pas);
        }
}

void start_all_sm(PIO *pio, uint *sm) {
    // enable ALL state machines with the divisors all in sync
    pio_enable_sm_multi_mask_in_sync(pio[0], 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0);
}

void stop_all_sm(PIO *pio, uint *sm) {
    // stop all state machines
    pio_set_sm_multi_mask_enabled(pio[0], 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0, false);
}

void unload_program(PIO *pio, uint *sm, uint *offset) {
    // free resources and unload the program
    for (int i = 0; i < 4; i++) {
        pio_set_irq0_source_enabled(pio[i], pis_sm0_rx_fifo_not_empty + sm[i], false); // deactivate IRQ from SMi
        pio_remove_program_and_unclaim_sm(&squarewave_irq_program, pio[i], sm[i], offset[i]);
    }
    
}