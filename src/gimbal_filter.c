/**
  ******************************************************************************
  * @file      gimbal_filter.c
  * @brief     STM32F4 calc setting file.
  * @author    Junichi
  * @date      27-October-2017
  * @version   1.0
  ******************************************************************************
  */ 
  
/* Includes -------------------------------------------------------------------*/
#include "gimbal_filter.h"

/* Variable -------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/

/**
  * @fn     filter_ema
  * @brief  
  *
  * @param p_pre_val  
  * @param p_val      
  */
float filter_ema(float32_t val, float32_t pre_val)
{
   return(val * (float32_t)EMA_K) + (pre_val * (float32_t)(1 - EMA_K));
}

/**********************************END OF FILE**********************************/
