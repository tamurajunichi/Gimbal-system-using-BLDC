/**
  ******************************************************************************
  * @file      gimbal_proc.h  
  * @brief     STM32F4 calc setting file.
  * @author    Junichi
  * @date      22-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_PROC_H
#define __GIMBAL_PROC_H

/* Includes -------------------------------------------------------------------*/
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define WAITTIME 50
#define SINE_ARRAY_MAX 359

/* Variable -------------------------------------------------------------------*/
uint32_t samp_Time;

float32_t temp,pre_angle_x,pre_angle_y,angle_x,angle_y,angle_z,accel_angle_x,accel_angle_y,gyro_angle_x,gyro_angle_y,gyro_angle_z,c_angle_x,c_angle_y,c_pre_angle_x,c_pre_angle_y,accel_x,pre_accel_x,accel_y,pre_accel_y,accel_z,gyro_x,gyro_y,gyro_z,offset_ax,offset_ay,offset_az,offset_gx,offset_gy,offset_gz,duty_Phaseu_x,duty_Phasev_x,duty_Phasew_x,duty_Phaseu_y,duty_Phasev_y,duty_Phasew_y,print_Time,i,dbg_period_x,dbg_period_y,i_angle_x,i_angle_y;

int   phaseu_x,phasev_x,phasew_x,phaseu_y,phasev_y,phasew_y,flag;

/* Functions ------------------------------------------------------------------*/
void data_init();
void data_processing(uint32_t tim2_count);

void proc_mpu6050();
void proc_gyro_angle();
void proc_accel_angle();
void proc_angle();

float32_t get_angle_x();
float32_t get_angle_y();
float32_t get_angle_z();
void generate_sine_pwm(int dir_angle, TIM_TypeDef* TIMx);

#endif /* __GIMBAL_PROC_H */
/**********************************END OF FILE**********************************/
