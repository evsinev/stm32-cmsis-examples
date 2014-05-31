#include "delay.h"
#include "../stm32f10x_conf.h"

#include "led_debug.h"

static volatile u32 systick_10ms_ticks = 0xfffffff0;

/*
 * Функция задержки
 */
void delay_ms(u32 msec) {
    u32 tenms = msec / 10;
    u32 dest_time = systick_10ms_ticks + tenms;

if(dest_time < tenms) {
    systick_10ms_ticks = 0;
    dest_time = tenms;
}

    while(systick_10ms_ticks < dest_time) {
        // __WFI();
    }
}

void delay_config() {
   SysTick_Config( SystemCoreClock / 80);
}


void SysTick_Handler2(void) {
    systick_10ms_ticks++;
}
