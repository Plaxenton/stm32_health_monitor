#include "mlx90614.h"

/* 读取MLX90614寄存器值（16位） */
static uint16_t mlx_read_reg(uint8_t reg)
{
    uint8_t buf[3] = {0};
    HAL_I2C_Mem_Read(&hi2c2, MLX90614_ADDR, reg, 1, buf, 3, HAL_MAX_DELAY);
    return (buf[1] << 8) | buf[0];
}

/* 初始化MLX90614传感器，检查I2C通信是否正常 */
void MLX90614_Init(void)
{
    if (HAL_I2C_IsDeviceReady(&hi2c2, MLX90614_ADDR, 3, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler(); // I2C通信失败，进入错误处理
    }
}

/* 获取温度值（环境温度或物体温度） */
float MLX90614_GetTemp(uint8_t reg)
{
    uint16_t temp = mlx_read_reg(reg);
    return (float)temp * 0.02f - 273.15f; // 转换为摄氏度
}

