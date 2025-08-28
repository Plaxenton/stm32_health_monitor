#ifndef __MLX90614_H
#define __MLX90614_H

#include "bsp_system.h"

/* I²C地址（7位地址左移1位） */
#define MLX90614_ADDR (0x5A << 1)

/* 寄存器地址定义 */
#define MLX90614_TA    0x06    // 环境温度寄存器
#define MLX90614_TOBJ1 0x07    // 物体温度寄存器

/* 初始化函数 */
void MLX90614_Init(void);

/* 获取温度函数，参数为寄存器地址 */
float MLX90614_GetTemp(uint8_t reg);

#endif

