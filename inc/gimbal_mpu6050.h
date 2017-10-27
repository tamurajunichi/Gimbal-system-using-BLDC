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
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define MPU6050_I2C_ADDR 0x68

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


#define ACCEL_X     0
#define ACCEL_Y     1
#define ACCEL_Z     2
#define GYRO_X      3
#define GYRO_Y      4
#define GYRO_Z      5
#define TEMPERATURE 6

#define I2C_CLK 400000
/* Define variable ------------------------------------------------------------*/
uint8_t mpu6050_reg_buffer[14];
volatile uint32_t i2c_async_stage;
uint8_t i2c_async_reg;
uint8_t *i2c_async_buf;
uint32_t i2c_async_len;

int16_t val;
uint8_t buf[14];

/* Variable -------------------------------------------------------------------*/
/* This is apparently needed for libc/libm (eg. powf()). */
int __errno;

/* Functions ------------------------------------------------------------------*/
void delay(__IO uint32_t nCount);

void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void DMA1_Stream0_IRQHandler(void);

void (*i2c_async_event_handler)(void);
void (*dma_event_handler)(void);

void setup_i2c_for_mpu6050(void);
void read_mpu6050_reg_multi(uint8_t reg, uint8_t *buf, uint32_t len);
uint8_t read_mpu6050_reg(uint8_t reg);
void async_read_event_handler(void);
void dma_done_handler(void);
void async_read_mpu6050reg_multi(uint8_t reg, uint8_t *buf, uint32_t len);
void write_mpu6050_reg(uint8_t reg, uint8_t val);
void setup_mpu6050(void);

int16_t mpu6050_get_data(int data_type);
#endif /* __GIMBAL_MPU6050_H */
/**********************************END OF FILE**********************************/
