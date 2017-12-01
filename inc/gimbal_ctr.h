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
float32_t kp_x,ki_x,kd_x,kp_y,ki_y,kd_y,e[5],ux,uy,tim1_period,tim2_period,i_sum_x,i_sum_y;

int dir_x,dir_y;
/* Functions ------------------------------------------------------------------*/
void ctr_init();
int dir_ctr(TIM_TypeDef* target,int dir);
int get_dir(TIM_TypeDef* target);
float32_t pid_ctr(float32_t pid_angle,float32_t samp_time,TIM_TypeDef* target);
float32_t get_kp(TIM_TypeDef* TIMx);
float32_t set_kp(float32_t set_kp, TIM_TypeDef* TIMx);
float32_t get_u(TIM_TypeDef* TIMx);

#endif /* __GIMBAL_CTR_H */
/**********************************END OF FILE**********************************/
