#ifndef __DELAY_H__
#define __DELAY_H__

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"

// ��ʱ�ṹ��
typedef struct {
    uint32_t start_time;  // ��ʼʱ��
    uint32_t delay_ms;    // ��ʱ������
    bool  is_running;     // �Ƿ�������ʱ
} Delay_t;

// ��������
void Delay_Init(Delay_t *delay);
bool Delay_Check(Delay_t *delay);
void Delay_Start(Delay_t *delay, uint32_t delay_ms);
bool Delay_IsRunning(Delay_t *delay);
void Delay_Stop(Delay_t *delay);

#endif /* __DELAY_H__ */

