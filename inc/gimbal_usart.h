/**
  ******************************************************************************
  * @file      gimbal_usart.h  
  * @brief     STM32F4 usart setting file.
  * @author    Junichi
  * @date      22-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef __GIMBAL_USART_H
#define __GIMBAL_USART_H

/* Includes -------------------------------------------------------------------*/
#include<math.h>
#include<string.h>
#include "gimbal_stm32.h"

/* Define macro ---------------------------------------------------------------*/
#define BAUDLATE (115200*3)

/* Define struct --------------------------------------------------------------*/

/* Functions ------------------------------------------------------------------*/
void setup_serial(void);
void serial_putchar(USART_TypeDef* USARTx, uint32_t c);
void serial_puts(USART_TypeDef *usart, const char *s);
void serial_output_hexdig(USART_TypeDef* USARTx, uint32_t dig);
void serial_output_hexbyte(USART_TypeDef* USARTx, uint8_t byte);
void println_uint32(USART_TypeDef* usart, uint32_t val);
void println_int32(USART_TypeDef* usart, int32_t val);
void float_to_str(char *buf, float f, uint32_t dig_before, uint32_t dig_after);
void println_float(USART_TypeDef* usart, float f, uint32_t dig_before, uint32_t dig_after);

#endif /* __GIMBAL_USART_H */
/**********************************END OF FILE**********************************/
