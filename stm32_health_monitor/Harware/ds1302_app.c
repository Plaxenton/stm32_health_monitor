#include "ds1302_app.h"

static Delay_t alarm_delay;
static bool alarm_triggered = false;
uint8_t g_year, g_mon, g_date, g_hour, g_min, g_sec;
uint8_t g_alarm[3] = {00, 00, 01};

/* 首次初始化时间：23-09-01 23:59:54 */
void DS1302_Proc(void)
{
    static uint32_t tick;
    if (uwTick - tick < 1000) return;
    tick = uwTick;

    DS1302_GetTime(&g_year, &g_mon, &g_date, &g_hour, &g_min, &g_sec);

    // 每天定时触发
    if (!alarm_triggered &&
        g_hour == g_alarm[0] &&
        g_min == g_alarm[1] &&
        g_sec == g_alarm[2])
    {
        sg90_state = SG90_STATE_90;  // 转到90°
        Delay_Start(&alarm_delay, 20000);  // 启动20秒延时
        alarm_triggered = true;
    }

    // 非阻塞延时结束，回到0°
    if (alarm_triggered && Delay_Check(&alarm_delay))
    {
        sg90_state = SG90_STATE_0;
        alarm_triggered = false;
    }
}

