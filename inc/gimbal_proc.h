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
#define WAITTIME 20
#define PRINTTIME 50
#define SINE_ARRAY_MAX 359

/* Variable -------------------------------------------------------------------*/
uint32_t samp_Time,print_Time;
float32_t temp,angle_x,angle_y,angle_z,accel_x,pre_accel_x,accel_y,pre_accel_y,accel_z,gyro_x,gyro_y,gyro_z;
float32_t duty_PhaseU,duty_PhaseV,duty_PhaseW;
int   phaseU,phaseV,phaseW,i;

/* Functions ------------------------------------------------------------------*/
void data_init();
void data_processing(uint32_t tim2_count);

void proc_mpu6050();
void proc_angle_z();
void proc_angle_x();
void proc_angle_y();

float32_t get_angle_x();
float32_t get_angle_y();
float32_t get_angle_z();
void generate_sine_pwm();

#endif /* __GIMBAL_PROC_H */
/**********************************END OF FILE**********************************/
