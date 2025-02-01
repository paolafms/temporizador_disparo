#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_BLUE 12
#define LED_RED 13
#define LED_GREEN 11
#define BUTTON 5

typedef enum {
    STATE_OFF,
    STATE_ALL_ON,
    STATE_TWO_ON,
    STATE_ONE_ON
} LedState;

volatile LedState currentState = STATE_OFF;
volatile bool timerActive = false;

// Protótipo da função alarm_callback
int64_t alarm_callback(alarm_id_t id, void *user_data);

void turn_off_callback() {
    switch (currentState) {
        case STATE_ALL_ON:
            gpio_put(LED_BLUE, 0);
            currentState = STATE_TWO_ON;
            add_alarm_in_ms(3000, alarm_callback, NULL, false); // Reinicia o alarme
            break;
        case STATE_TWO_ON:
            gpio_put(LED_RED, 0);
            currentState = STATE_ONE_ON;
            add_alarm_in_ms(3000, alarm_callback, NULL, false); // Reinicia o alarme
            break;
        case STATE_ONE_ON:
            gpio_put(LED_GREEN, 0);
            currentState = STATE_OFF;
            timerActive = false; // Finaliza a temporização
            break;
        default:
            break;
    }
}

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    turn_off_callback();
    return 0; // Não rearma o alarme
}

void debounce_button() {
    static uint32_t last_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (current_time - last_time < 200) { // Debounce de 200ms
        return;
    }

    last_time = current_time;

    if (!gpio_get(BUTTON) && !timerActive) {
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        currentState = STATE_ALL_ON;
        timerActive = true;
        add_alarm_in_ms(3000, alarm_callback, NULL, false); // Inicia o alarme
    }
}

int main() {
    stdio_init_all();

    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON);

    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON, GPIO_IN);

    gpio_pull_up(BUTTON);

    while (1) {
        debounce_button();
        sleep_ms(10); // Delay para evitar leitura excessiva
    }

    return 0;
}