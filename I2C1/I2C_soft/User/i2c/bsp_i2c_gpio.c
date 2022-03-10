#include "bsp_i2c_gpio.h"

static void i2c_CfgGpio(void);

static void i2c_Delay(void)
{
	uint8_t i;

	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
	for (i = 0; i < 10; i++);
}



/* I2C起始信号 */
void i2c_Start(void) {
	EEPROM_I2C_SDA_1();		//一开始SDA是高电平
	EEPROM_I2C_SCL_1();		//一开始SCL是高电平
	i2c_Delay();
	EEPROM_I2C_SDA_0();		//将SDA数据线拉低
	i2c_Delay();
	//EEPROM_I2C_SCL_0();		//将SCL时钟线拉低
	//i2c_Delay();

	return ;
	
}

/* I2C停止信号 */
void i2c_Stop(void) {
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	EEPROM_I2C_SDA_0();		//将SDA数据线拉低
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_1();		//将SDA数据线拉高

	return ;
}


/* 功能说明: CPU向I2C总线设备发送8bit数据 */
void i2c_SendByte(uint8_t _ucByte) {
	uint8_t i;
	EEPROM_I2C_SCL_0();	//允许数据变化
	i2c_Delay();
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{	
		if (_ucByte & 0x80) {		//如果最高位是1，就发送高电平，否则就发送低电平
			EEPROM_I2C_SDA_1();
		} else {
			EEPROM_I2C_SDA_0();
		}
		_ucByte <<= 1;	/* 左移一个bit */
		
		EEPROM_I2C_SCL_1();		//SCL高电平，数据有效
		i2c_Delay();	
		
		EEPROM_I2C_SCL_0();		//允许数据变化
		i2c_Delay();	
		
	}
	
	EEPROM_I2C_SDA_1(); // 释放总线	(方便应答信号)
	i2c_Delay();
	
	return;
}



/* 功能说明: CPU从I2C总线设备读取8bit数据 */
uint8_t i2c_ReadByte(void) {
	//数据是串行的
	uint8_t i;
	uint8_t value;
	
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	
	/* SCL不断拉高拉低，拉高读取数据，拉低允许数据变化 */
	for(i = 0; i < 8; i++) {
		value <<= 1;
		EEPROM_I2C_SCL_1();//SCL高电平，数据有效
		i2c_Delay();
		if (EEPROM_I2C_SDA_READ()) {	//如果读到的bit为1，那么就置1
			value++;
		}
		EEPROM_I2C_SCL_0();	//允许数据变化
		i2c_Delay();
	}
	
	return value;
}

/* 功能说明: CPU产生一个时钟，并读取器件的ACK应答信号 */
uint8_t i2c_WaitAck(void) {
	uint8_t reply;
	
	EEPROM_I2C_SDA_1();	/* CPU释放SDA总线，由从机接管数据线 */
	i2c_Delay();
	
	EEPROM_I2C_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
	
	//读取SDA数据线的第9bit
	if( EEPROM_I2C_SDA_READ() ) {
		reply = 1;
	} else {
		reply = 0;
	}
	
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	
	return reply;
	
}


/* 功能说明: CPU产生一个ACK信号 */
void i2c_Ack(void) {
	EEPROM_I2C_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	EEPROM_I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	EEPROM_I2C_SDA_1();	/* CPU释放SDA总线 */
}

/* 功能说明: CPU产生1个NACK信号 */
void i2c_NAck(void) {
	EEPROM_I2C_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	EEPROM_I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();	
}

/* 功能说明: 配置I2C总线的GPIO，采用模拟IO的方式实现 */
static void i2c_CfgGpio(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(EEPROM_I2C_GPIO_PORT_RCC, ENABLE);	/* 打开GPIOB时钟 */
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* 开漏输出 */
	GPIO_Init(EEPROM_I2C_GPIO_PORT, &GPIO_InitStructure);	

	/* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
	i2c_Stop();
	
	return ;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_CheckDevice
*	功能说明: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
*	形    参：_Address：设备的I2C总线地址
*	返 回 值: 返回值 0 表示正确， 返回1表示未探测到
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address) {
	uint8_t ucAck;
	
	i2c_CfgGpio();		/* 配置GPIO */
	
	i2c_Start();		/* 发送启动信号 */
	
	/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
	i2c_SendByte(_Address | EEPROM_I2C_WR);
	ucAck = i2c_WaitAck();	/* 检测设备的ACK应答 */
	//i2c_Stop();			/* 发送停止信号 */
	
	return ucAck;

}
