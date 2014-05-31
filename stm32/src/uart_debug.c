#include "uart_debug.h"


void debug_putchar(unsigned char ch) {
    while (!USART_GetFlagStatus(UART_DEBUG, USART_FLAG_TC)) {
    }
    USART_SendData(UART_DEBUG, (uint16_t) ch);
}

void debug(char *aStr) {
    int len=0;
    for(int i=0; i<200; i++) {
        len++;
        if(aStr[i]==0) {
            break;
        }
    }
    for(int i=0; i<len; i++) {
        debug_putchar(aStr[i]);
    }
    debug_putchar('\n');
    debug_putchar('\r');
}


void uart_debug_rcc() {
    
}

void uart_debug_gpio() {
    GPIO_InitTypeDef gpio;

    /* Configure USARTx_Tx as 'alternate function push-pull' */
    gpio.GPIO_Pin = UART_DEBUG_TX_PIN;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART_DEBUG_GPIO, &gpio);

    /* Configure USARTx_Rx as 'input floating' */
    gpio.GPIO_Pin = UART_DEBUG_RX_PIN;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART_DEBUG_GPIO, &gpio);
 
}


void uart_debug_init() {
    USART_InitTypeDef usart;
    
    /* structure with data for USART configuration */
    USART_DeInit(UART_DEBUG);

    /* USART parameters */
    usart.USART_BaudRate = 115200;
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Parity = USART_Parity_No;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    /* Configuring and enabling USARTx */
    USART_Init(UART_DEBUG, &usart);
    USART_Cmd(UART_DEBUG, ENABLE);
}

void uart_debug_config(void) {
    uart_debug_rcc();
    uart_debug_gpio();
    uart_debug_init();
    
    xdev_out(debug_putchar);
}

