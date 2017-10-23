/**
  ******************************************************************************
  * @file      gimbal_mpu6050.h  
  * @brief     STM32F4 mpu6050 setting file.
  * @author    Junichi
  * @date      23-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_MPU6050_H
#define __GIMBAL_MPU6050_H

/* Includes -------------------------------------------------------------------*/
#include<math.h>
#include<string.h>
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define MPU6050_REG_SMPRT_DIV 25
#define MPU6050_REG_CONFIG 26
#define MPU6050_REG_GYRO_CONFIG 27
#define MPU6050_REG_ACCEL_CONFIG 28
#define MPU6050_REG_FIFO_EN 35
#define MPU6050_REG_INT_PIN_CFG 55
#define MPU6050_REG_INT_ENABLE 56
#define MPU6050_REG_INT_STATUS 58

#define MPU6050_REG_ACCEL_XOUT_H 59
#define MPU6050_REG_ACCEL_XOUT_L 60
#define MPU6050_REG_ACCEL_YOUT_H 61
#define MPU6050_REG_ACCEL_YOUT_L 62
#define MPU6050_REG_ACCEL_ZOUT_H 63
#define MPU6050_REG_ACCEL_ZOUT_L 64
#define MPU6050_REG_TEMP_OUT_H 65
#define MPU6050_REG_TEMP_OUT_L 66
#define MPU6050_REG_GYRO_XOUT_H 67
#define MPU6050_REG_GYRO_XOUT_L 68
#define MPU6050_REG_GYRO_YOUT_H 69
#define MPU6050_REG_GYRO_YOUT_L 70
#define MPU6050_REG_GYRO_ZOUT_H 71
#define MPU6050_REG_GYRO_ZOUT_L 72

#define MPU6050_REG_USER_CTRL 106
#define MPU6050_REG_PWR_MGMT_1 107
#define MPU6050_REG_PWR_MGMT_2 108
#define MPU6050_REG_FIFO_COUNT_H 114
#define MPU6050_REG_FIFO_COUNT_L 115
#define MPU6050_REG_FIFO_R_W 116
#define MPU6050_REG_WHOAMI 117

/* Functions ------------------------------------------------------------------*/
extern void I2C1_EV_IRQHandler(void);
extern void I2c!_ER_IRQHandler(void);
extern void DMA1_Stream0_IRQHandler(void);

void (*i2c_async_event_handler)(void);
void (*dma_event_handler)(void);



#endif /* __GIMBAL_MPU6050_H */
/**********************************END OF FILE**********************************/
