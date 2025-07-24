#include "squarewave.pio.h" // header from pico_generate_pio_header in cmakelists.txt
#include "squarewave.h"

// Définition des pins GPIO pour les signaux STEP
#define GPIO_STEP0 6
#define GPIO_STEP1 8
#define GPIO_STEP2 10
#define GPIO_STEP3 12
#define GPIO_STEP4 14 
#define GPIO_STEP5 17
#define GPIO_STEP6 19 
#define GPIO_STEP7 21

// Définition des pins GPIO pour les signaux DIR
#define GPIO_DIR0 7
#define GPIO_DIR1 9
#define GPIO_DIR2 11
#define GPIO_DIR3 13
#define GPIO_DIR4 15 
#define GPIO_DIR5 16
#define GPIO_DIR6 18 
#define GPIO_DIR7 20

#define FCLK 150000000 // 150 MHz, the frequency of the PICO's clock

volatile uint16_t sm_completed;


/*TODO : send direcions and different clock divisor too*/


//Handlers for irq pio0
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

// Handlers pour PIO1
void pio1_irq_handler0() {
    pio_interrupt_clear(pio1, 0);
    sm_completed |= (1 << 4); 
}

void pio1_irq_handler1() {
    pio_interrupt_clear(pio1, 1);
    sm_completed |= (1 << 5);
}

void pio1_irq_handler2() {
    pio_interrupt_clear(pio1, 2);
    sm_completed |= (1 << 6);
}

void pio1_irq_handler3() {
    pio_interrupt_clear(pio1, 3);
    sm_completed |= (1 << 7);
}


// handlers for each  PIO
irq_handler_t handlers[4] = {pio_irq_handler0, pio_irq_handler1, pio_irq_handler2, pio_irq_handler3};
irq_handler_t pio1_handlers[4] = {pio1_irq_handler0, pio1_irq_handler1, pio1_irq_handler2, pio1_irq_handler3};



/*sm functions*/
void setup_sm_programm(PIO *pio, uint *sm, uint *offset, uint16_t **divf){
    bool success;

    for(int i = 0; i < 8; i++) {
        uint pin = 0;
        success = false;
        
        switch (i){
            case 0: pin = GPIO_STEP0; break;
            case 1: pin = GPIO_STEP1; break;
            case 2: pin = GPIO_STEP2; break;
            case 3: pin = GPIO_STEP3; break;
            case 4: pin = GPIO_STEP4; break;
            case 5: pin = GPIO_STEP5; break;
            case 6: pin = GPIO_STEP6; break;
            case 7: pin = GPIO_STEP7; break;
        }

        // which pio to use (pio0 pour i=0-3, pio1 pour i=4-7)
        PIO pio_to_use = (i < 4) ? pio0 : pio1;
        pio[i] = pio_to_use;
        
        uint sm_index = i % 4; // sms numerotation goes from 0 to 3 on each pio

        // Select right handler depending on pio1 or pio0
        irq_handler_t* handler_array = (pio_to_use == pio0) ? handlers : pio1_handlers;

        // Load the program onto the appropriate pio
        success = setup_pio(&squarewave_irq_program, &pio[i], &sm[i], &offset[i], pin, divf[i][i%2], sm_index, handler_array[sm_index]); //sm_index = irq_num -> 0-3 on each pio
        hard_assert(success);
    }

    // Vérifier que les 4 premiers SM utilisent pio0 et les 4 suivants pio1
    assert(pio[0] == pio[1] && pio[1] == pio[2] && pio[2] == pio[3] && pio[0] == pio0);
    assert(pio[4] == pio[5] && pio[5] == pio[6] && pio[6] == pio[7] && pio[4] == pio1);
}

void setup_pin_direction(){
    // direction GPIO14
    for (int i = 0; i < 7; i++) {
        gpio_init(GPIO_DIR0 + i);
        gpio_set_dir(GPIO_DIR0 + i, GPIO_OUT);
    }
}

void send_direction(bool **dir) {
    // Set the direction for each clock hand
    for (int i = 0; i < 8; i++) {
        gpio_put(GPIO_DIR0 + i, dir[i][i%2]); // Set direction based on the value in dir array
    }
}

void send_pulses(PIO *pio, uint *sm, uint **nb_pas) {
    // Send N_pulses to each state machine
    for (int i = 0; i < 8; i++) {
        pio_sm_put_blocking(pio[i], sm[i], nb_pas[i][i%2]);
    }
}

void start_all_sm(PIO *pio, uint *sm) {
    // Enable all state machines with the divisors all in sync
    pio_enable_sm_multi_mask_in_sync(pio0, 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0);
    pio_enable_sm_multi_mask_in_sync(pio1, 0, (1 << sm[4]) | (1 << sm[5]) | (1 << sm[6]) | (1 << sm[7]), 0);
}

void stop_all_sm(PIO *pio, uint *sm) {
    pio_set_sm_multi_mask_enabled(pio0, 0, (1 << sm[0]) | (1 << sm[1]) | (1 << sm[2]) | (1 << sm[3]), 0, false);
    pio_set_sm_multi_mask_enabled(pio1, 0, (1 << sm[4]) | (1 << sm[5]) | (1 << sm[6]) | (1 << sm[7]), 0, false);
}

void unload_program(PIO *pio, uint *sm, uint *offset) {
    // free resources and unload the program
    for (int i = 0; i < 8; i++) {
        // Utiliser l'index relatif pour désactiver l'IRQ
        pio_set_irq0_source_enabled(pio[i], pis_sm0_rx_fifo_not_empty + sm[i], false); // deactivate IRQ from SMi
        pio_remove_program_and_unclaim_sm(&squarewave_irq_program, pio[i], sm[i], offset[i]);
    }
}

uint16_t calculate_nbPas(const uint16_t *angleTarget, const uint16_t *currentAngle) {
    return 12 * (&angleTarget - &currentAngle); //calculate for micro step cf 1/12° /* See with full step irl*/
}

uint16_t calculate_divf(const uint16_t nb_pas, const float delta_t) {
    // Calculate the frequency divisor to send a pio sm in order to reach the target angle in the specified time
    uint16_t f_pwm = (uint16_t) nb_pas/delta_t;
    return (uint16_t) (FCLK)/(2*10*f_pwm); // 10 is the number of machine cycle per instruction (up/down) /* Do we miss a + or -1 somewhere? */
}