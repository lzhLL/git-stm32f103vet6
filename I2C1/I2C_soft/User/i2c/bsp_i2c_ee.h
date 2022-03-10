#ifndef __BSP_I2C_EE_H__
#define __BSP_I2C_EE_H__

#include "stm32f10x.h"

#define EEPROM_DEV_ADDR			0xA0		/* 24xx02的设备地址:10100000 */
#define EEPROM_PAGE_SIZE		  8			  /* 24xx02的页面大小 */
#define EEPROM_SIZE				  256			  /* 24xx02总容量 */

uint8_t ee_CheckOk(void);
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
void ee_Erase(void);
uint8_t ee_Test(void);


#endif /* __BSP_I2C_EE_H__ */
