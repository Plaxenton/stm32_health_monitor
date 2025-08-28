/*
 * 文件名: beeper.c
 * 描述  : 蜂鸣器驱动实现
 * 作者  : -
 * 日期  : 2025-08-26
 * 版本  : V1.0
 */
#include "beeper.h"

/* 初始化蜂鸣器（PF12引脚，低电平响） */
void BEEPER_Init(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET); // 默认关闭
}

/* 打开蜂鸣器 */
void BEEPER_On(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET);
}

/* 关闭蜂鸣器 */
void BEEPER_Off(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
}

/* 切换蜂鸣器状态 */
void BEEPER_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_12);
}

