#include "key.h"

/* 获取按键当前物理状态（PE4引脚） */
uint8_t Key_GetState(void)
{
    return (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_SET) ? KEY_PRESSED
                                                                 : KEY_UNPRESSED;
}

