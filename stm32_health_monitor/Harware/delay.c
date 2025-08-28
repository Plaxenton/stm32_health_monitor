/**
 * @file    delay.c
 * @brief   毫秒级非阻塞延时实现
 * @author  -
 * @date    2025-08-26
 */
#include "delay.h"

/**
 * @brief  初始化延时结构体
 * @param  delay 延时句柄
 * @retval None
 */
void Delay_Init(Delay_t *delay)
{
    if (delay == NULL) return;

    delay->start_time = 0;
    delay->delay_ms   = 0;
    delay->is_running = false;
}

/**
 * @brief  检查延时是否到达
 * @param  delay 延时句柄
 * @retval true  已到时间
 * @retval false 未到时间
 */
bool Delay_Check(Delay_t *delay)
{
    if (delay == NULL || !delay->is_running)
        return true;

    uint32_t now = HAL_GetTick();

    /* 处理 systick 溢出 */
    if (now < delay->start_time)
    {
        if ((now + (0xFFFFFFFF - delay->start_time + 1)) >= delay->delay_ms)
        {
            delay->is_running = false;
            return true;
        }
    }
    else
    {
        if ((now - delay->start_time) >= delay->delay_ms)
        {
            delay->is_running = false;
            return true;
        }
    }

    return false;
}

/**
 * @brief  启动延时
 * @param  delay 延时句柄
 * @param  ms    延时毫秒数
 * @retval None
 */
void Delay_Start(Delay_t *delay, uint32_t ms)
{
    if (delay == NULL) return;

    delay->start_time = HAL_GetTick();
    delay->delay_ms   = ms;
    delay->is_running = true;
}

/**
 * @brief  查询延时是否正在运行
 * @param  delay 延时句柄
 * @retval true  正在运行
 * @retval false 未运行
 */
bool Delay_IsRunning(Delay_t *delay)
{
    return (delay == NULL) ? false : delay->is_running;
}

/**
 * @brief  强制停止延时
 * @param  delay 延时句柄
 * @retval None
 */
void Delay_Stop(Delay_t *delay)
{
    if (delay == NULL) return;
    delay->is_running = false;
}

