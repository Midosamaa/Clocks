#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {

    //on allume la led pour montrerque ca tourne
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, true);

    const uint pwm_pin = 0;

    gpio_set_function(pwm_pin, GPIO_FUNC_PWM); // configurer GP0 en PWM
    uint slice = pwm_gpio_to_slice_num(pwm_pin);
    uint channel = pwm_gpio_to_channel(pwm_pin);

    pwm_set_phase_correct(slice, false); // mode normal (non phase-correct)
    
    pwm_set_clkdiv(slice, 100.0f); // diviseur de fréquence
    pwm_set_wrap(slice, 6249);     // wrap pour atteindre 200 Hz
    pwm_set_chan_level(slice, channel, 625); // 50% duty cycle (50% de 6250)

    pwm_set_enabled(slice, true); // activer le PWM

    while (true) {
        tight_loop_contents(); // boucle vide
    }
}