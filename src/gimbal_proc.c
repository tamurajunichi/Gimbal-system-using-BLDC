/**
  ******************************************************************************
  * @file      gimbal_calc.c  
  * @brief     STM32F4 calc setting file.
  * @author    Junichi
  * @date      24-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Includes -------------------------------------------------------------------*/
#include "gimbal_proc.h"
/* Variable -------------------------------------------------------------------*/
const float32_t sine_Array[]={0.50 ,	0.51 ,	0.52 ,	0.53 ,	0.53 ,	0.54 ,	0.55 ,	0.56 ,	0.57 ,	0.58 ,	0.59 ,	0.60 ,	0.60 ,	0.61 ,	0.62 ,	0.63 ,	0.64 ,	0.65 ,	0.65 ,	0.66 ,	0.67 ,	0.68 ,	0.69 ,	0.70 ,	0.70 ,	0.71 ,	0.72 ,	0.73 ,	0.73 ,	0.74 ,	0.75 ,	0.76 ,	0.76 ,	0.77 ,	0.78 ,	0.79 ,	0.79 ,	0.80 ,	0.81 ,	0.81 ,	0.82 ,	0.83 ,	0.83 ,	0.84 ,	0.85 ,	0.85 ,	0.86 ,	0.87 ,	0.87 ,	0.88 ,	0.88 ,	0.89 ,	0.89 ,	0.90 ,	0.90 ,	0.91 ,	0.91 ,	0.92 ,	0.92 ,	0.93 ,	0.93 ,	0.94 ,	0.94 ,	0.95 ,	0.95 ,	0.95 ,	0.96 ,	0.96 ,	0.96 ,	0.97 ,	0.97 ,	0.97 ,	0.98 ,	0.98 ,	0.98 ,	0.98 ,	0.99 ,	0.99 ,	0.99 ,	0.99 ,	0.99 ,	0.99 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	1.00 ,	0.99 ,	0.99 ,	0.99 ,	0.99 ,	0.99 ,	0.99 ,	0.98 ,	0.98 ,	0.98 ,	0.98 ,	0.97 ,	0.97 ,	0.97 ,	0.96 ,	0.96 ,	0.96 ,	0.95 ,	0.95 ,	0.95 ,	0.94 ,	0.94 ,	0.93 ,	0.93 ,	0.92 ,	0.92 ,	0.91 ,	0.91 ,	0.90 ,	0.90 ,	0.89 ,	0.89 ,	0.88 ,	0.88 ,	0.87 ,	0.87 ,	0.86 ,	0.85 ,	0.85 ,	0.84 ,	0.83 ,	0.83 ,	0.82 ,	0.81 ,	0.81 ,	0.80 ,	0.79 ,	0.79 ,	0.78 ,	0.77 ,	0.76 ,	0.76 ,	0.75 ,	0.74 ,	0.73 ,	0.73 ,	0.72 ,	0.71 ,	0.70 ,	0.70 ,	0.69 ,	0.68 ,	0.67 ,	0.66 ,	0.65 ,	0.65 ,	0.64 ,	0.63 ,	0.62 ,	0.61 ,	0.60 ,	0.60 ,	0.59 ,	0.58 ,	0.57 ,	0.56 ,	0.55 ,	0.54 ,	0.53 ,	0.53 ,	0.52 ,	0.51 ,	0.50 ,	0.49 ,	0.48 ,	0.47 ,	0.47 ,	0.46 ,	0.45 ,	0.44 ,	0.43 ,	0.42 ,	0.41 ,	0.40 ,	0.40 ,	0.39 ,	0.38 ,	0.37 ,	0.36 ,	0.35 ,	0.35 ,	0.34 ,	0.33 ,	0.32 ,	0.31 ,	0.30 ,	0.30 ,	0.29 ,	0.28 ,	0.27 ,	0.27 ,	0.26 ,	0.25 ,	0.24 ,	0.24 ,	0.23 ,	0.22 ,	0.21 ,	0.21 ,	0.20 ,	0.19 ,	0.19 ,	0.18 ,	0.17 ,	0.17 ,	0.16 ,	0.15 ,	0.15 ,	0.14 ,	0.13 ,	0.13 ,	0.12 ,	0.12 ,	0.11 ,	0.11 ,	0.10 ,	0.10 ,	0.09 ,	0.09 ,	0.08 ,	0.08 ,	0.07 ,	0.07 ,	0.06 ,	0.06 ,	0.05 ,	0.05 ,	0.05 ,	0.04 ,	0.04 ,	0.04 ,	0.03 ,	0.03 ,	0.03 ,	0.02 ,	0.02 ,	0.02 ,	0.02 ,	0.01 ,	0.01 ,	0.01 ,	0.01 ,	0.01 ,	0.01 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.00 ,	0.01 ,	0.01 ,	0.01 ,	0.01 ,	0.01 ,	0.01 ,	0.02 ,	0.02 ,	0.02 ,	0.02 ,	0.03 ,	0.03 ,	0.03 ,	0.04 ,	0.04 ,	0.04 ,	0.05 ,	0.05 ,	0.05 ,	0.06 ,	0.06 ,	0.07 ,	0.07 ,	0.08 ,	0.08 ,	0.09 ,	0.09 ,	0.10 ,	0.10 ,	0.11 ,	0.11 ,	0.12 ,	0.12 ,	0.13 ,	0.13 ,	0.14 ,	0.15 ,	0.15 ,	0.16 ,	0.17 ,	0.17 ,	0.18 ,	0.19 ,	0.19 ,	0.20 ,	0.21 ,	0.21 ,	0.22 ,	0.23 ,	0.24 ,	0.24 ,	0.25 ,	0.26 ,	0.27 ,	0.27 ,	0.28 ,	0.29 ,	0.30 ,	0.30 ,	0.31 ,	0.32 ,	0.33 ,	0.34 ,	0.35 ,	0.35 ,	0.36 ,	0.37 ,	0.38 ,	0.39 ,	0.40 ,	0.40 ,	0.41 ,	0.42 ,	0.43 ,	0.44 ,	0.45 ,	0.46 ,	0.47 ,	0.47 ,	0.48 ,	0.49 
};


