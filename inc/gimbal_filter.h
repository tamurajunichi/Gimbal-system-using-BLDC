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
#define EMA_K 0.6
/* Variable -------------------------------------------------------------------*/
float ema_val,pre_ema_val;
/* Functions ------------------------------------------------------------------*/
void filter_ema(float* p_val);
float filter_sma(float* p_val_array);

#endif /* __GIMBAL_FILTER_H */
/**********************************END OF FILE**********************************/
