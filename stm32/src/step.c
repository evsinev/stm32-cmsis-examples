#include "step.h"
#include "../stm32f10x_conf.h"
#include "delay.h"

#define STEP_PIN       GPIO_Pin_1
#define DIR_PIN       GPIO_Pin_2

#define STEP_GPIO      GPIOA

void step_config() {
    GPIO_InitTypeDef gpio;

    /* Заполняем структуру gpio данными для инициализации:
     * - Режим: вывод, Push-Pull
     * - Пины: 8 и 9
     * - Частота обновления: 2 МГц
     */
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = STEP_PIN | DIR_PIN ;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;

    /* Инициализируем GPIO на порту C */
    GPIO_Init(STEP_GPIO, &gpio);

    GPIO_ResetBits(STEP_GPIO, STEP_PIN | DIR_PIN);

}

void step_make() {
    int DELAY=100;
    volatile int i=0;
    GPIO_SetBits(STEP_GPIO, STEP_PIN);
    for(i=0;i<DELAY; i++) {    }
    GPIO_ResetBits(STEP_GPIO, STEP_PIN);
    for(i=0;i<DELAY; i++) {    }
}

void step_forward() {
    GPIO_ResetBits(STEP_GPIO, DIR_PIN);
}


void step_back() {
    GPIO_SetBits(STEP_GPIO, DIR_PIN);
}