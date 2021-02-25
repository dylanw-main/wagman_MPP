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
#include "hardware/adc.h"


const uint LED_PIN = 25;
const uint SIG_SENSOR = 27; // label 32 pin ADC1, gp27
const uint MESSAGE_PIN = 1;
const uint BUTTON_GPIO = 2;


const int BLINK_INTERVAL = 1000;
const uint DOT_PERIOD_MS = 100;

const char *morse_letters[] = {
        ".-",    // A
        "-...",  // B
        "-.-.",  // C
        "-..",   // D
        ".",     // E
        "..-.",  // F
        "--.",   // G
        "....",  // H
        "..",    // I
        ".---",  // J
        "-.-",   // K
        ".-..",  // L
        "--",    // M
        "-.",    // N
        "---",   // O
        ".--.",  // P
        "--.-",  // Q
        ".-.",   // R
        "...",   // S
        "-",     // T
        "..-",   // U
        "...-",  // V
        ".--",   // W
        "-..-",  // X
        "-.--",  // Y
        "--.."   // Z
};

int state = 1;
int count = 0;

const int BLINK_LENGTH = 100;
int LED_state = 0;
uint32_t previousMS = 0;
uint32_t currentMS = 0;
int numPress = 0;


int blinkLED() {
    // pulse for 1 blink
    if ((LED_state == 1) && (currentMS - previousMS >= BLINK_LENGTH)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 0);
        //printf("off\n");
        LED_state = 0;
    } else if ((LED_state == 0) && (currentMS - previousMS >= BLINK_INTERVAL)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 1);
        LED_state = 1;
        //printf("on\n");
    }
    //return LED_state;
}

int blinkLED_2() {
    // pulse for 2 blink
    if ((LED_state == 0) && (currentMS - previousMS >= BLINK_INTERVAL)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 1);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 0);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 1);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 0);

        LED_state = 0;
        //printf("on\n");
    }
}

int blinkLED_3() {
    // pulse for 2 blink
    if ((LED_state == 0) && (currentMS - previousMS >= BLINK_INTERVAL)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 1);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 0);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 1);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 0);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 1);
        sleep_ms(DOT_PERIOD_MS);
        gpio_put(LED_PIN, 0);
        LED_state = 0;
        //printf("on\n");
    }   
}

int blinkLED_4() {
    // pulse for 1 blink
    if ((LED_state == 1) && (currentMS - previousMS >= BLINK_LENGTH)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 0);
        LED_state = 0;
    } else if ((LED_state == 0) && (currentMS - previousMS >= BLINK_LENGTH)) {
        previousMS = currentMS;
        gpio_put(LED_PIN, 1);
        LED_state = 1;
    }
    //return LED_state;
}

void put_morse_letter(const char *pattern) {
    for (; *pattern; ++pattern) {
        gpio_put(MESSAGE_PIN, 1);
        if (*pattern == '.')
            sleep_ms(DOT_PERIOD_MS);
        else
            sleep_ms(DOT_PERIOD_MS * 3);
        gpio_put(MESSAGE_PIN, 0);
        sleep_ms(DOT_PERIOD_MS * 1);
    }
    sleep_ms(DOT_PERIOD_MS * 2);
}

void put_morse_str(const char *str) {
    for (; *str; ++str) {
        if (*str >= 'A' && *str < 'Z') {
            put_morse_letter(morse_letters[*str - 'A']);
        } else if (*str >= 'a' && *str < 'z') {
            put_morse_letter(morse_letters[*str - 'a']);
        } else if (*str == ' ') {
            sleep_ms(DOT_PERIOD_MS * 4);
        }
    }
}


int main() {
    // init 
    stdio_init_all(); 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // external led
    //gpio_init(LED_GPIO);
    //gpio_set_dir(LED_GPIO, GPIO_OUT);

    // Signal in sensor
    adc_gpio_init(SIG_SENSOR);
    adc_select_input(1);
    const float conversion_factor = 3.3f / (1 << 12);

    // button init
    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO);

    // main loop
    while(1){
        currentMS = to_ms_since_boot(get_absolute_time());
        // updates the state of the LED
        
        switch(state) {
            case 1:
                blinkLED();
                // send out clue - Morse code on pin 1
                put_morse_str("Press pin two");
                
                // check for button press on Button GPIO (pin 2)
                if (!gpio_get(BUTTON_GPIO)) {
                    state = 2;
                }
                break;
            case 2:
                blinkLED_2();
                printf("Light up or power ADC pin ADC1!");
                uint16_t result = adc_read();
                if (result * conversion_factor >= 1) {
                    state = 3; }
                break;
            case 3:
                blinkLED_3();
                printf("Send the board a message that youre DONE. Hint: The Button");
                // check for less than 9 button presses, the morse siganl of 'DONE'
                if (!gpio_get(BUTTON_GPIO)) {
                    count++;
                }
                if (count >= 7) {
                    state = 4;
                }
                break;
            case 4:
                // solved state
                blinkLED_4();
                printf("PUZZLE SOLVED! Secret key: 2e3063701c22d979e0cc19ed88ae89426168c88c3c30f0b0ed85cb131e590b39");
                break;
        }

    }
}

