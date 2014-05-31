/* 
 * File:   led_debug.h
 * Author: es
 *
 * Created on July 7, 2012, 2:21 PM
 */

#ifndef LED_DEBUG_H
#define	LED_DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../stm32f10x_conf.h"
    
#define LED_BLUE_PIN  GPIO_Pin_8
#define LED_GREEN_PIN GPIO_Pin_9
#define LED_GPIO      GPIOC

void led_debug_config();
void led_blue_on();
void led_blue_off();

void led_green_on();
void led_green_off();

#ifdef	__cplusplus
}
#endif

#endif	/* LED_DEBUG_H */

