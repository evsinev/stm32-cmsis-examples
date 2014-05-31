/* 
 * File:   uart_debug.h
 * Author: es
 *
 * Created on July 7, 2012, 12:14 PM
 */

#ifndef UART_DEBUG_H
#define	UART_DEBUG_H


#include "../stm32f10x_conf.h"

#include "xprintf.h"

#ifdef	__cplusplus
extern "C" {
#endif

// usart 1    
#define UART_DEBUG USART1
#define UART_DEBUG_GPIO GPIOA
#define UART_DEBUG_TX_PIN GPIO_Pin_9
#define UART_DEBUG_RX_PIN GPIO_Pin_10

// usart 2
//#define UART_DEBUG USART2
//#define UART_DEBUG_GPIO GPIOA
//#define UART_DEBUG_TX_PIN GPIO_Pin_2
//#define UART_DEBUG_RX_PIN GPIO_Pin_3
    
    
#define debugf xprintf    
void uart_debug_config();
void debug(char *aStr) ;


#ifdef	__cplusplus
}
#endif

#endif	/* UART_DEBUG_H */

