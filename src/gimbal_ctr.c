/**
  ******************************************************************************
  * @file      gimbal_ctr.h  
  * @brief     STM32F4 calc setting file.
  * @author    Junichi
  * @date      22-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Includes -------------------------------------------------------------------*/
#include "gimbal_ctr.h"


/* Variable -------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/
void ctr_init()
{
  int j;

  for(j=0;j<6;j++){
    e[j] = 0.0f;
  }

  kp_x = 5.00f;
  ki_x = 0.00f;
  kd_x = 0.07f;
  kp_y = 0.5f;
  ki_y = 0.0f;
  kd_y = 0.0f;
  /*kp_y = 18.0f;
  ki_y = 17.8f;
  kd_y = 0.0082f;*/

  ux = 0.0f;
  uy = 0.0f;

  i_sum_x = 0.0f;
  i_sum_y = 0.0f;

  dir_x = 0;
  dir_y = 0;
}

int dir_ctr(TIM_TypeDef* target,int dir)
{
  if(target == TIM1){
    dir_x = dir;
  }
  else if(target == TIM7){
    dir_y = dir;
  }
}

int get_dir(TIM_TypeDef* target)
{
  if(target == TIM1)return dir_x;
  if(target == TIM7)return dir_y;
}

float32_t pid_ctr(float32_t pid_angle,float32_t samp_time,TIM_TypeDef* target)
{
  //ux and uy is [deg/s]

  //if(pid_angle < 0)pid_angle = -pid_angle;

  if(target == TIM1)
  {
    if(pid_angle < 0.2f && pid_angle > -0.2f)pid_angle = 0.0f;

    e[2] = e[1];
    e[1] = e[0];
    e[0] = (float32_t)TARGET_ANGLE - pid_angle;
    i_sum_x += (e[0] + e[1]) / 2.0f * samp_time;

    ux = kp_x*e[0] + ki_x*i_sum_x + kd_x*(e[1] - e[0])/samp_time;
    
    //CW
    if(ux < 0){
      if(ux < -400)ux = -400;      
      tim1_period = -((84000.0f / (6.0f * ux)) + 1.0f);
      dir_ctr(target,1);
    }else
    //CCW
    if(ux > 0){
      if(ux > 400)ux = 400;
      tim1_period = (84000.0f / (6.0f * ux)) + 1.0f;
      dir_ctr(target,-1);
    }
    
    if(tim1_period > 65535.0f)tim1_period = 65535.0f;
    return tim1_period;
  }
  if(target == TIM7)
  {
    //if(pid_angle < 0.3f && pid_angle > -0.3f)pid_angle = 0.0f;

    e[5] = e[4];
    e[4] = e[3];
    e[3] = (float32_t)TARGET_ANGLE - pid_angle;
    i_sum_y += (e[3] + e[4]) / 2.0f * samp_time;

    uy = kp_y*e[3] + ki_y*i_sum_y + kd_y*(e[4] - e[3])/samp_time;

    //CW
    if(uy < 0){
      if(uy < -400)uy = -400;      
      tim2_period = -((84000.0f / (6.0f * uy)) + 1.0f);
      dir_ctr(target,1);
    }else
    //CCW
    if(uy > 0){
      if(uy > 400)uy = 400;
      tim2_period = (84000.0f / (6.0f * uy)) + 1.0f;
      dir_ctr(target,-1);
    }
    
    if(tim2_period > 65535.0f)tim2_period = 65535.0f;
    return tim2_period;
  }
}

float32_t get_kp(TIM_TypeDef* TIMx)
{
  if(TIMx == TIM1)return kp_x;
  if(TIMx == TIM7)return kp_y;
}

float32_t set_kp(float32_t set_kp,TIM_TypeDef* TIMx)
{
  if(TIMx == TIM1){
    kp_x = set_kp;
    get_kp(TIMx);
  }
  if(TIMx == TIM7){
    kp_y = set_kp;
    get_kp(TIMx);
  }
}

float32_t get_u(TIM_TypeDef* TIMx)
{
  if(TIMx == TIM1)return ux;
  if(TIMx == TIM7)return uy;
}
/**********************************END OF FILE**********************************/
