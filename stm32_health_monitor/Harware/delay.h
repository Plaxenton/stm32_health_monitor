#ifndef __DELAY_H__
#define __DELAY_H__

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"

// 延时结构体
typedef struct {
    uint32_t start_time;  // 开始时间
    uint32_t delay_ms;    // 延时毫秒数
    bool  is_running;     // 是否正在延时
} Delay_t;

// 函数声明
void Delay_Init(Delay_t *delay);
bool Delay_Check(Delay_t *delay);
void Delay_Start(Delay_t *delay, uint32_t delay_ms);
bool Delay_IsRunning(Delay_t *delay);
void Delay_Stop(Delay_t *delay);

#endif /* __DELAY_H__ */

