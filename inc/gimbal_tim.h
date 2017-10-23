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

/**
  * @brief  TIMx_GPIO_pins_define
  * 
  */
#define TIM3_GPIO_PIN ((uint16_t)(GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9))
#define TIM4_GPIO_PIN ((uint16_t)(GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin15))
#define TIM5_GPIO_PIN ((uint16_t)(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4))

#define TIM3_GPIO_PIN_SOURCE ((uint16_t)GPIO_PinSource7 | GPIO_PinSource8 | GPIO_PinSource9)
#define TIM4_GPIO_PIN_SOURCE ((uint16_t)GPIO_PinSource13 | GPIO_PinSource14 | GPIO_PinSource15)
#define TIM5_GPIO_PIN_SOURCE ((uint16_t)GPIO_PinSource2 | GPIO_PinSource3 | GPIO_PinSource4)

/**
  * @brief  RCC_define
  *
  */
#define RCC_GPIO  ((uint32_t)RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD)
#define RCC_TIM   ((uint32_t)RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7 | RCC_APB1Periph_TIM8)
/* Define struct --------------------------------------------------------------*/
/**
  * @brief  Define TIMx_GPIOInit struct 
  */
typedef struct{
  GPIO_TypeDef* GPIOx;
  uint8_t GPIO_AF
  uint16_t GPIO_Pins;
  uint16_t GPIO_Pinsources;
} TIM_GPIOInitTypeDef


/* Functions ------------------------------------------------------------------*/
void tim_init();
void user_struct_init(TIM_GPIOInitTypeDef* iTIM_GPIOInit);
void setup_carrier(TIM_TypeDef* TIMx, TIM_GPIOInitTypeDef TIM_GPIOInit);
void setup_sine(TIM_TypeDef* TIMx, uint8_t TIMx_IRQn);
void setup_timer();
void setup_tim_nvic(uint8_t TIMx_IRQn);
void setup_tim_gpio(TIM_GPIOInitTypeDef* TIM_GPIOInit);
void setup_tim_rcc();

#endif /* __GIMBAL_TIM_H */
/**********************************END OF FILE**********************************/
