#include "sg90.h"

void SG90_Init(void)
{
    // 启动PWM通道
    HAL_TIM_PWM_Start(&SG90_TIM, SG90_TIM_CHANNEL);
    
    // 初始位置设为90度
    SG90_SetAngle(0);
}

void SG90_SetAngle(uint8_t angle)
{
    // 角度限幅
    if(angle <= SG90_MIN_ANGLE) angle = SG90_MIN_ANGLE;
    if(angle >= SG90_MAX_ANGLE) angle = SG90_MAX_ANGLE;
    
    // 计算对应的脉冲宽度(单位: us)
    uint32_t pulse = SG90_MIN_PULSE + (angle * (SG90_MAX_PULSE - SG90_MIN_PULSE)) / SG90_MAX_ANGLE;
    
    // 设置PWM占空比
    __HAL_TIM_SET_COMPARE(&SG90_TIM, SG90_TIM_CHANNEL, pulse);
}

