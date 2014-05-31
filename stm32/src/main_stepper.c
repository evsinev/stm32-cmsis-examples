#include "../stm32f10x_conf.h"

#include "rcc.h"
#include "uart_debug.h"
#include "led_debug.h"
#include "delay.h"
#include "step.h"


int stepper_test() {
    rcc_config();
    
    delay_config();
    led_debug_config();
    step_config();
    
    led_blue_off();
    led_green_off();

    int i=0;
    while(1) {
       led_green_on();
       led_blue_off();

       step_forward();
       for(i=0; i<16*100; i++) {
           step_make();
       }
       delay_ms(1000);

       step_forward();
       for(i=0; i<16*10000; i++) {
           step_make();
       }
       delay_ms(1000);
       
       led_green_off();
       led_blue_on();
       step_back();
       for(i=0; i<16*10000; i++) {
           step_make();
       }

       delay_ms(1000);
    }
}

int main() {
  return stepper_test();
}

