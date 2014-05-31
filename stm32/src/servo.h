#ifndef SERVO_H
#define	SERVO_H

#include "../stm32f10x_conf.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define SERVO_180 7500
#define SERVO_0   3500

void servo_config();

// Функция устанавливает позицию вала (в градусах)
void servo_set_pos(uint8_t pos);

void servo_start();

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