/* Functions ------------------------------------------------------------------*/

/**
  * @fn     data_init
  * @bried  initialization data
  * 
  * @param  None
  */
void data_init()
{
  phaseu_x      = 0;
  phasev_x      = 120;
  phasew_x      = 240;
  phaseu_y      = 0;
  phasev_y      = 120;
  phasew_y      = 240;
  duty_Phaseu_x = 0.0f;
  duty_Phasev_x = 0.0f;
  duty_Phasew_x = 0.0f;
  duty_Phaseu_y = 0.0f;
  duty_Phasev_y = 0.0f;
  duty_Phasew_y = 0.0f;

  pre_accel_x = 0.0f;
  pre_accel_y = 0.0f;

  gyro_angle_x = 0.0f;
  gyro_angle_y = 0.0f;
  gyro_angle_z = 0.0f;

  gyro_angle_x = 0.0f;
  gyro_angle_y = 0.0f;
  accel_angle_x = 0.0f;
  accel_angle_y = 0.0f;
  angle_x = 0.0f;
  angle_y = 0.0f;

  offset_az = 0.0f;
  offset_gx = 0.0f;
  offset_gy = 0.0f;
  offset_gz = 0.0f;

  flag = 0;
  i = 10.0f;
  dbg_period_x = 0.0f;
  dbg_period_y = 0.0f;

  samp_Time  = tim2_get_time();
  print_Time = 0.0f;

  //serial_puts(USART3,"\nTIME\tANGLE_X\tANGLE_Y\tACCEL_X\tACCEL_Y\tACCEL_Z\t");
  //serial_puts(USART3,"GYRO_X\tGYRO_Y\tGYRO_Z\n");
}


/**
  * @fn     data_processing
  * @bried  process data
  * 
  * @param  tim2_count
  */
