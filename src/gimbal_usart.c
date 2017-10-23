 /**
  ******************************************************************************
  * @file      gimbal_usart.c 
  * @brief     STM32F4 usart function file.
  * @author    Junichi
  * @date      23-October-2017
  * @version   1.0
  ******************************************************************************
  */ 

/* Includes -------------------------------------------------------------------*/
#include "gimbal_usart.h"

/* Functions ------------------------------------------------------------------*/

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
  * @fn     setup_serial
  * @brief  Setting  USART3 
  *
  *@param   
  */
void setup_serial(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* enable peripheral clock for USART3 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* GPIOD Configuration:  USART3 TX on PD8 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect USART3 pins to AF */
  // TX = PD8
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);

  USART_InitStructure.USART_BaudRate = BAUDLATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);

  USART_Cmd(USART3, ENABLE); // enable USART3
}

/**
  * @brief     Send data functiions
  *
@verbatim   
 ===============================================================================
                        ##### Send data functions #####
 ===============================================================================  
@endverbatim
  *
  */

/**
  * @fn     serial_putchar
  * @brief  Send data use USART_SendData()
  *
  *@param   
  */
void serial_putchar(USART_TypeDef* USARTx, uint32_t c)
{
  while(!(USARTx->SR & USART_FLAG_TC));
  USART_SendData(USARTx, c);
}


/**
  * @fn     serial_puts
  * @brief  Send string with *s
  *
  *@param   *s Enter the Strings
  */
void serial_puts(USART_TypeDef *usart, const char *s)
{
  while (*s)
    serial_putchar(usart, (uint8_t)*s++);
}


/**
  * @fn     serial_output_hexdig
  * @brief  Converting DEC to HEX
  *
  *@param   dig
  */
void serial_output_hexdig(USART_TypeDef* USARTx, uint32_t dig)
{
  //if(dig>=10){c=('A'-10+dig)}else{c=('0'+dig)}
  serial_putchar(USARTx, (dig >= 10 ? 'A' - 10 + dig : '0' + dig));
}


/**
  * @fn     serial_output_hexbyte
  * @brief  Converting BIN to HEX
  *
  *@param   byte
  */
void serial_output_hexbyte(USART_TypeDef* USARTx, uint8_t byte)
{
  serial_output_hexdig(USARTx, byte >> 4);
  serial_output_hexdig(USARTx, byte & 0xf);
}


/**
  * @fn     println_uint32
  * @brief  Send data(uint32_t) as strings
  *
  *@param   val Enter the int data type
  */
void println_uint32(USART_TypeDef* usart, uint32_t val)
{
  char buf[13];
  char *p = buf;
  uint32_t l, d;

  l = 1000000000UL;
  while (l > val && l > 1)
    l /= 10;

  do
  {
    d = val / l;
    *p++ = '0' + d;
    val -= d*l;
    l /= 10;
  } while (l > 0);

  *p++ = '\r';
  *p++ = '\n';
  *p = '\0';
  serial_puts(usart, buf);
}


/**
  * @fn     println_int32
  * @brief  Send data
  *
  *@param   val Enter the int data type
  */
void println_int32(USART_TypeDef* usart, int32_t val)
{
  if (val < 0)
  {
    serial_putchar(usart, '-');
    println_uint32(usart, (uint32_t)0 - (uint32_t)val);
  }
  else
    println_uint32(usart, val);
}


/**
  * @fn     float_to_str
  * @brief  Converting float to string
  *
  *@param   buf         Buffer to store the strings
  *@param   f           Enter the Float data type
  *@param   dig_before  integer part
  *@param   dig_after   fractional part
  */
void float_to_str(char *buf, float f, uint32_t dig_before, uint32_t dig_after)
{
  float a;
  uint32_t d;
  uint8_t leading_zero;

  if (f == 0.0f)
  {
    buf[0] = '0';
    buf[1] = '\0';
    return;
  }
  if (f < 0)
  {
    *buf++ = '-';
    f = -f;
  }
  a =  powf(10.0f, (float)dig_before);
  if (f >= a)
  {
    buf[0] = '#';
    buf[1] = '\0';
    return;
  }
  leading_zero = 1;
  while (dig_before)
  {
    a /= 10.0f;
    d = (uint32_t)(f / a);
    if (leading_zero && d == 0 && a >= 10.0f)
      *buf++ = ' ';
    else
    {
      leading_zero = 0;
      *buf++ = '0' + d;
      f -= d*a;
    }
    --dig_before;
  }
  if (!dig_after)
  {
    *buf++ = '\0';
    return;
  }
  *buf++ = '.';
  do
  {
    f *= 10.0f;
    d = (uint32_t)f;
    *buf++ = '0' + d;
    f -= (float)d;
    --dig_after;
  } while (dig_after);
  *buf++ = '\0';
}


/**
  * @fn     println_float
  * @brief  
  *
  *@param   
  */
void println_float(USART_TypeDef* usart, float f,uint32_t dig_before, uint32_t dig_after)
{
  char buf[21];
  char *p = buf;

  float_to_str(p, f, dig_before, dig_after);
  while (*p)
    ++p;
  *p++ = '\r';
  *p++ = '\n';
  *p = '\0';
  serial_puts(usart, buf);
}


#endif /* __GIMBAL_USART_H */
/**********************************END OF FILE**********************************/
