#include "max30102_app.h"

uint32_t max_red = 0, max_ir = 0;

void MAX30102_Proc(void)
{
    static uint32_t tick;
    if (uwTick - tick < 10) return;
    tick = uwTick;

    if (MAX30102_DataReady())
    {
        uint32_t red, ir;
        MAX30102_ReadFIFO(&red, &ir);
        
        // 添加数据有效性检查
        if (red > 1000 && ir > 1000)  // 过滤无效数据
        {
            max_red = red;
            max_ir = ir;
        }
    }
}