void data_processing(uint32_t tim2_count)
{
  if((tim2_count - samp_Time) >= WAITTIME){
   samp_Time  = tim2_count;
   print_Time = (float32_t)samp_Time / 10000.0f;

   /*if(print_Time > 15.0f){
   if(((int)(print_Time*100.0f) % 500 == 0) && (flag == 1))i += 1.0f;
   }*/

    proc_mpu6050();

  if(flag == 0  || print_Time <= 15.0f){
    print_float(USART3,print_Time,5,3);
    serial_puts(USART3,",");
    print_float(USART3,accel_z,3,3);
    serial_puts(USART3,"\n");
   }
   else if(flag == 1 && print_Time > 15.0f){
    print_float(USART3,print_Time,5,3);
    serial_puts(USART3,",");
    print_float(USART3,angle_x,3,3);
    serial_puts(USART3,",");
    print_float(USART3,angle_y,3,3);
    /*serial_puts(USART3,",");
    print_float(USART3,angle_z,3,3);
    serial_puts(USART3,",");
    print_float(USART3,accel_x,3,3);
    serial_puts(USART3,",");
    print_float(USART3,accel_y,3,3);
    serial_puts(USART3,",");
    print_float(USART3,accel_z,3,3);
    serial_puts(USART3,",");
    print_float(USART3,gyro_x,5,3);
    serial_puts(USART3,",");
    print_float(USART3,gyro_y,5,3);
    serial_puts(USART3,",");
    print_float(USART3,gyro_z,5,3);*/
    serial_puts(USART3,",");
    print_float(USART3,get_u(TIM1),3,3);
    serial_puts(USART3,",");
    print_float(USART3,get_u(TIM7),3,3);
    /*serial_puts(USART3,",");
    print_float(USART3,set_kp(i,TIM1),3,3);
    serial_puts(USART3,",");
    print_float(USART3,set_kp(i,TIM7),3,3);*/
    serial_puts(USART3,"\n");
   }

 }
}

/**
  * @fn     proc_mpu6050
  * @bried  processing of accel and gyro data
  * 
  * @param  None
  */
void proc_mpu6050()
{

  accel_x = (float32_t)(mpu6050_get_data(ACCEL_X)/2048.0f)-offset_ax;
  accel_y = (float32_t)(mpu6050_get_data(ACCEL_Y)/2048.0f)-offset_ay;
  accel_z = (float32_t)mpu6050_get_data(ACCEL_Z)/2048.0f;
  gyro_x  = (float32_t)(mpu6050_get_data(GYRO_X)/16.4f)-offset_gx;
  gyro_y  = (float32_t)(mpu6050_get_data(GYRO_Y)/16.4f)-offset_gy;
  gyro_z  = (float32_t)(mpu6050_get_data(GYRO_Z)/16.4f)-offset_gz;
  temp    = (float32_t)mpu6050_get_data(TEMPERATURE)/340.0f+36.53f;
  
  if(flag == 0){
    del_accel_offset(accel_x,accel_y,&offset_ax,&offset_ay);
    flag = del_gyro_offset(gyro_x,gyro_y,gyro_z,&offset_gx,&offset_gy,&offset_gz);
  }else if(flag == 1 && print_Time > 15.0f){
  proc_accel_angle();
  proc_angle();

  dbg_period_x = resetup_sine(TIM1,pid_ctr(angle_x,0.005f,TIM1));
  dbg_period_y = resetup_sine(TIM7,pid_ctr(angle_y,0.005f,TIM7));
  }

}

/**
  * @fn     proc_angle_x
  * @bried  processing of data
  * 
  * @param  accel_x
  */
void proc_accel_angle()
{
  float32_t sqrt;
  
  /* origin accel_x LPF */
  //accel_x = filter_ema(accel_x,pre_accel_x);
  //pre_accel_x = accel_x;
  arm_sqrt_f32((accel_y*accel_y + accel_z*accel_z),&sqrt);
  accel_angle_x = myAtan(accel_x/sqrt) * 180.0f / PI;

  /* origin accel_y LPF */
  //accel_y = filter_ema(accel_y,pre_accel_y);
  //pre_accel_y = accel_y;
  arm_sqrt_f32((accel_x*accel_x + accel_z*accel_z),&sqrt);
  accel_angle_y = myAtan(accel_y/sqrt) * 180.0f / PI;
}

/**
  * @fn     proc_angle_x
  * @bried  processing of data
  * 
  * @param  accel_x
  */
void proc_gyro_angle()
{  
  gyro_angle_x += gyro_x * 0.005f;
  gyro_angle_y += gyro_y * 0.005f;

}

/**
  * @fn     proc_angle_x
  * @bried  processing of data
  * 
  * @param  accel_x
  */
