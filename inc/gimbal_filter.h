/**
  ******************************************************************************
  * @file      gimbal_filter.h  
  * @brief     STM32F4 data filter setting file.
  * @author    Junichi
  * @date      27-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_FILTER_H
#define __GIMBAL_FILTER_H

/* Includes -------------------------------------------------------------------*/
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/

/* Variable -------------------------------------------------------------------*/

float32_t ema_val,pre_ema_val,avg_accel_x,avg_accel_y,avg_accel_z,avg_gyro_x,avg_gyro_y,avg_gyro_z,Q_angle,Q_gyro,R_angle,x_angle,y_angle,x_bias,y_bias,p_00_x,p_01_x,p_10_x,p_11_x,p_00_y,p_01_y,p_10_y,p_11_y,y_x,y_y,S_x,S_y,k_0_x,k_1_x,k_0_y,k_1_y,dt,kal_deg;

uint32_t func_count;
/* Functions ------------------------------------------------------------------*/
void filter_init();
float32_t filter_ema(float32_t val, float32_t pre_val);
int del_accel_offset(float32_t ax, float32_t ay,float32_t* p_offset_ax,float32_t* p_offset_ay);
int del_gyro_offset(float32_t gx, float32_t gy,float32_t gz,float32_t* p_offset_gx,float32_t* p_offset_gy,float32_t* p_offset_gz);
float32_t filter_sma(float32_t* p_val_array);
float32_t filter_kalman(float32_t new_angle, float32_t new_rate,TIM_TypeDef* TIMx);

#endif /* __GIMBAL_FILTER_H */
/**********************************END OF FILE**********************************/
