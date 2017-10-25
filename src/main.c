#include"gimbal_stm32.h"

int main()
{
  setup_serial();
  data_init();
  tim_init();
  delay(2000000);
  setup_i2c_for_mpu6050();
  delay(2000000);
  setup_mpu6050();

  /*
  res = read_mpu6050_reg(MPU6050_REG_WHOAMI);
  serial_output_hexbyte(USART3, res);
  res = read_mpu6050_reg(MPU6050_REG_PWR_MGMT_1);
  serial_output_hexbyte(USART3, res);
  */

  while (1)
  {
    data_processing(tim2_get_time());
  }

  return 0;
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line){
  while(1);
}
#endif
