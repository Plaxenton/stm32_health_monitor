/*
 * 文件名: beeper.h
 * 描述  : 蜂鸣器驱动头文件
 * 作者  : -
 * 日期  : 2025-08-26
 * 版本  : V1.0
 */
#ifndef __BEEPER_H
#define __BEEPER_H

#include "bsp_system.h"

/* 蜂鸣器控制接口 */
void BEEPER_Init(void);     // 初始化蜂鸣器
void BEEPER_On(void);       // 打开蜂鸣器
void BEEPER_Off(void);      // 关闭蜂鸣器
void BEEPER_Toggle(void);   // 切换蜂鸣器状态

#endif

