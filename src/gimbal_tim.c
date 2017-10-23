/**
  ******************************************************************************
  * @file      gimbal_tim.c 
  * @brief     STM32F4 Timer setting file.
  * @author    Junichi
  * @date      22-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "gimbal_tim.h"

/* Functions -----------------------------------------------------------------*/

/**
  * @brief     Initialization and Configuration
  *
@verbatim   
 ===============================================================================
                 ##### Initialization and Configuration #####
 ===============================================================================  
@endverbatim
  *
  */

/** 
  * @fn     tim_init
  * @brief  Initialize the Timer
  *
  * This function is initialized 7Timers for gimbal.
  * 3 Timers generete carrier frequency and output pins. 
  * 3 Timers are used to generate the sinewaves with intterupt service.
  * A Timer`s role is watch.
  *
  * @param  None
  * @param  None
  */
void tim_init()
{
  TIM_GPIOInitTypeDef TIM_GPIOInit[2];

  user_struct_init(&TIM_GPIOInit);
  setup_tim_rcc();

  setup_carrier(TIM3,TIM_GPIOInit[0]);
  setup_carrier(TIM4,TIM_GPIOInit[1]);
  setup_carrier(TIM5,TIM_GPIOInit[2]);
  
  setup_sine(TIM6,TIM6_IRQn);
  setup_sine(TIM7,TIM7_IRQn);
  setup_sine(TIM8,TIM8_IRQn);

  setup_timer();
  
}

/**
  * @fn     setup_carrier
  * @brief  Setting the carrier frequency
  *
  * @param  TIMx select TIM1 - TIM8
  * @param  RCC_APB1Periph_TIMx 
  */
void setup_carrier(TIM_TypeDef* TIMx, TIM_GPIOInitTypeDef TIM_GPIOInit)
{
  setup_tim_gpio(TIM_GPIOInit);

  TIM_TimeBaseInitTypeDef TIM_BaseStruct;
  TIM_BaseStruct.TIM_Prescaler = 0;
  TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_BaseStruct.TIM_Period = CARRIER_TIM_PERIOD;
  TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_BaseStruct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIMx,&TIM_BaseStruct);
  TIM_Cmd(TIMx,ENABLE);

  TIM_OCInitTypeDef TIM_OCStruct;
  TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCStruct.TIM_Pulse = 0;
  TIM_OC2Init(TIMx,&TIM_OCStruct);
  TIM_OC2PreloadConfig(TIMx,TIM_OCPreload_Enable);
  TIM_OCStruct.TIM_Pulse = 0;
  TIM_OC3Init(TIMx,&TIM_OCStruct);
  TIM_OC3PreloadConfig(TIMx,TIM_OCPreload_Enable);
  TIM_OCStruct.TIM_Pulse = 0;
  TIM_OC4Init(TIMx,&TIM_OCStruct);
  TIM_OC4PreloadConfig(TIMx,TIM_OCPreload_Enable);

}

/**
  * @fn     setup_sine
  * @brief  Setting to Intterupt Timer increment sinetable[] with NVIC
  *
  * @param  TIMx select TIM6 - TIM8
  * @param  TIMx_IRQChannel select TIM6 - TIM8
  */
void setup_sine(TIM_TypeDef* TIMx, uint8_t TIMx_IRQn)
{
  setup_tim_nvic(TIMx_IRQn);

  TIM_TimeBaseInitTypeDef TIM_BaseStruct;
  TIM_BaseStruct.TIM_Prescaler = 839;
  TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_BaseStruct.TIM_Period = 999;
  TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_BaseStruct.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIMx,&TIM_BaseStruct);
  TIM_ClearITPendingBit(TIMx,TIM_IT_Update);
  TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIMx,ENABLE);
}

/**
  * @fn     setup_timer
  * @brief  Setting timer used Sampling Time
  *
  *@param   None
  */
void setup_timer()
{
  setup_tim_nvic(TIM2_IRQn);

  TIM_TimeBaseInitTypeDef TIM_BaseStruct;
  TIM_BaseStruct.TIM_Prescaler = 839;
  TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_BaseStruct.TIM_Period = 999;
  TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_BaseStruct.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM2,&TIM_BaseStruct);
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
  TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM2,ENABLE);
}

/**
  * @fn     setup_tim_gpio
  * @brief  Setting GPIO pins with TIM3-5
  *
  * @param  TIM_GPIOInitStruct 
  */
void setup_tim_gpio(TIM_GPIOInitTypeDef TIM_GPIOInitStruct)
{ 
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_PinAFConfig(TIM_GPIOInitStruct.GPIOx,TIM_GPIOInitStruct.GPIO_Pinsources,TIM_GPIOInitStruct.GPIO_AF);

  GPIO_InitStruct.GPIO_Pin = TIM_GPIOInitStruct.GPIO_Pins;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(TIM_GPIOInitStruct.GPIOx,&GPIO_InitStruct);
}

/**
  * @fn     user_struct_init
  * @brief  Structure TIM_GPIOInit initialized 
  *
  * @param  iTIM_GPIOInit Enter the TIM_GPIOInit[2] pointer
  */
void user_struct_init(TIM_GPIOInitTypeDef* iTIM_GPIOInit)
{
  iTIM_GPIOInit[] = {GPIOB,GPIO_AF_TIM3,TIM3_GPIO_PIN,TIM3_GPIO_PIN_SOURCE},
                    {GPIOD,GPIO_AF_TIM4,TIM3_GPIO_PIN,TIM4_GPIO_PIN_SOURCE},
                    {GPIOA,GPIO_AF_TIM5,TIM3_GPIO_PIN,TIM5_GPIO_PIN_SOURCE};
}

/**
  * @fn     setup_tim_nvic
  * @brief  Setting NVIC intterupt timer
  *
  * @param  TIMx_IRQn Setting IRQChannel
  */
void setup_tim_nvic(uint8_t TIMx_IRQn)
{
  NVIC_InitTypeDef NVIC_InitStruct;
  NVIC_InitStruct.NVIC_IRQChannel = TIMx_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}

/**
  *@fn      setup_tim_rcc
  *@brief   setting supply clock 
  *
  *@param   None
  */
void setup_tim_rcc()
{
  RCC_AHB1PeriphClockCmd(RCC_GPIO,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_TIM,ENABLE);
}

/**********************************END OF FILE**********************************/
