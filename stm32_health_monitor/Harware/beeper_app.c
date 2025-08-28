#include "beeper_app.h"

/* 全局变量：蜂鸣器状态 */
bool beeper_state = false;

/* 蜂鸣器状态处理函数（200ms周期调用） */
void Beeper_Proc(void)
{
    beeper_state ? BEEPER_On() : BEEPER_Off();
}

