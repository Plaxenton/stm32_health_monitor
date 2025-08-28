#ifndef __KEY_H
#define __KEY_H

#include "bsp_system.h"

/* 按键物理电平定义 */
#define KEY_PRESSED     1   // 按下时为高电平（PE4默认上拉）
#define KEY_UNPRESSED   0   // 未按下时为低电平

/* 按键事件枚举 */
typedef enum {
    KEY_NONE   = 0,         // 无事件
    KEY_DOWN   = 1 << 0,    // 按下沿
    KEY_UP     = 1 << 1,    // 抬起沿
    KEY_SINGLE = 1 << 2,    // 单击
    KEY_DOUBLE = 1 << 3,    // 双击
    KEY_LONG   = 1 << 4,    // 长按
    KEY_REPEAT = 1 << 5     // 连按
} key_evt_t;

/* 获取按键当前状态（原始电平） */
uint8_t Key_GetState(void);

/* 获取按键事件（需在主循环中周期调用） */
key_evt_t Key_Tick(void);

#endif

