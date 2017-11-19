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
  * @fn     filter_init
  * @brief  
  *
  * @param None
  */
void filter_init()
{
  ema_val=0;
  pre_ema_val=0;
  avg_accel_x=0;
  avg_accel_y=0;
  avg_accel_z=0;
  avg_gyro_x=0;
  avg_gyro_y=0;
  avg_gyro_z=0;
  func_count=0;

  Q_angle = 0.001;
  Q_gyro = 0.003;
  R_angle = 0.03;
  x_bias = 0;

  p[0][0] = 0;
  p[1][0] = 0;
  p[0][1] = 0;
  p[1][1] = 0;
  dt = 0.005;

}


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


/**
  * @fn     del_offset
  * @brief  
  *
  * @param ax 
  * @param ay      
  * @param *p_offset_x 
  * @param *p_offset_y 
  */
int del_accel_offset(float32_t ax, float32_t ay,float32_t* p_offset_ax,float32_t* p_offset_ay)
{
  func_count++;
  avg_accel_x += ax;
  avg_accel_y += ay;

  if(func_count >= 1500){
    *p_offset_ax = avg_accel_x/1500.0f;
    *p_offset_ay = avg_accel_y/1500.0f;
    return 1;
  }
  return 0;
}

/**
  * @fn     del_offset
  * @brief  
  *
  * @param ax 
  * @param ay      
  * @param *p_offset_x 
  * @param *p_offset_y 
  */
int del_gyro_offset(float32_t gx, float32_t gy,float32_t gz,float32_t* p_offset_gx,float32_t* p_offset_gy,float32_t* p_offset_gz)
{
  avg_gyro_x += gx;
  avg_gyro_y += gy;
  avg_gyro_z += gz;

  if(func_count >= 1500){
    *p_offset_gx = avg_gyro_x/1500.0f;
    *p_offset_gy = avg_gyro_y/1500.0f;
    *p_offset_gz = avg_gyro_z/1500.0f;
    return 1;
  }
  return 0;
}

/**
  * @fn     filter_kalman
  * @brief  
  *
  * @param p_pre_val  
  * @param p_val      
  */
float32_t filter_kalman(float32_t new_angle, float32_t new_rate)
{
  x_angle += dt * (new_rate - x_bias);

  p[0][0] += dt * (dt * p[1][1] - p[0][1] - p[1][0] + Q_angle);
  p[0][1] -= dt * p[1][1];
  p[1][0] -= dt * p[1][1];
  p[1][1] += Q_gyro * dt;

  y = new_angle - x_angle;
  S = p[0][0] + R_angle;
  k[0] = p[0][0] / S;
  k[1] = p[1][0] / S;

  x_angle += k[0] * y;
  x_bias  += k[1] * y;

  p[0][0] -= k[0]*p[0][0];
  p[0][1] -= k[0]*p[0][1];
  p[1][0] -= k[1]*p[0][0];
  p[1][1] -= k[1]*p[0][1];

  return x_angle;
}

/**********************************END OF FILE**********************************/
