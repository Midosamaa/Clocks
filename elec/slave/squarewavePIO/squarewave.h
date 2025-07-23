#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// extern variable
extern volatile uint8_t sm_completed; //existing variable in squrewave.c

//functions
void pio_irq_handler0();
void pio_irq_handler1();
void pio_irq_handler2();
void pio_irq_handler3();

void setup_pin_direction14();
void setup_sm_programm(PIO *pio, uint *sm, uint *offset);
void send_pulses(PIO *pio, uint *sm, uint nb_pas);
void start_all_sm(PIO *pio, uint *sm);
void stop_all_sm(PIO *pio, uint *sm);
void unload_program(PIO *pio, uint *sm, uint *offset);

#endif // SQUAREWAVE_H