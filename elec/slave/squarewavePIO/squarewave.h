#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#define GPIO_STEP0 6
#define GPIO_STEP1 8
#define GPIO_STEP2 10
#define GPIO_STEP3 12
#define GPIO_STEP4 14 
#define GPIO_STEP5 17
#define GPIO_STEP6 19 
#define GPIO_STEP7 21

#define GPIO_DIR0 7  
#define GPIO_DIR1 9 
#define GPIO_DIR2 11
#define GPIO_DIR3 13
#define GPIO_DIR4 15
#define GPIO_DIR5 16
#define GPIO_DIR6 18
#define GPIO_DIR7 20

// extern variable
extern volatile uint16_t sm_completed; //existing variable in squrewave.c

//functions
void pio_irq_handler0();
void pio_irq_handler1();
void pio_irq_handler2();
void pio_irq_handler3();

void setup_sm_programm(PIO *pio, uint *sm, uint *offset, uint16_t **divf);
void send_pulses(PIO *pio, uint *sm, uint **nb_pas);
void start_all_sm(PIO *pio, uint *sm);
void stop_all_sm(PIO *pio, uint *sm);
void setup_pin_direction();
void send_direction(bool **dir) ;
void unload_program(PIO *pio, uint *sm, uint *offset);
uint16_t calculate_nbPas(const uint16_t *angleTarget, const uint16_t *currentAngle);
uint16_t calculate_divf(const uint16_t nb_pas, const float delta_t);

#endif // SQUAREWAVE_H