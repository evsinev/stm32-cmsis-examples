#include "motor.h"
#include "../stm32f10x_conf.h"

#define MOTOR_INPUT3   GPIO_Pin_5
#define MOTOR_INPUT4   GPIO_Pin_2
#define MOTOR_ENABLE2  GPIO_Pin_4

#define MOTOR_GPIO      GPIOA

void motor_config() {
    GPIO_InitTypeDef gpio;

    /* Заполняем структуру gpio данными для инициализации:
     * - Режим: вывод, Push-Pull
     * - Пины: 8 и 9
     * - Частота обновления: 2 МГц
     */
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = MOTOR_INPUT3 | MOTOR_INPUT4 | MOTOR_ENABLE2;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;

    /* Инициализируем GPIO на порту C */
    GPIO_Init(MOTOR_GPIO, &gpio);

    GPIO_ResetBits(MOTOR_GPIO, MOTOR_INPUT3 | MOTOR_INPUT4 | MOTOR_ENABLE2);

}

void motor_back() {
    GPIO_ResetBits(MOTOR_GPIO, MOTOR_INPUT4);
    GPIO_SetBits(MOTOR_GPIO, MOTOR_INPUT3);
    GPIO_SetBits(MOTOR_GPIO, MOTOR_ENABLE2);
}

void motor_forward() {
    GPIO_ResetBits(MOTOR_GPIO, MOTOR_INPUT3);
    GPIO_SetBits(MOTOR_GPIO, MOTOR_INPUT4);
    GPIO_SetBits(MOTOR_GPIO, MOTOR_ENABLE2);
}

void motor_stop() {
    GPIO_ResetBits(MOTOR_GPIO, MOTOR_INPUT3 | MOTOR_INPUT4 | MOTOR_ENABLE2);
}


