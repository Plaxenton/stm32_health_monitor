#include "key_app.h"

/* 时间阈值（20 ms 周期计数）*/
#define DEBOUNCE_CNT 2      // 40 ms
#define LONG_HOLD_CNT 100   // 2 s
#define DOUBLE_GAP_CNT 25   // 500 ms
#define REPEAT_PERIOD_CNT 5 // 100 ms

static struct
{
    uint8_t debounceCnt;
    uint8_t state; // 0:空闲 1:已按下 2:等待双击 3:连发
    uint16_t timer;
    key_evt_t evt;
    uint8_t isAfterDouble;
} k = {0};

/* 20 ms 周期调用 */
void Key_Proc(void)
{
    static uint8_t raw, prev = KEY_UNPRESSED;
    static key_evt_t ret = KEY_NONE;

    /* ---------- 1. 采样与去抖 ---------- */
    raw = Key_GetState();
    if (raw == prev)
    {
        if (k.debounceCnt < DEBOUNCE_CNT)
            ++k.debounceCnt;
    }
    else
    {
        k.debounceCnt = 0;
    }
    prev = raw;

    if (k.debounceCnt < DEBOUNCE_CNT)
        return; // 抖动中，直接退出

    /* ---------- 2. 状态机 ---------- */
    switch (k.state)
    {
    case 0: /* 空闲 */
        if (raw == KEY_PRESSED)
        {
            k.timer = LONG_HOLD_CNT;
            k.state = 1;
            ret = KEY_DOWN;
            k.isAfterDouble = 0;
        }
        break;

    case 1:                       /* 已按下 */
        if (raw == KEY_UNPRESSED) // 松开
        {
            if (k.isAfterDouble) {
                // 双击后的松开，直接回到空闲
                k.state = 0;
                k.isAfterDouble = 0;
            } else {
                // 普通单击后的松开，进入等待双击
                k.timer = DOUBLE_GAP_CNT;
                k.state = 2;
            }
            ret = KEY_UP;
        }
        else if (k.timer == 0) // 持续按住
        {
            ret = KEY_LONG;
            k.state = 3;
            k.timer = REPEAT_PERIOD_CNT;
            k.isAfterDouble = 0;
        }
        break;

    case 2:                     /* 等待双击窗口 */
        if (raw == KEY_PRESSED) // 在窗口内再次按下 → 双击
        {
            ret = KEY_DOUBLE;
            k.state = 1;
            k.timer = LONG_HOLD_CNT;
            k.isAfterDouble = 1; // 标记为双击后状态
        }
        else if (k.timer == 0) // 窗口超时 → 单击
        {
            ret = KEY_SINGLE;
            k.state = 0;
            k.isAfterDouble = 0;
        }
        break;

    case 3:                       /* 连发态 */
        if (raw == KEY_UNPRESSED) // 松开
        {
            k.state = 0;
            ret = KEY_UP;
        }
        else if (k.timer == 0) // 连发周期到
        {
            ret = KEY_REPEAT;
            k.timer = REPEAT_PERIOD_CNT;
        }
        break;
    }

    if (k.timer)
        k.timer--;

    /* ---------- 3. 事件分发 ---------- */
    if (ret == KEY_SINGLE)
    {
        /* 单击 -> 舵机 90° */
        sg90_state = SG90_STATE_90;
        ret = KEY_NONE;
    }
    else if (ret == KEY_DOUBLE)
    {
        /* 双击 -> 舵机 0° */
        sg90_state = SG90_STATE_0;
        ret = KEY_NONE;
    }
    else if (ret == KEY_LONG)
    {
        /* 长按 -> 开始缓升 */
        sg90_state = SG90_STATE_UP;
        ret = KEY_NONE;
    }
    else if (ret == KEY_UP && sg90_state == SG90_STATE_UP)
    {
        /* 长按时松手 -> 停止 */
        sg90_state = SG90_STATE_STOP;
        ret = KEY_NONE;
    }
}

