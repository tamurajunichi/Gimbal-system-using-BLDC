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
#define WAITTIME 30
#define PRINTTIME 50
#define SINE_ARRAY_MAX 359

/* Variable -------------------------------------------------------------------*/
uint32_t samp_Time,print_Time;
float temp,angle_x,angle_y,angle_z,accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z;
float duty_phaseU,duty_phaseV,duty_phaseW;
int   phaseU,phaseV,phaseW;

/* Functions ------------------------------------------------------------------*/
void data_init();
void data_processing(uint32_t tim2_count);
void calc_mpu6050();
float proc_angle_z(float gyro_z);
float proc_angle_x(float accel_x);
float proc_angle_y(float accel_y);
float get_angle_x();
float get_angle_y();
void generate_sine_pwm();

#endif /* __GIMBAL_PROC_H */
/**********************************END OF FILE**********************************/
