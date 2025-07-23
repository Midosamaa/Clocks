#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/sync.h"

#define CLKDIV 100.0f
#define PWM_FREQ 200
#define PERIOD_US 5000

void setup_pwm(uint gpio, uint16_t level, uint16_t top) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    uint channel = pwm_gpio_to_channel(gpio);

    pwm_set_phase_correct(slice, false);
    pwm_set_clkdiv(slice, CLKDIV);
    pwm_set_wrap(slice, top);
    pwm_set_chan_level(slice, channel, level);
    pwm_set_enabled(slice, true);
}

int main() {
    stdio_init_all();

    // LED témoin
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, true);

    // GPIO 4 à l'état haut
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    gpio_put(2, true);

    uint16_t top = 7499;              // Pour 200 Hz avec clkdiv=100
    uint16_t level = top / 2;         // 50% duty cycle

    // Setup PWM outputs
    setup_pwm(0, level, top); // GPIO 0
    sleep_us(2500);
    setup_pwm(1, level, top); // GPIO 1
    // sleep_us(1250);
    // setup_pwm(2, level, top); // GPIO 2
    // sleep_us(1250);
    // setup_pwm(3, level, top); // GPIO 3

    // Get slices for control later
    uint slice0 = pwm_gpio_to_slice_num(0);
    uint slice1 = pwm_gpio_to_slice_num(1);
    // uint slice2 = pwm_gpio_to_slice_num(2);
    // uint slice3 = pwm_gpio_to_slice_num(3);

    while (true) {
        // Disable all PWM outputs
        pwm_set_enabled(slice0, false);
        pwm_set_enabled(slice1, false);
        // pwm_set_enabled(slice2, false);
        // pwm_set_enabled(slice3, false);

        sleep_ms(500);  // PWM off duration

        // Enable all PWM outputs
        pwm_set_enabled(slice0, true);
        pwm_set_enabled(slice1, true);
        // pwm_set_enabled(slice2, true);
        // pwm_set_enabled(slice3, true);

        sleep_ms(500);  // PWM on duration
    }
}
