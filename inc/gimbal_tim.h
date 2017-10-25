/**
  ******************************************************************************
  * @file      gimbal_tim.h  
  * @brief     STM32F4 Timer setting file.
  * @author    Junichi
  * @date      22-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_TIM_H
#define __GIMBAL_TIM_H

/* Includes -------------------------------------------------------------------*/
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define CARRIER_TIM_PERIOD 8399
#define CLOCK 84000000
#define SINE_TIM_PERIOD 500
/**
  * @brief  TIMx_GPIO_pins_define
  * 
  */
#define TIM3_GPIO_PIN ((uint16_t)(GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9))
#define TIM4_GPIO_PIN ((uint16_t)(GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15))
#define TIM5_GPIO_PIN ((uint16_t)(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4))

#define TIM3_GPIO_PIN_SOURCE ((uint16_t)GPIO_PinSource7 | GPIO_PinSource8 | GPIO_PinSource9)
#define TIM4_GPIO_PIN_SOURCE ((uint16_t)GPIO_PinSource13 | GPIO_PinSource14 | GPIO_PinSource15)
#define TIM5_GPIO_PIN_SOURCE ((uint16_t)GPIO_PinSource2 | GPIO_PinSource3 | GPIO_PinSource4)

/**
  * @brief  RCC_define
  *
  */
#define RCC_GPIO  ((uint32_t)RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD)
#define RCC_APB1_TIM   ((uint32_t)RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM7 )
#define RCC_APB2_TIM ((uint32_t)RCC_APB2Periph_TIM1 | RCC_APB2Periph_TIM8)

/* Variable -------------------------------------------------------------------*/
int __errno;

uint32_t TIM2_Count;

/* Functions ------------------------------------------------------------------*/

void delay(__IO uint32_t nCount);

void TIM2_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM7_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);

void tim_init();
void setup_carrier(TIM_TypeDef* TIMx);
void setup_sine(TIM_TypeDef* TIMx);
void setup_timer();
void setup_tim_nvic();
void setup_tim_gpio();
void setup_tim_rcc();

uint32_t tim2_get_time();

#endif /* __GIMBAL_TIM_H */
/**********************************END OF FILE**********************************/
