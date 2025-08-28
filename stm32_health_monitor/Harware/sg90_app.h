/**
 ******************************************************************************
 * @file    sg90_app.h
 * @brief   SG90���Ӧ�ò�ͷ�ļ�
 * @author
 * @date
 * @version V1.0
 ******************************************************************************
 */
#ifndef __SG90_APP_H
#define __SG90_APP_H

#include "bsp_system.h"

/* 宏定义 */
#define ANGLE_STEP 1          /* 步长:1°/步 */
#define ANGLE_STEP_PERIOD 100 /* 步长周期:100 ms */

/* sg90_state 状态宏定义 */
#define SG90_STATE_STOP 0   /* 停止状态 */
#define SG90_STATE_90 1     /* 转到90° */
#define SG90_STATE_0 2      /* 转到0° */
#define SG90_STATE_UP 3     /* 缓慢上升 */

/* ��������� */
void SG90_Proc(void);

/* ���ȫ�ֱ������� */
extern uint8_t sg90_angle;
extern uint32_t sg90_last_change;

#endif /* __SG90_APP_H */
