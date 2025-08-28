#include "mlx90614_app.h"

/* 全局变量：环境温度和物体温度 */
float ambient_temp = 0;
float object_temp = 0;

/* 每500ms读取一次温度数据 */
void MLX90614_Proc(void)
{
    static uint32_t tick;
    if (uwTick - tick < 500) return;
    tick = uwTick;

    ambient_temp = MLX90614_GetTemp(MLX90614_TA);    // 读取环境温度
    object_temp = MLX90614_GetTemp(MLX90614_TOBJ1);  // 读取物体温度
}

