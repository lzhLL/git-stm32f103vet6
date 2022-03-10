#include "bsp_spi_flash.h"

static __IO uint32_t SPITimeout = SPIT_LONG_TIMEOUT;

/**
  * @brief  I2C eeprom 配置，工作参数配置
  * @param  None
  * @retval None
  */
void SPI_FLASH_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStruct;

	// 打开外设spi的时钟
	FLASH_SPI_APBxClock_FUN(FLASH_SPI_CLK, ENABLE);

	// 打开SPI_GPIO的时钟
	FLASH_SPI_GPIO_APBxClock_FUN(FLASH_SPI_GPIO_CLK, ENABLE);

	// 将I2C_SCK的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_SCK_PORT, &GPIO_InitStructure);

		// 将I2C_MOSI的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_MOSI_PORT, &GPIO_InitStructure);
	
	// 将I2C_MISO的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_MISO_PORT, &GPIO_InitStructure);

	//初始化CS引脚，使用软件控制，所以直接设置成推挽输出
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_CS_PORT, &GPIO_InitStructure);
	FLASH_SPI_CS_HIGH;
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2 ;
	//SPI使用模式3
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge ;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High ;
	SPI_InitStruct.SPI_CRCPolynomial = 0;//不使用CRC校验
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b ;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB ;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft ;
	
	// 完成SPI的初始化配置
	SPI_Init(FLASH_SPIx, &SPI_InitStruct);
	
	// 使能SPI
	SPI_Cmd(FLASH_SPIx, ENABLE);
}

//发送并接收一个字节
uint8_t SPI_FLASH_SendByte(uint8_t data) {
	SPITimeout = SPIT_FLAG_TIMEOUT;
	
	//检查并等待至TX缓冲区为空
	while( SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET) {
		SPITimeout--;
		if(SPITimeout == 0) {
			return SPI_TIMEOUT_UserCallback(0);
		}
	}
	
	//发送数据
	SPI_I2S_SendData(FLASH_SPIx, data);
	
	SPITimeout = SPIT_FLAG_TIMEOUT;
	//检查并等待至RX缓冲区非空
	while( SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET) {
		SPITimeout--;
		if(SPITimeout == 0) {
			return SPI_TIMEOUT_UserCallback(1);
		}
	}
	
	return (SPI_I2S_ReceiveData(FLASH_SPIx));
		
}

uint8_t SPI_FLASH_Read_Byte(void) {
	return (SPI_FLASH_SendByte(DUMMY) );
}

//读取ID号
uint32_t SPI_Read_ID(void) {
	uint32_t flash_id = 0;
	//片选拉低，启动时序
	FLASH_SPI_CS_LOW;
	//发送9f命令，获取ID
	SPI_FLASH_SendByte(READ_JEDEC_ID);
	
	flash_id = SPI_FLASH_SendByte(DUMMY);
	
	flash_id = flash_id << 8;
	
	flash_id |= SPI_FLASH_SendByte(DUMMY);
	
	flash_id = flash_id << 8;
	
	flash_id |= SPI_FLASH_SendByte(DUMMY);
	
	FLASH_SPI_CS_HIGH;
	
	return flash_id;
}

//擦除FLASH指定的扇区
void SPI_Erase_Ssector(uint32_t addr) {
	SPI_Write_Enable();
	//片选拉低，启动时序
	FLASH_SPI_CS_LOW;
	//发送0X20擦除命令
	SPI_FLASH_SendByte(SECTOR_ERASE);	
	
	//发送擦除地址
	SPI_FLASH_SendByte((addr >> 16) & 0xf);
	SPI_FLASH_SendByte((addr >> 8) & 0xf);
	SPI_FLASH_SendByte(addr);
	
	FLASH_SPI_CS_HIGH;
	
	//等待FLASH内部时序操作完成
	SPI_WaitForWriteEnd();
	
	return;
} 

//读取flash的内容
void SPI_Read_Data(uint32_t addr, uint8_t* read_buff, uint32_t numByteToRead) {
	//片选拉低，启动时序
	FLASH_SPI_CS_LOW;
	//发送0x05读取命令
	SPI_FLASH_SendByte(READ_DATA);	
	
	//发送要读取的地址
	SPI_FLASH_SendByte((addr >> 16) & 0xf);
	SPI_FLASH_SendByte((addr >> 8) & 0xf);
	SPI_FLASH_SendByte(addr);
	
	while(numByteToRead) {
		*read_buff = SPI_FLASH_SendByte(DUMMY);
		read_buff++;
		numByteToRead--;
	}
	
	FLASH_SPI_CS_HIGH;
	
	
	return;

}

//等待FLASH内部时序操作完成
void SPI_WaitForWriteEnd(void) {
	uint8_t status_reg = 0;
	//片选拉低，启动时序
	FLASH_SPI_CS_LOW;
	
	//发送读取状态寄存器命令
	SPI_FLASH_SendByte(READ_STATUS);	
	
	do {
		status_reg = SPI_FLASH_SendByte(DUMMY);	
	} 
	while((status_reg & 0x01) == 1);
	
	FLASH_SPI_CS_HIGH;
}

//写入使能
void SPI_Write_Enable(void) {
	//片选拉低，启动时序
	FLASH_SPI_CS_LOW;
	//发送写使能命令
	SPI_FLASH_SendByte(WRITE_ENABLE);	
	FLASH_SPI_CS_HIGH;

}

//向FLASH写入数据
void SPI_Write_Data(uint32_t addr, uint8_t* write_buff, uint32_t numByteToWrite) {
	SPI_Write_Enable();
	//片选拉低，启动时序
	FLASH_SPI_CS_LOW;
	//发送0x02写入命令
	SPI_FLASH_SendByte(WRITE_DATA);	
	
	//发送要写入的地址
	SPI_FLASH_SendByte((addr >> 16) & 0xf);
	SPI_FLASH_SendByte((addr >> 8) & 0xf);
	SPI_FLASH_SendByte(addr);
	
	while(numByteToWrite) {
		SPI_FLASH_SendByte(*write_buff);
		write_buff++;
		numByteToWrite--;
	}
	
	FLASH_SPI_CS_HIGH;
	
	//等待FLASH内部时序操作完成
	SPI_WaitForWriteEnd();
	
	return;
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示IIC读取失败.
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FLASH_ERROR("I2C 等待超时!errorCode = %d",errorCode);
  
  return 0;
}
