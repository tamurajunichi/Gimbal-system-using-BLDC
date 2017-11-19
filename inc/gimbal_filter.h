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
#define EMA_K 0.1
/* Variable -------------------------------------------------------------------*/
float32_t ema_val,pre_ema_val,avg_accel_x,avg_accel_y,avg_accel_z,avg_gyro_x,avg_gyro_y,avg_gyro_z,Q_angle,Q_gyro,R_angle,x_angle,x_bias,p[1][1],y,S,k[1],dt,kal_deg;
uint32_t func_count;
/* Functions ------------------------------------------------------------------*/
void filter_init();
float32_t filter_ema(float32_t val, float32_t pre_val);
int del_accel_offset(float32_t ax, float32_t ay,float32_t* p_offset_ax,float32_t* p_offset_ay);
int del_gyro_offset(float32_t gx, float32_t gy,float32_t gz,float32_t* p_offset_gx,float32_t* p_offset_gy,float32_t* p_offset_gz);
float32_t filter_sma(float32_t* p_val_array);
float32_t filter_kalman(float32_t new_angle, float32_t new_rate);

#endif /* __GIMBAL_FILTER_H */
/**********************************END OF FILE**********************************/
