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
  target_angle_x = TARGET_ANGLE_X;
  target_angle_y = TARGET_ANGLE_Y;
}

int dir_controler()
{
  if((target_angle_x - get_angle_x()) > 0)  return 1;
  if((target_angle_x - get_angle_x()) < 0 ) return -1;
}


/**********************************END OF FILE**********************************/
