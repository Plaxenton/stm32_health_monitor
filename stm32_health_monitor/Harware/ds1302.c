#include "ds1302.h"

static void delay_us(uint32_t us)
{
    for(uint32_t i = 0; i < us * 8; i++) __NOP();
}

static void ds1302_write_byte(uint8_t dat)
{
    DS1302_IO_OUT();                 // ← 确保为输出
    for(uint8_t i = 0; i < 8; i++)
    {
        DS1302_SCLK_L();
        if(dat & 0x01) DS1302_IO_H();
        else           DS1302_IO_L();
        delay_us(1);
        DS1302_SCLK_H();
        dat >>= 1;
    }
}

static uint8_t ds1302_read_byte(void)
{
    uint8_t dat = 0;
    DS1302_IO_IN();                  // ← 确保为输入
    for(uint8_t i = 0; i < 8; i++)
    {
        dat >>= 1;
        DS1302_SCLK_L();
        delay_us(1);
        if(DS1302_IO_READ()) dat |= 0x80;
        DS1302_SCLK_H();
    }
    return dat;
}

static void ds1302_write_reg(uint8_t addr,uint8_t dat)
{
    DS1302_CE_H();
    ds1302_write_byte(addr);
    ds1302_write_byte(dat);
    DS1302_CE_L();
}

static uint8_t ds1302_read_reg(uint8_t addr)
{
    uint8_t ret;
    DS1302_CE_H();
    ds1302_write_byte(addr|0x01);
    ret = ds1302_read_byte();
    DS1302_CE_L();
    return ret;
}

void DS1302_Init(void)
{
    /* 引脚初始化已在 CubeMX 完成（PB0=SCLK, PB1=IO, PB2=CE）*/
    DS1302_CE_L();
    DS1302_SCLK_L();
    /* 关闭写保护 */
    ds1302_write_reg(0x8E,0x00);
}

void DS1302_SetTime(uint8_t yr, uint8_t mon, uint8_t date,
                    uint8_t hr, uint8_t min, uint8_t sec)
{
    /* 将十进制转为 BCD 后写入寄存器 */
    ds1302_write_reg(0x80, ((sec  / 10) << 4) | (sec  % 10));
    ds1302_write_reg(0x82, ((min  / 10) << 4) | (min  % 10));
    ds1302_write_reg(0x84, ((hr   / 10) << 4) | (hr   % 10));
    ds1302_write_reg(0x86, ((date / 10) << 4) | (date % 10));
    ds1302_write_reg(0x88, ((mon  / 10) << 4) | (mon  % 10));
    ds1302_write_reg(0x8C, ((yr   / 10) << 4) | (yr   % 10));
}

void DS1302_GetTime(uint8_t *yr, uint8_t *mon, uint8_t *date,
                    uint8_t *hr, uint8_t *min, uint8_t *sec)
{
    /* 从寄存器读取 BCD 数据并转为十进制 */
    uint8_t raw_sec  = ds1302_read_reg(0x81);
    uint8_t raw_min  = ds1302_read_reg(0x83);
    uint8_t raw_hr   = ds1302_read_reg(0x85);
    uint8_t raw_date = ds1302_read_reg(0x87);
    uint8_t raw_mon  = ds1302_read_reg(0x89);
    uint8_t raw_yr   = ds1302_read_reg(0x8D);

    *sec  = ((raw_sec  >> 4) & 0x07) * 10 + (raw_sec  & 0x0F);
    *min  = ((raw_min  >> 4) & 0x07) * 10 + (raw_min  & 0x0F);
    *hr   = ((raw_hr   >> 4) & 0x03) * 10 + (raw_hr   & 0x0F);
    *date = ((raw_date >> 4) & 0x03) * 10 + (raw_date & 0x0F);
    *mon  = ((raw_mon  >> 4) & 0x01) * 10 + (raw_mon  & 0x0F);
    *yr   = ((raw_yr   >> 4) & 0x0F) * 10 + (raw_yr   & 0x0F);
}

