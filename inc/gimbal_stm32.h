/**
  *****************************************************************************
  * @file    gimbal_stm32.h
  * @author  Junichi Tamura
  * @version V0.0.1
  * @date    22-October-2017
  * @brief   Header configuration file.
  *****************************************************************************
  */

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_STM32_H
#define __GIMBAL_STM32_H

/* Includes ------------------------------------------------------------------*/
#include<arm_math.h>
#include"stm32f4xx_conf.h"
#include"stm32f4xx.h"
#include"usart.h"
#include"my_math.h"
#include"gimbal_proc.h"
#include"gimbal_tim.h"
#include"gimbal_mpu6050.h"
#include"gimbal_ctr.h"
#include"gimbal_filter.h"

#endif /*__GIMBAL_STM32_H */
