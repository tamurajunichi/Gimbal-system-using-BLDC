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
    e[j] = 0;
  }

  kp_x = 2000.0f;
  ki_x = 0.0f;
  kd_x = 0.0f;
  kp_y = 0.0f;
  ki_y = 0.0f;
  kd_y = 0.0f;

  ux = 65535.0f;
  uy = 65535.0f;
}

int dir_ctr(float32_t dir_angle)
{
    if((TARGET_ANGLE - dir_angle) > 0.0f){
      return -1;
    }else if((TARGET_ANGLE - dir_angle) < 0.0f){
        return 1;
    }
}

int pid_ctr(float32_t pid_angle,float32_t samp_time,TIM_TypeDef* target)
{
  if(target == TIM1)
  {

    if(pid_angle < 0)pid_angle = -pid_angle;
    e[0] = (float32_t)TARGET_ANGLE - pid_angle;

    ux += kp_x*(e[0] - e[1])+ki_x*e[0]+kd_x*((e[0]-e[1])-(e[1]-e[2]));  

    if(ux < 10000.0f)ux = 10000.0f;
    if(ux>65535.0f)ux=65535.0f;


    e[2] = e[1];
    e[1] = e[0];
    return ux;
  }
  if(target == TIM7)
  {
    e[3] = (float32_t)TARGET_ANGLE - pid_angle;
    uy += (int)(kp_y*e[3]+ ki_y*(e[3] + e[4] + e[5])*samp_time);  
    if(uy < 0)uy = 0;

    e[5] = e[4];
    e[4] = e[3];
    return uy;
  }
}

/**********************************END OF FILE**********************************/
