#include "OLED_App.h"

void OLED_Proc(void)
{
    uint16_t red_display = (max_red * 100) / 0x3FFFF;
    uint16_t ir_display = (max_ir * 100) / 0x3FFFF;
    
    /* 固定显示格式：
         2025-07-23
         22:59:57
    */
    OLED_ShowString(1, 1, "20");
    OLED_ShowNum(1, 3, g_year, 2);
    OLED_ShowChar(1, 5, '-');
    OLED_ShowNum(1, 6, g_mon, 2);
    OLED_ShowChar(1, 8, '-');
    OLED_ShowNum(1, 9, g_date, 2);
    

    OLED_ShowNum(2, 1, g_hour, 2);
    OLED_ShowChar(2, 3, ':');
    OLED_ShowNum(2, 4, g_min, 2);
    OLED_ShowChar(2, 6, ':');
    OLED_ShowNum(2, 7, g_sec, 2);
    
    /* 第三行：左侧显示温度传感器，右侧显示心率传感器 */
    // 左侧：环境温度
    OLED_ShowString(3, 1, "Amb:");
    OLED_ShowNum(3, 5, (uint32_t)ambient_temp, 2);
    OLED_ShowChar(3, 7, '.');
    OLED_ShowNum(3, 8, (uint32_t)(ambient_temp * 10) % 10, 1);
    OLED_ShowChar(3, 9, 'C');
    
    // 右侧：红光数据 (留1列空白分隔)
    OLED_ShowString(3, 11, "R:");
    OLED_ShowNum(3, 13, red_display, 3);
    OLED_ShowChar(3, 16, '%');

    /* 第四行：左侧显示物体温度，右侧显示红外数据 */
    // 左侧：物体温度
    OLED_ShowString(4, 1, "Obj:");
    OLED_ShowNum(4, 5, (uint32_t)object_temp, 2);
    OLED_ShowChar(4, 7, '.');
    OLED_ShowNum(4, 8, (uint32_t)(object_temp * 10) % 10, 1);
    OLED_ShowChar(4, 9, 'C');
    
    // 右侧：红外数据 (留1列空白分隔)
    OLED_ShowString(4, 11, "IR:");
    OLED_ShowNum(4, 14, ir_display, 2);  // 调整位置使%对齐
    OLED_ShowChar(4, 16, '%');
}



