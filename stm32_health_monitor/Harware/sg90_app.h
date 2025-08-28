/**
 ******************************************************************************
 * @file    sg90_app.h
 * @brief   SG90¶æ»úÓ¦ÓÃ²ãÍ·ÎÄ¼ş
 * @author
 * @date
 * @version V1.0
 ******************************************************************************
 */
#ifndef __SG90_APP_H
#define __SG90_APP_H

#include "bsp_system.h"

/* å®å®šä¹‰ */
#define ANGLE_STEP 1          /* æ­¥é•¿:1Â°/æ­¥ */
#define ANGLE_STEP_PERIOD 100 /* æ­¥é•¿å‘¨æœŸ:100 ms */

/* sg90_state çŠ¶æ€å®å®šä¹‰ */
#define SG90_STATE_STOP 0   /* åœæ­¢çŠ¶æ€ */
#define SG90_STATE_90 1     /* è½¬åˆ°90Â° */
#define SG90_STATE_0 2      /* è½¬åˆ°0Â° */
#define SG90_STATE_UP 3     /* ç¼“æ…¢ä¸Šå‡ */

/* ¶æ»ú´¦Àíº¯Êı */
void SG90_Proc(void);

/* ¶æ»úÈ«¾Ö±äÁ¿ÉùÃ÷ */
extern uint8_t sg90_angle;
extern uint32_t sg90_last_change;

#endif /* __SG90_APP_H */
