#ifndef __DS1302_H
#define __DS1302_H

#include "bsp_system.h"

/* ---------- 引脚宏 ---------- */
#define DS1302_SCLK_H()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define DS1302_SCLK_L()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)

#define DS1302_IO_H()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
#define DS1302_IO_L()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)
#define DS1302_IO_IN()    {GPIO_InitTypeDef t={GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}; HAL_GPIO_Init(GPIOB,&t);}
#define DS1302_IO_OUT()   {GPIO_InitTypeDef t={GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}; HAL_GPIO_Init(GPIOB,&t);}
#define DS1302_IO_READ()  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)

#define DS1302_CE_H()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define DS1302_CE_L()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)

/* ---------- API ---------- */
void DS1302_Init(void);
void DS1302_SetTime(uint8_t yr,uint8_t mon,uint8_t date,uint8_t hr,uint8_t min,uint8_t sec);
void DS1302_GetTime(uint8_t *yr,uint8_t *mon,uint8_t *date,uint8_t *hr,uint8_t *min,uint8_t *sec);

#endif

