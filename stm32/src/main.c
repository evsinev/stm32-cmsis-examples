#include "../stm32f10x_conf.h"

#include "rcc.h"
#include "uart_debug.h"
#include "led_debug.h"
// #include "delay.h"
// #include "step.h"
#include "../stm32f10x_conf.h"

// volatile int state_tick = 0;

#define STATE_IDLE                   1
#define STATE_WAIT_FOR_FIRST_HEADER  2
#define STATE_WAIT_FOR_SECOND_HEADER 3
#define STATE_PAYLOAD                4


volatile u32 state = 0;
volatile int the_pwm   = 10;

volatile u32 the_state = STATE_IDLE;
volatile u32 the_time         = 0;        
volatile u32 the_last_time    = 0;        
volatile u32 the_value        = 0;
volatile u32 the_bit_position = 0;
u32 buf[300];


void pwm_config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitTypeDef gpio;
  gpio.GPIO_Pin   = (GPIO_Pin_1);
  gpio.GPIO_Mode  = GPIO_Mode_AF_PP;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &gpio);
  
  //Разрешаем таймеру использовать ногу PA1 для ШИМа
  TIM2->CCER |= (TIM_CCER_CC2E);
  TIM2->CCMR1|= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
  TIM3->CCMR2|= TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
  //Настраиваем предделитель чтоб частота ШИМа была в районе 50 Гц
  // 236
  // http://avr-start.ru/?p=610
  TIM2->PSC = 236;

  TIM2->ARR  = 100;
  TIM2->CCR2 =  11;

}

void pwm_start() {
    //Запускаем таймер
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Функция устанавливает позицию вала (в градусах)
void pwm_set(uint8_t pos) {
  //uint32_t tmp=(7500 - 3500) /180 ;
  // TIM2->CCR3 = 100;
    if(pos==10) {
        pos = 11;
    }
    if(pos==100) {
        pos = 101;
    }
    TIM2->CCR2 =  pos;
    
     debugf("pwm = %d\n", pos);

}

void button_config() {
    // Enable the BUTTON Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // Configure Button pin as input
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    gpio.GPIO_Pin   = GPIO_Pin_1;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpio);
    
    // Connect Button EXTI Line to Button GPIO Pin
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
    
    // Configure Button EXTI line
    EXTI_InitTypeDef exti;
    exti.EXTI_Line    = EXTI_Line0;
    exti.EXTI_Mode    = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
    
    // Enable and set Button EXTI Interrupt to the lowest priority
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel                   = EXTI0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0x0F;
    nvic.NVIC_IRQChannelSubPriority        = 0x0F;
    nvic.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&nvic);
}


void toggle_leds() {
        if(state == 0 ) {
           led_green_on();
           led_blue_off();
           state = 1;
        } else {
           led_green_off();
           led_blue_on();
           state = 0;
        }
        
}

void on_value() {

    switch (the_value) {
        case 0xEE11FB04: the_pwm -=   5; break;
        case 0xED12FB04: the_pwm +=   5; break;
        case 0xEF10FB04: the_pwm  =   0; break;
        case 0xE619FB04: the_pwm  = 100; break;
        case 0xEC13FB04: the_pwm  =  10; break;
        
    }
    
    if(the_pwm>100) {
        the_pwm = 100;
    }
    
    if(the_pwm<0) {
        the_pwm = 0 ;
    }
    
    pwm_set(the_pwm);
    
        debugf("on_value: %X\n", the_value);
        for(int i=0; i<300; i++) {
            if(buf[i]!=0) {
                debugf(", %d",  buf[i]);
                buf[i] = 0 ;
            }
        }
        debugf("\n");

    
}

void on_tsop() {

    
    switch (the_state) {
        case STATE_IDLE:
            the_state = STATE_WAIT_FOR_FIRST_HEADER;
            break;

        case STATE_WAIT_FOR_FIRST_HEADER:
            
            if(the_time - the_last_time  > 300) {
                the_state = STATE_WAIT_FOR_SECOND_HEADER;                
            }
            break;
            
        case STATE_WAIT_FOR_SECOND_HEADER:
            if( the_time - the_last_time> 70) {
                the_state = STATE_PAYLOAD;
                the_bit_position = 0;
                the_value = 0;
            }
            break;
            
        case STATE_PAYLOAD:
            if(the_bit_position <= 31) {
                buf[the_bit_position] = the_time - the_last_time;
                
                u32 bit = the_time - the_last_time > 18 ? 1 : 0;
                the_value |= bit << the_bit_position;
                
                if(the_bit_position == 31) {
                    on_value();
                    the_state = STATE_IDLE;
                } else {
                    the_bit_position++;
                }
            }
            break;            
    }
    

    the_last_time = the_time;
    
}

void SysTick_Handler(void) {

    the_time++;
    
    //debugf("last = %d, time=%d", the_last_time, the_time);
    
    if(  the_state == STATE_PAYLOAD && ((the_time - the_last_time) > 5000 )) {
        

        debugf("time: %d, bit_pos:%d\n", the_time - the_last_time, the_bit_position);
        
        for(int i=0; i<300; i++) {
            if(buf[i]!=0) {
                debugf(", %d",  buf[i]);
                buf[i] = 0 ;
            }
        }
        debugf("\n");

        the_state = STATE_IDLE;
    }
}


void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) != RESET) {
        toggle_leds();
        on_tsop();
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}



int stepper_test() {
    rcc_config();
    
    delay_config();
    led_debug_config();
    
    button_config();
    pwm_config();
    SysTick_Config( SystemCoreClock / 10000);

    
    pwm_start();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    uart_debug_config();
    //pwm_set(10);
        
    // 10        - 100 ms
    // 100       -  10 ms
    // 1000      -   1 ms
    // 10,000    - 100 us
    // 100,000   -  10 us
    // 1,000,000 -   3 us
     
    led_blue_off();
    led_green_off();

    //TIM2->CCR2 =  10;
    
    RCC_ClocksTypeDef Sys_RCC_Clocks;
    RCC_GetClocksFreq(&Sys_RCC_Clocks);


    debugf("SYSCLK_Frequency : %d Hz\n", Sys_RCC_Clocks.SYSCLK_Frequency);
    debugf("HCLK_Frequency   : %d Hz\n", Sys_RCC_Clocks.HCLK_Frequency);
    debugf("PCLK1_Frequency  : %d Hz\n", Sys_RCC_Clocks.PCLK1_Frequency);
    debugf("PCLK2_Frequency  : %d Hz\n", Sys_RCC_Clocks.PCLK2_Frequency);
    debugf("ADCCLK_Frequency : %d Hz\n", Sys_RCC_Clocks.ADCCLK_Frequency);

    
    int i=0;
    while(1) {
       //delay_ms(1000);
       for (int i=0; i<1000000; i++) {}
       
       if(i>100) i=0;
       i++;
       
       //TIM2->CCR2 =  i;
       //TIM2->CR1 |= TIM_CR1_CEN;
       // led_green_on();
       // led_blue_off();

       // delay_ms(1000);

       // led_green_off();
       // led_blue_on();

       // delay_ms(1000);
    }
}

int main() {
  return stepper_test();
}


