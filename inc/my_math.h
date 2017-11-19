/**
  ******************************************************************************
  * @file      my_math.h  
  * @brief     STM32F4 calc setting file.
  * @author    Junichi
  * @date      30-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __MY_MATH_H
#define __MY_MATH_H

/* Includes -------------------------------------------------------------------*/
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define TABLE_SIXE_ATAN   (577)
#define BLOCK_NUM_ATAN    (26)
#define DEBIDE_ONE_BLOCK_ATAN  (24)

/* Variable -------------------------------------------------------------------*/

/* Functions ------------------------------------------------------------------*/
float myAtan(float32_t x);
float myAtan2(float32_t y,float32_t x);
float32_t mypowf(float32_t src,uint32_t n);
void round_3(float32_t* val);
#endif /* __MY_MATH_H */
/**********************************END OF FILE**********************************/
