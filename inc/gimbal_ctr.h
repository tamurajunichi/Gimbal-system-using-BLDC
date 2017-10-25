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
#define TARGET_ANGLE_X 0
#define TARGET_ANGLE_Y 0
/* Variable -------------------------------------------------------------------*/
float target_angle_x;
float target_angle_y;

/* Functions ------------------------------------------------------------------*/
void ctr_init();
int dir_controler();

#endif /* __GIMBAL_CTR_H */
/**********************************END OF FILE**********************************/
