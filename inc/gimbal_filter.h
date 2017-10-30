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
float32_t ema_val,pre_ema_val;
/* Functions ------------------------------------------------------------------*/
float32_t filter_ema(float32_t val, float32_t pre_val);
float32_t filter_sma(float32_t* p_val_array);

#endif /* __GIMBAL_FILTER_H */
/**********************************END OF FILE**********************************/
