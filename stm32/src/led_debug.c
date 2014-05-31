#include "led_debug.h"

void led_debug_config() {
    GPIO_InitTypeDef gpio;

    /* Заполняем структуру gpio данными для инициализации:
     * - Режим: вывод, Push-Pull
     * - Пины: 8 и 9
     * - Частота обновления: 2 МГц
     */
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = LED_BLUE_PIN | LED_GREEN_PIN;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;

    /* Инициализируем GPIO на порту C */
    GPIO_Init(LED_GPIO, &gpio);

    GPIO_ResetBits(LED_GPIO, LED_BLUE_PIN | LED_GREEN_PIN);
    
}

void led_blue_on() {
    GPIO_SetBits(LED_GPIO, LED_BLUE_PIN);
}

void led_blue_off() {
    GPIO_ResetBits(LED_GPIO, LED_BLUE_PIN);
}

void led_green_on() {
   GPIO_SetBits(LED_GPIO, LED_GREEN_PIN);
}

void led_green_off() {
    GPIO_ResetBits(LED_GPIO, LED_GREEN_PIN);
}

