/**
  ******************************************************************************
  * @file      gimbal_ctr.h  
  * @brief     STM32F4 calc setting file.
  * @author    Junichi
  * @date      24-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_CTR_H
#define __GIMBAL_CTR_H

/* Includes -------------------------------------------------------------------*/
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define TARGET_ANGLE 0

/* Variable -------------------------------------------------------------------*/
float32_t kp_x,ki_x,kd_x,kp_y,ki_y,kd_y,e[5],ux,uy;

/* Functions ------------------------------------------------------------------*/
void ctr_init();
int dir_ctr(float32_t dir_angle);
int pid_ctr(float32_t pid_angle,float32_t samp_time,TIM_TypeDef* target);

#endif /* __GIMBAL_CTR_H */
/**********************************END OF FILE**********************************/
