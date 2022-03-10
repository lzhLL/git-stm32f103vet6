#ifndef __BSP_I2C_GPIO_H__
#define __BSP_I2C_GPIO_H__

#include "stm32f10x.h"

/* i2c������APB1�����ϣ���I2C1��I2C2���������õ���I2C1 */
/* SCL��PB6, SDA��PB7 ��   ������stm32			�ӻ���EEPROM*/

#define EEPROM_I2C_WR	0		/* ���� д ���ݵ��ӻ�    ����bit */
#define EEPROM_I2C_RD	1		/* ���� �� �ӻ��ж�����  ����bit */

#define EEPROM_I2C_GPIO_PORT			GPIOB			/* GPIO�˿� */
#define EEPROM_I2C_GPIO_PORT_RCC	RCC_APB2Periph_GPIOB			/* GPIO�˿�ʱ�� */
#define EEPROM_I2C_SCL_PIN				GPIO_Pin_6			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define EEPROM_I2C_SDA_PIN				GPIO_Pin_7			/* ���ӵ�SDA�����ߵ�GPIO */


/* ֱ�Ӳ����Ĵ���ʵ��IO��д */
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


