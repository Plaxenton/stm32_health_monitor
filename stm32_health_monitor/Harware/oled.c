#include "oled.h"
/*
| 功能         | 引脚      | CubeMX 配置        |
| ---------- | ------- | ---------------- |
| SPI1\_SCK  | **PA5** | SPI1\_SCK (AF5)  |
| SPI1\_MOSI | **PA7** | SPI1\_MOSI (AF5) |
| OLED\_RES  | **PB6** | GPIO\_Output     |
| OLED\_DC   | **PB7** | GPIO\_Output     |
| OLED\_CS   | **PB5** | GPIO\_Output     |
*/

/* ------------- 底层 SPI 发送 ------------- */
static void OLED_SPI_SendByte(uint8_t byte)
{
    OLED_CS_L();
    HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
    OLED_CS_H();
}

/* ------------- 写命令 / 写数据 ------------- */
void OLED_WriteCommand(uint8_t cmd)
{
    OLED_DC_L();
    OLED_SPI_SendByte(cmd);
}

void OLED_WriteData(uint8_t data)
{
    OLED_DC_H();
    OLED_SPI_SendByte(data);
}

/* ------------- 光标 ------------- */
void OLED_SetCursor(uint8_t y, uint8_t x)
{
    OLED_WriteCommand(0xB0 + y);
    OLED_WriteCommand(0x10 | ((x & 0xF0) >> 4));
    OLED_WriteCommand(0x00 | (x & 0x0F));
}

/* ------------- 清屏 ------------- */
void OLED_Clear(void)
{
    uint8_t y, x;
    for (y = 0; y < 8; y++)
    {
        OLED_SetCursor(y, 0);
        for (x = 0; x < 128; x++)
            OLED_WriteData(0x00);
    }
}

/* ------------- 显示字符 ------------- */
void OLED_ShowChar(uint8_t line, uint8_t col, char chr)
{
    uint8_t i;
    OLED_SetCursor((line - 1) * 2, (col - 1) * 8);
    for (i = 0; i < 8; i++)
        OLED_WriteData(OLED_F8x16[chr - ' '][i]);
    OLED_SetCursor((line - 1) * 2 + 1, (col - 1) * 8);
    for (i = 0; i < 8; i++)
        OLED_WriteData(OLED_F8x16[chr - ' '][i + 8]);
}

/* ------------- 其余 API 与之前完全一致 ------------- */
void OLED_ShowString(uint8_t line, uint8_t col, char *str)
{
    while (*str)
        OLED_ShowChar(line, col++, *(str++));
}

uint32_t OLED_Pow(uint32_t x, uint32_t y)
{
    uint32_t res = 1;
    while (y--) res *= x;
    return res;
}

void OLED_ShowNum(uint8_t line, uint8_t col, uint32_t num, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
        OLED_ShowChar(line, col + i, num / OLED_Pow(10, len - i - 1) % 10 + '0');
}

void OLED_ShowSignedNum(uint8_t line, uint8_t col, int32_t num, uint8_t len)
{
    uint8_t i, l = len;
    if (num < 0) { OLED_ShowChar(line, col++, '-'); num = -num; l--; }
    else         { OLED_ShowChar(line, col++, '+'); l--; }
    for (i = 0; i < l; i++)
        OLED_ShowChar(line, col + i, num / OLED_Pow(10, l - i - 1) % 10 + '0');
}

void OLED_ShowHexNum(uint8_t line, uint8_t col, uint32_t num, uint8_t len)
{
    uint8_t i, n;
    for (i = 0; i < len; i++)
    {
        n = (num >> (4 * (len - 1 - i))) & 0x0F;
        OLED_ShowChar(line, col + i, n < 10 ? n + '0' : n - 10 + 'A');
    }
}

void OLED_ShowBinNum(uint8_t line, uint8_t col, uint32_t num, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
        OLED_ShowChar(line, col + i, (num >> (len - 1 - i)) & 1 ? '1' : '0');
}

/* ------------- OLED 初始化指令序列 ------------- */
void OLED_Init(void)
{
    /* 硬件复位 */
    OLED_RES_L();
    HAL_Delay(100);
    OLED_RES_H();
    HAL_Delay(100);

    OLED_WriteCommand(0xAE);        // Display OFF
    OLED_WriteCommand(0xD5); OLED_WriteCommand(0x80);
    OLED_WriteCommand(0xA8); OLED_WriteCommand(0x3F);
    OLED_WriteCommand(0xD3); OLED_WriteCommand(0x00);
    OLED_WriteCommand(0x40);
    OLED_WriteCommand(0xA1);        // 左右正常
    OLED_WriteCommand(0xC8);        // 上下正常
    OLED_WriteCommand(0xDA); OLED_WriteCommand(0x12);
    OLED_WriteCommand(0x81); OLED_WriteCommand(0xCF);
    OLED_WriteCommand(0xD9); OLED_WriteCommand(0xF1);
    OLED_WriteCommand(0xDB); OLED_WriteCommand(0x30);
    OLED_WriteCommand(0xA4);
    OLED_WriteCommand(0xA6);
    OLED_WriteCommand(0x8D); OLED_WriteCommand(0x14);
    OLED_WriteCommand(0xAF);        // Display ON

    OLED_Clear();
}

