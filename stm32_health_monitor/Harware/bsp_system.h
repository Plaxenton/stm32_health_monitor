#ifndef __bsp_system__
#define __bsp_system__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>      // 定义 va_list / va_start / va_end 蓝牙模块
#include "main.h"
#include "stm32f4xx_hal.h"

#include "scheduler.h"

#include "oled_font.h"
#include "oled.h"
#include "OLED_App.h"
#include "ds1302.h"
#include "ds1302_app.h"
#include "max30102.h"
#include "max30102_app.h"
#include "mlx90614.h"
#include "mlx90614_app.h"
#include "sg90.h"
#include "sg90_app.h"
#include "beeper.h"
#include "key.h"
#include "key_app.h"
#include "delay.h"
#include "beeper_app.h"

extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim3;

extern void HC08D_RxCallback(uint8_t *buf, uint16_t len);

extern uint8_t g_year, g_mon, g_date, g_hour, g_min, g_sec;
extern uint32_t max_red, max_ir;
extern float ambient_temp, object_temp;
extern uint8_t sg90_angle;
extern uint32_t sg90_last_change;
extern uint8_t sg90_state;
extern uint8_t a;
extern Delay_t Delay_sg90;
extern bool beeper_state;

#endif

