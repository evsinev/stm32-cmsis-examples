#include "rcc.h"
#include "../stm32f10x_conf.h"

void rcc_config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    //Включем порт А
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    
    //Включаем Таймер 2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

}

void rcc_debug() {
    //RCC_ClocksTypeDef rcc;
    //RCC_GetClocksFreq(&rcc);
    //debugf("SYSCLK_Frequency : %d Hz\n", rcc.SYSCLK_Frequency);
    //debugf("HCLK_Frequency   : %d Hz\n", rcc.HCLK_Frequency);
    //debugf("PCLK1_Frequency  : %d Hz\n", rcc.PCLK1_Frequency);
    //debugf("PCLK2_Frequency  : %d Hz\n", rcc.PCLK2_Frequency);
    //debugf("ADCCLK_Frequency : %d Hz\n", rcc.ADCCLK_Frequency);
}

