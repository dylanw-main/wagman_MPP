/**
 * 
 * Osciliscope puzzle
 * Dylan Wagman
 * ME-193
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/binary_info.h"

int blinkLED(int state);

const uint LED_PIN = 25;
const int BLINK_LENGTH = 1000;

uint LED_state = 0;
uint32_t previousMS = 0;
uint32_t currentMS = 0;

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while(1){
        currentMS = to_ms_since_boot(get_absolute_time());
        blinkLED(LED_state);
    }
}
int blinkLED(int state) {
    if (currentMS - previousMS >= BLINK_LENGTH) {
        previousMS = currentMS;
        if (state == 0) {
            gpio_put(LED_PIN, 1);
            state = 1;
        } else if (state == 1) {
            gpio_put(LED_PIN, 0);
            state = 0;
        }
    }
    return LED_state = state;
}
