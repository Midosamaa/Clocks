#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// extern variable
extern volatile uint16_t sm_completed; 

//functions
void pio_irq_handler0();
void pio_irq_handler1();
void pio_irq_handler2();
void pio_irq_handler3();

void setup_sm_programm(PIO *pio, uint *sm, uint *offset, uint16_t (*divf)[2]);
void send_pulses(PIO *pio, uint *sm, uint16_t (*nb_pas)[2]);
void start_all_sm(PIO *pio, uint *sm);
void stop_all_sm(PIO *pio, uint *sm);
void setup_pin_direction();
void send_direction(bool (*dir)[2]) ;
void unload_program(PIO *pio, uint *sm, uint *offset);
uint16_t calculate_nbPas(const uint16_t angleTarget, const uint16_t currentAngle);
uint16_t calculate_divf(const uint16_t nb_pas, const float delta_t);

#endif // SQUAREWAVE_H