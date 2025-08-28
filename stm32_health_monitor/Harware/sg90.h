#ifndef __SG90_H
#define __SG90_H

#include "bsp_system.h"

/* 舵机角度范围定义 */
#define SG90_MIN_ANGLE     0
#define SG90_MAX_ANGLE     180
#define SG90_MIN_PULSE     500   // 0.5ms
#define SG90_MAX_PULSE     2500  // 2.5ms

/* PWM定时器配置 */
#define SG90_TIM           htim3
#define SG90_TIM_CHANNEL   TIM_CHANNEL_1

/* API */
void SG90_Init(void);
void SG90_SetAngle(uint8_t angle);

#endif

