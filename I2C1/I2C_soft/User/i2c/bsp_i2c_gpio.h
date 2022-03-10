#ifndef __BSP_I2C_GPIO_H__
#define __BSP_I2C_GPIO_H__

#include "stm32f10x.h"

/* i2c挂载在APB1总线上，有I2C1和I2C2。本程序用的是I2C1 */
/* SCL在PB6, SDA在PB7 ，   主机：stm32			从机：EEPROM*/

#define EEPROM_I2C_WR	0		/* 主机 写 数据到从机    控制bit */
#define EEPROM_I2C_RD	1		/* 主机 从 从机中读数据  控制bit */

#define EEPROM_I2C_GPIO_PORT			GPIOB			/* GPIO端口 */
#define EEPROM_I2C_GPIO_PORT_RCC	RCC_APB2Periph_GPIOB			/* GPIO端口时钟 */
#define EEPROM_I2C_SCL_PIN				GPIO_Pin_6			/* 连接到SCL时钟线的GPIO */
#define EEPROM_I2C_SDA_PIN				GPIO_Pin_7			/* 连接到SDA数据线的GPIO */


/* 直接操作寄存器实现IO读写 */
#define EEPROM_I2C_SCL_1()				EEPROM_I2C_GPIO_PORT->BSRR |= EEPROM_I2C_SCL_PIN	/* SCL = 1 */
#define EEPROM_I2C_SCL_0()				EEPROM_I2C_GPIO_PORT->BRR	 |= EEPROM_I2C_SCL_PIN  /* SCL = 0 */

#define EEPROM_I2C_SDA_1()				EEPROM_I2C_GPIO_PORT->BSRR |= EEPROM_I2C_SDA_PIN	/* SDA = 1 */
#define EEPROM_I2C_SDA_0()				EEPROM_I2C_GPIO_PORT->BRR  |= EEPROM_I2C_SDA_PIN	/* SDA = 0 */

#define EEPROM_I2C_SDA_READ()			((EEPROM_I2C_GPIO_PORT->IDR & EEPROM_I2C_SDA_PIN) != 0)


void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);

#endif /* __BSP_I2C_GPIO_H__ */


