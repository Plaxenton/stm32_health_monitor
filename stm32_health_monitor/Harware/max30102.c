#include "max30102.h"

static void max_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    HAL_I2C_Master_Transmit(&hi2c2, MAX30102_ADDR, buf, 2, HAL_MAX_DELAY);
}

static uint8_t max_read_reg(uint8_t reg)
{
    uint8_t val = 0;
    HAL_I2C_Mem_Read(&hi2c2, MAX30102_ADDR, reg, 1, &val, 1, HAL_MAX_DELAY);
    return val;
}

//static void max_read_fifo(uint8_t *buf, uint8_t len)
//{
//    HAL_I2C_Mem_Read(&hi2c2, MAX30102_ADDR, REG_INTR_STATUS_1,
//                     1, buf, len, HAL_MAX_DELAY);
//}

void MAX30102_Init(void)
{
    max_write_reg(REG_MODE_CONFIG,   0x40);      /* 复位 */
    HAL_Delay(10);

    // 验证器件ID
    if(max_read_reg(REG_PART_ID) != 0x15) {
        Error_Handler(); // 器件ID验证失败
    }

    // 配置FIFO（平均采样4次，启用rollover）
    max_write_reg(REG_FIFO_CONFIG, 0x4F); 
    
    max_write_reg(REG_MODE_CONFIG,   0x03);      /* SpO2 模式 */
    max_write_reg(REG_SPO2_CONFIG, 0x17);  // 50Hz, 411us
    max_write_reg(REG_LED1_PA, 0x15);      // 5.2mA
    max_write_reg(REG_LED2_PA, 0x15);      // 5.2mA
    max_write_reg(REG_FIFO_CONFIG, 0x4F);  // 平均4次
    max_write_reg(REG_INTR_ENABLE_1, 0xC0);      /* FIFO 中断使能 */
}

bool MAX30102_DataReady(void)
{
    return (max_read_reg(REG_INTR_STATUS_1) & 0x40);
}

void MAX30102_ReadFIFO(uint32_t *red, uint32_t *ir)
{
    uint8_t buf[6];
    
    // 先读取状态清除中断标志
    max_read_reg(REG_INTR_STATUS_1);
    
    // 读取FIFO数据
    HAL_I2C_Mem_Read(&hi2c2, MAX30102_ADDR, REG_FIFO_DATA, 
                    1, buf, 6, HAL_MAX_DELAY);
    
    // 重组数据（注意MAX30102是18位数据）
    *red = ((buf[0] << 16) | (buf[1] << 8) | buf[2]) & 0x3FFFF;
    *ir  = ((buf[3] << 16) | (buf[4] << 8) | buf[5]) & 0x3FFFF;
}

