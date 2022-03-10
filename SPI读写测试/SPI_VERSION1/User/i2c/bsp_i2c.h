/**
  ******************************************************************************
  * @author  lzh
  * @version V3.5.0
	* @file 	 bsp_i2c.h
  * @date    28-December-2021
  * @brief   I2C_eeprom 
  ******************************************************************************
  */
	
#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__

#include "stm32f10x.h"
#include "bsp_usart.h"
/* AT24C01/02每页有8个字节 */
#define  I2C_PageSize									8

/**
* IIC EEOROM的引脚定义
*
*/

#define  TM32_I2C_OWN_ADDR 						 0x5f

//eeprom设备地址
#define  EEPROM_ADDR									 0xA0

//IIC
#define  EEPROM_I2C                 	 I2C1
#define  EEPROM_I2C_CLK                RCC_APB1Periph_I2C1
#define  EEPROM_I2C_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  EEPROM_I2C_BAUDRATE           400000 

// IIC  GPIO 引脚宏定义
#define  EEPROM_I2C_SCL_GPIO_CLK        (RCC_APB2Periph_GPIOB)
#define  EEPROM_I2C_SDA_GPIO_CLK        (RCC_APB2Periph_GPIOB)
#define  EEPROM_I2C_GPIO_APBxClkCmd    	RCC_APB2PeriphClockCmd
    
#define  EEPROM_I2C_SCL_GPIO_PORT       GPIOB   
#define  EEPROM_I2C_SCL_GPIO_PIN        GPIO_Pin_6
#define  EEPROM_I2C_SDA_GPIO_PORT       GPIOB
#define  EEPROM_I2C_SDA_GPIO_PIN        GPIO_Pin_7


/* 等待超时时间 */
#define  I2CT_FLAG_TIMEOUT              ((uint32_t)0x1000)
#define  I2CT_LONG_TIMEOUT              ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/*信息输出*/
#define EEPROM_DEBUG_ON         0

#define EEPROM_INFO(fmt,arg...)           printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)          printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)          do{\
                                          if(EEPROM_DEBUG_ON)\
                                          printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

void I2C_EE_Config(void);
uint32_t EEPROM_Byte_Write(uint8_t addr, uint8_t data);
uint32_t EEPROM_Read(uint8_t addr, uint8_t* data, uint16_t num);
uint32_t EEPROM_Page_Write(uint8_t addr, uint8_t* data, uint8_t numByteToWrite);
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void EEPROM_WaitForWriteEnd(void);
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);
#endif

