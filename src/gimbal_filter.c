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
const float32_t ema_k = 0.05f;

/* Functions ------------------------------------------------------------------*/
/**
  * @fn     filter_init
  * @brief  
  *
  * @param None
  */
void filter_init()
{
  ema_val=0.0f;
  pre_ema_val=0.0f;
  avg_accel_x=0.0f;
  avg_accel_y=0.0f;
  avg_accel_z=0.0f;
  avg_gyro_x=0.0f;
  avg_gyro_y=0.0f;
  avg_gyro_z=0.0f;
  func_count=0.0f;

  Q_angle = 0.001f;
  Q_gyro = 0.003f;
  R_angle = 0.03f;

  x_bias = 0.0f;
  y_bias = 0.0f;

  p_00_x = 0.0f;
  p_10_x = 0.0f;
  p_01_x = 0.0f;
  p_11_x = 0.0f;

  p_00_y = 0.0f;
  p_10_y = 0.0f;
  p_01_y = 0.0f;
  p_11_y = 0.0f;

  dt = 0.01;

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
   return(val * (float32_t)ema_k) + (pre_val * (float32_t)(1.0f - ema_k));
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

  if(func_count >= 4000){
    *p_offset_ax = avg_accel_x/4000.0f;
    *p_offset_ay = avg_accel_y/4000.0f;
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

  if(func_count >= 4000){
    *p_offset_gx = avg_gyro_x/4000.0f;
    *p_offset_gy = avg_gyro_y/4000.0f;
    *p_offset_gz = avg_gyro_z/4000.0f;
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
float32_t filter_kalman(float32_t new_angle, float32_t new_rate,TIM_TypeDef* TIMx)
{
  if(TIMx == TIM1){
    x_angle += dt * (new_rate - x_bias);

    p_00_x += dt * (dt * p_11_x - p_01_x - p_10_x + Q_angle);
    p_01_x -= dt * p_11_x;
    p_10_x -= dt * p_11_x;
    p_11_x += Q_gyro * dt;

    y_x = new_angle - x_angle;
    S_x = p_00_x + R_angle;
    k_0_x = p_00_x / S_x;
    k_1_x = p_10_x / S_x;

    x_angle += k_0_x * y_x;
    x_bias  += k_1_x * y_x;

    p_00_x -= k_0_x*p_00_x;
    p_01_x -= k_0_x*p_01_x;
    p_10_x -= k_1_x*p_00_x;
    p_11_x -= k_1_x*p_01_x;

    return x_angle;
  }else
  if(TIMx == TIM7){
    y_angle += dt * (new_rate - y_bias);

    p_00_y += dt * (dt * p_11_y - p_01_y - p_10_y + Q_angle);
    p_01_y -= dt * p_11_y;
    p_10_y -= dt * p_11_y;
    p_11_y += Q_gyro * dt;

    y_y = new_angle - y_angle;
    S_y = p_00_y + R_angle;
    k_0_y = p_00_y / S_y;
    k_1_y = p_10_y / S_y;

    y_angle += k_0_y * y_y;
    y_bias  += k_1_y * y_y;

    p_00_y -= k_0_y*p_00_y;
    p_01_y -= k_0_y*p_01_y;
    p_10_y -= k_1_y*p_00_y;
    p_11_y -= k_1_y*p_01_y;

    return y_angle;
  }

}

/**********************************END OF FILE**********************************/
