#include "reed.h"
#include "../stm32f10x_conf.h"

void reed_config() {
    GPIO_InitTypeDef g;
    g.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_0;
    g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &g);
}

void reed_delay_left() {
    volatile uint32_t i;
    while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1) {}
    // && GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==0
    //for (i=1; i < 0x20FFFF && GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==1; i++) {
    //}

}

void reed_delay_right() {
    volatile uint32_t i;
    //while(    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==0) {}
    while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==1) {}
    
//    for (i=1; i < 0x20FFFF  ; i++) {
//    }
}