void proc_angle()
{  
  
 /* compliment filter */
 
  c_angle_x = 0.92f * (c_pre_angle_x + gyro_x * (100.0f / 10000.0f)) + 0.08f * accel_angle_x;
  c_angle_y = 0.97f * (c_pre_angle_y + gyro_y * 0.005f) + 0.03f * accel_angle_y;
  //angle_z = gyro_z * ( 100.0f / 10000.0f );
  c_pre_angle_x = c_angle_x;
  c_pre_angle_y = c_angle_y;


  /* kalman filter */
  angle_x = filter_kalman(accel_angle_x, gyro_angle_x, TIM1);
  //angle_x = filter_ema(angle_x,pre_angle_x);
  angle_y = filter_kalman(accel_angle_y, gyro_angle_y, TIM7);
  //angle_y = filter_ema(angle_y,pre_angle_y);
}

/**
  * @fn     get_angle_x
  * @bried  
  * 
  * @param  None
  */
float get_angle_x()
{
  return angle_x;
}

/**
  * @fn     get_angle_y
  * @bried  
  * 
  * @param  None
  */
float get_angle_y()
{
  return angle_y;
}

/**
  * @fn     get_angle_y
  * @bried  
  * 
  * @param  None
  */
float get_angle_z()
{
  return angle_z;
}

/**
  * @fn     generate_sine_pwm
  * @bried  
  * 
  * @param  None
  */
void generate_sine_pwm(int dir_angle, TIM_TypeDef* TIMx)
{
  if(TIMx == TIM4){
    if(dir_angle == 1){
     phaseu_x++;
     phasev_x++;
     phasew_x++;
    }
    else if(dir_angle == -1)
    {
     phaseu_x--;
     phasev_x--;
     phasew_x--;
    }
    if(phaseu_x > SINE_ARRAY_MAX)phaseu_x = 0;
    if(phasev_x > SINE_ARRAY_MAX)phasev_x = 0;
    if(phasew_x > SINE_ARRAY_MAX)phasew_x = 0;
    if(phaseu_x < 0)phaseu_x = SINE_ARRAY_MAX;
    if(phasev_x < 0)phasev_x = SINE_ARRAY_MAX;
    if(phasew_x < 0)phasew_x = SINE_ARRAY_MAX;
    duty_Phaseu_x = (float32_t)CARRIER_TIM_PERIOD*sine_Array[phaseu_x];
    duty_Phasev_x = (float32_t)CARRIER_TIM_PERIOD*sine_Array[phasev_x];
    duty_Phasew_x = (float32_t)CARRIER_TIM_PERIOD*sine_Array[phasew_x];
    TIM_SetCompare2(TIMx,(uint32_t)duty_Phaseu_x);
    TIM_SetCompare3(TIMx,(uint32_t)duty_Phasev_x);
    TIM_SetCompare4(TIMx,(uint32_t)duty_Phasew_x);
  }
  else if (TIMx == TIM5)
  {
    if(dir_angle == 1){
     phaseu_y++;
     phasev_y++;
     phasew_y++;
    }
    else if(dir_angle == -1)
    {
     phaseu_y--;
     phasev_y--;
     phasew_y--;
    }
    if(phaseu_y > SINE_ARRAY_MAX)phaseu_y = 0;
    if(phasev_y > SINE_ARRAY_MAX)phasev_y = 0;
    if(phasew_y > SINE_ARRAY_MAX)phasew_y = 0;
    if(phaseu_y < 0)phaseu_y = SINE_ARRAY_MAX;
    if(phasev_y < 0)phasev_y = SINE_ARRAY_MAX;
    if(phasew_y < 0)phasew_y = SINE_ARRAY_MAX;
    duty_Phaseu_y = (float32_t)CARRIER_TIM_PERIOD*sine_Array[phaseu_y];
    duty_Phasev_y = (float32_t)CARRIER_TIM_PERIOD*sine_Array[phasev_y];
    duty_Phasew_y = (float32_t)CARRIER_TIM_PERIOD*sine_Array[phasew_y];
    TIM_SetCompare2(TIMx,(uint32_t)duty_Phaseu_y);
    TIM_SetCompare3(TIMx,(uint32_t)duty_Phasev_y);
    TIM_SetCompare4(TIMx,(uint32_t)duty_Phasew_y);
  }
}

/**********************************END OF FILE**********************************/
