/**
  ******************************************************************************
  * @author  lzh
  * @version V3.5.0
	* @file 	 bsp_spi_flash.h
  * @date    31-December-2021
  * @brief   SPI_FLASH
  ******************************************************************************
  */
	
#ifndef __BSP_SPI_FLASH_H__
#define __BSP_SPI_FLASH_H__

#include "stm32f10x.h"
#include "bsp_usart.h"


//SPI
#define  FLASH_SPIx               	  SPI1
#define  FLASH_SPI_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define  FLASH_SPI_CLK                RCC_APB2Periph_SPI1


#define  USER_ZN												1
// SPI_GPIO 引脚宏定义
#if (1 == USER_ZN) 
	#define FLASH_SPI_GPIO_CLK					(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC)
	#define FLASH_SPI_GPIO_CS_PORT			GPIOC
	#define FLASH_SPI_GPIO_CS_PIN        GPIO_Pin_0
#else
	#define FLASH_SPI_GPIO_CLK					(RCC_APB2Periph_GPIOA)
	#define FLASH_SPI_GPIO_CS_PORT			GPIOA
	#define FLASH_SPI_GPIO_CS_PIN        GPIO_Pin_4
#endif

#define  FLASH_SPI_GPIO_APBxClock_FUN  RCC_APB2PeriphClockCmd
    
#define  FLASH_SPI_GPIO_SCK_PORT       GPIOA 
#define  FLASH_SPI_GPIO_SCK_PIN        GPIO_Pin_5

#define  FLASH_SPI_GPIO_MISO_PORT       GPIOA
#define  FLASH_SPI_GPIO_MISO_PIN        GPIO_Pin_6

#define  FLASH_SPI_GPIO_MOSI_PORT       GPIOA
#define  FLASH_SPI_GPIO_MOSI_PIN        GPIO_Pin_7

/* 等待超时时间 */
#define  SPIT_FLAG_TIMEOUT              ((uint32_t)0x1000)
#define  SPIT_LONG_TIMEOUT              ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))


/*信息输出*/
#define FLASH_DEBUG_ON         0

#define FLASH_INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)          do{\
                                          if(FLASH_DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

//CS引脚配置																					
#define FLASH_SPI_CS_HIGH								GPIO_SetBits(FLASH_SPI_GPIO_CS_PORT, FLASH_SPI_GPIO_CS_PIN)																
#define FLASH_SPI_CS_LOW							  GPIO_ResetBits(FLASH_SPI_GPIO_CS_PORT, FLASH_SPI_GPIO_CS_PIN)

#define DUMMY														0x00																			
#define READ_JEDEC_ID										0x9F		
#define SECTOR_ERASE									  0x20 
#define READ_STATUS											0x05
#define READ_DATA												0x03
#define WRITE_ENABLE										0x06
#define WRITE_DATA											0x02
																					
void SPI_FLASH_Config(void);
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);				
uint8_t SPI_FLASH_Read_Byte(void);	
uint32_t SPI_Read_ID(void);	
void SPI_Erase_Ssector(uint32_t addr);																					
void SPI_WaitForWriteEnd(void);		
void SPI_Read_Data(uint32_t addr, uint8_t* read_buff, uint32_t numByteToRead);
void SPI_Write_Enable(void);
void SPI_Write_Data(uint32_t addr, uint8_t* write_buff, uint32_t numByteToWrite);


#endif
