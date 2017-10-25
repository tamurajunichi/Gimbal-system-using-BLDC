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
  * @brief     Timer IRQHandler functions
  *
@verbatim   
 ===============================================================================
                            ##### IRQHandlers #####
 ===============================================================================  
@endverbatim
  *
  */

/**
  * @fn     TIM2_IRQHandler
  * @brief  Count timer
  *
  * @param  None
  */
void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM2_Count++;
  }
}

/**
  * @fn     TIM6_IRQHandler
  * @brief  Generate sinusoidal pwm
  *
  * @param  None
  */
void TIM1_UP_TIM10_IRQHandler()
{
  if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    generate_sine_pwm();
  }
}

/**
  * @fn     TIM7_IRQHandler
  * @brief  Generate sinusoidal pwm
  *
  * @param  None
  */
void TIM7_IRQHandler()
{
  if(TIM_GetITStatus(TIM7,TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

  }
}

/**
  * @fn     TIM8_IRQHandler
  * @brief  Generate sinusoidal pwm
  *
  * @param  None
  */
void TIM8_UP_TIM13_IRQHandler()
{
  if(TIM_GetITStatus(TIM8,TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM8, TIM_IT_Update);

  }
}

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
  * TIM3 - 5 generete carrier frequency and output pins. 
  * TIM6 - 8 are used to generate the sinewaves with intterupt service.
  * TIM2 use as a watch.
  *
  * @param  None
  * @param  None
  */
void tim_init()
{
  TIM2_Count = 0;

  setup_tim_rcc();

  setup_carrier(TIM3);
  setup_carrier(TIM4);
  setup_carrier(TIM5);
  
  setup_tim_nvic();

  setup_sine(TIM1);
  setup_sine(TIM7);
  setup_sine(TIM8);
  setup_timer();
  
}

/**
  * @fn     setup_carrier
  * @brief  Setting the carrier frequency
  *
  * @param  TIMx select TIM1 - TIM8
  * @param  RCC_APB1Periph_TIMx 
  */
void setup_carrier(TIM_TypeDef* TIMx)
{
  setup_tim_gpio();

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
  * @brief  Setting intterupt timer for sinusoidal
  *
  * @param  TIMx select TIM6 - TIM8
  * @param  TIMx_IRQChannel select TIM6 - TIM8
  */
void setup_sine(TIM_TypeDef* TIMx)
{
  TIM_TimeBaseInitTypeDef TIM_BaseStruct;
  /*84000000 / (pre + 1) = 10kHz */
  TIM_BaseStruct.TIM_Prescaler = 839;
  TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  /*100000 / freq = TIM_Period + 1*/
  TIM_BaseStruct.TIM_Period = SINE_TIM_PERIOD;
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
  TIM_TimeBaseInitTypeDef TIM_BaseStruct;
  TIM_BaseStruct.TIM_Prescaler = CLOCK / 1000000 - 1 ;
  TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_BaseStruct.TIM_Period = 1000;
  TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_BaseStruct.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM2,&TIM_BaseStruct);
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM2,ENABLE);
}

/**
  * @fn     setup_tim_gpio
  * @brief  Setting GPIO pins with TIM3-5
  *
  * @param  TIM_GPIOInitStruct 
  */
void setup_tim_gpio()
{ 
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4,GPIO_AF_TIM5);

	GPIO_InitStruct.GPIO_Pin = TIM3_GPIO_PIN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = TIM4_GPIO_PIN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);


	GPIO_InitStruct.GPIO_Pin = TIM5_GPIO_PIN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

}

/**
  * @fn     setup_tim_nvic
  * @brief  Setting NVIC 
  *
  * @param  TIMx_IRQn Setting IRQChannel
  */
void setup_tim_nvic()
{
  NVIC_InitTypeDef NVIC_InitStruct;
  NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}

/**
  *@fn      setup_tim_rcc
  *@brief   supply clock 
  *
  *@param   None
  */
void setup_tim_rcc()
{
  RCC_AHB1PeriphClockCmd(RCC_GPIO,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1_TIM,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2_TIM,ENABLE);
}

/**
  *@fn      tim2_get_time
  *@brief   timer function 
  *
  *@param   None
  */
uint32_t tim2_get_time()
{
  return TIM2_Count;
}
/**********************************END OF FILE**********************************/
