#ifndef __MAX30102_H
#define __MAX30102_H

#include "bsp_system.h"

/* I²C 地址 */
#define MAX30102_ADDR          (0x57 << 1)

/* 寄存器地址 */
#define REG_INTR_STATUS_1      0x00
#define REG_INTR_STATUS_2      0x01
#define REG_INTR_ENABLE_1      0x02
#define REG_INTR_ENABLE_2      0x03
#define REG_FIFO_WR_PTR        0x04
#define REG_OVF_COUNTER        0x05
#define REG_FIFO_RD_PTR        0x06
#define REG_FIFO_DATA          0x07 
#define REG_FIFO_CONFIG        0x08
#define REG_MODE_CONFIG        0x09
#define REG_SPO2_CONFIG        0x0A
#define REG_LED1_PA            0x0C
#define REG_LED2_PA            0x0D
#define REG_PILOT_PA           0x10
#define REG_MULTI_LED_CTRL1    0x11
#define REG_MULTI_LED_CTRL2    0x12
#define REG_TEMP_INTEGER       0x1F
#define REG_TEMP_FRACTION      0x20
#define REG_TEMP_CONFIG        0x21
#define REG_PROX_INT_THRESH    0x30
#define REG_REV_ID             0xFE
#define REG_PART_ID            0xFF

/* 默认配置 */
#define DEFAULT_LED_CURR       0x7F        /* ≈7 mA */
#define DEFAULT_SAMPLE_RATE    0x03        /* 100 Hz */
#define DEFAULT_PULSE_WIDTH    0x03        /* 411 µs */

/* API */
void MAX30102_Init(void);
bool MAX30102_DataReady(void);
void MAX30102_ReadFIFO(uint32_t *red, uint32_t *ir);

#endif

