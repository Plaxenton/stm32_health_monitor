#ifndef __OLED_H
#define __OLED_H

#include "bsp_system.h"


extern SPI_HandleTypeDef hspi1;   /* CubeMX 生成 */

/* ------------- 引脚宏 ------------- */
#define OLED_RES_H()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)
#define OLED_RES_L()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)
#define OLED_DC_H()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define OLED_DC_L()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define OLED_CS_H()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET)
#define OLED_CS_L()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)

/* ------------- API ------------- */
void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t y, uint8_t x);
void OLED_ShowChar(uint8_t line, uint8_t col, char chr);
void OLED_ShowString(uint8_t line, uint8_t col, char *str);
void OLED_ShowNum(uint8_t line, uint8_t col, uint32_t num, uint8_t len);
void OLED_ShowSignedNum(uint8_t line, uint8_t col, int32_t num, uint8_t len);
void OLED_ShowHexNum(uint8_t line, uint8_t col, uint32_t num, uint8_t len);
void OLED_ShowBinNum(uint8_t line, uint8_t col, uint32_t num, uint8_t len);

#endif


