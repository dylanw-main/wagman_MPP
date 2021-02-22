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

int blinkLED();

const uint LED_PIN = 25;
const int BLINK_INTERVAL = 1000;

int state = 1;
const int BLINK_LENGTH = 100;
int LED_state = 0;
uint32_t previousMS = 0;
uint32_t currentMS = 0;

int main() {
    // init 
    stdio_init_all(); 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // main loop
    while(1){
        currentMS = to_ms_since_boot(get_absolute_time());
        // updates the state of the LED
        
        switch(state) {
            case 1:
                blinkLED(LED_state);
                int guard1 = 0;
                if (guard1 == 1) {
                    state = 2;
                    }
                break;
            case 2:
                blinkLED(LED_state);
                blinkLED(LED_state);

                int guard2 = 0;
                if (guard2 == 1) {
                    state = 3; }
                break;
                
        }

    }
    return 0;
}

int blinkLED() {
    // pulse for 1 blink
    if ((LED_state == 1) && (currentMS - previousMS >= BLINK_LENGTH)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 0);
        printf("off\n");
        LED_state = 0;
    } else if ((LED_state == 0) && (currentMS - previousMS >= BLINK_INTERVAL)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 1);
        LED_state = 1;
        printf("on\n");
    }
    //return LED_state;
}


