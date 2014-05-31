#ifndef DELAY_H
#define	DELAY_H

#include "../stm32f10x_conf.h"

#ifdef	__cplusplus
extern "C" {
#endif

void delay_config();

void delay_ms(u32 aMilliseconds) ;

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

