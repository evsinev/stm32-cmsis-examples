#include "servo.h"
#include "../stm32f10x_conf.h"

// Функция устанавливает позицию вала (в градусах)
void servo_set_pos(uint8_t pos) {
  uint32_t tmp=(SERVO_180 - SERVO_0) /180 ;
  TIM2->CCR2 = SERVO_0 + tmp * pos;
}


void servo_config() {
  GPIO_InitTypeDef PORT;
  // Настроим ногу (PA1) к которой подключен сервопривод
  PORT.GPIO_Pin = (GPIO_Pin_1);
  //Будем использовать альтернативный режим а не обычный GPIO
  PORT.GPIO_Mode = GPIO_Mode_AF_PP;
  PORT.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &PORT);
  //Разрешаем таймеру использовать ногу PA1 для ШИМа
  TIM2->CCER |= (TIM_CCER_CC2E);
  TIM2->CCMR1|= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
  //Настраиваем предделитель чтоб частота ШИМа была в районе 50 Гц
  TIM2->PSC = 6;
}

void servo_start() {
    //Запускаем таймер
    TIM2->CR1 |= TIM_CR1_CEN;
}
