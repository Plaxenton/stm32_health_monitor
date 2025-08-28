/**
 ******************************************************************************
 * @file    sg90_app.c
 * @brief   SG90舵机应用:PE4引脚控制实现
 * @author
 * @date
 * @version V1.0
 ******************************************************************************
 */
#include "sg90_app.h"

/* 全局变量定义 */
Delay_t Delay_sg90;            // 延时结构体
uint8_t sg90_state = 0;        // 舵机状态
uint8_t sg90_angle = 0;        // 舵机当前角度
uint32_t sg90_last_change = 0; // 上次角度变化时间戳



/* 处理函数:20 ms周期调用 */
void SG90_Proc(void)
{
    static uint8_t init_flag = 1;
    static uint32_t tick = 0;

    if (uwTick - tick < 20)
        return;
    tick = uwTick;

    /* 初始化处理 */
    if (init_flag)
    {
        SG90_SetAngle(0); // 初始角度设为0°
        sg90_angle = 0;
        init_flag = 0;
    }

    /* 状态机处理 */
    switch (sg90_state)
    {
    case SG90_STATE_90: /* 状态:转到90° */
        sg90_angle = 90;
        SG90_SetAngle(sg90_angle);
        sg90_state = SG90_STATE_STOP; // 完成后回到停止状态
        break;

    case SG90_STATE_0: /* 状态:转到0° */
        sg90_angle = 0;
        SG90_SetAngle(sg90_angle);
        sg90_state = SG90_STATE_STOP; // 完成后回到停止状态
        break;

    case SG90_STATE_UP: /* 状态:缓慢上升 */
        if (uwTick - sg90_last_change >= ANGLE_STEP_PERIOD)
        {
            sg90_last_change = uwTick;
            if (sg90_angle < 120) /* 未达到120° */
            {
                sg90_angle += ANGLE_STEP;
                SG90_SetAngle(sg90_angle);
            }
            else
            {
                sg90_state = SG90_STATE_STOP;
            }
        }
        break;

    default:
        /* 无效状态，不做处理 */
        break;
    }
}

