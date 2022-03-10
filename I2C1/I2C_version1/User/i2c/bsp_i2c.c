#include "bsp_i2c.h"

/**
  * @brief  I2C eeprom 配置，工作参数配置
  * @param  None
  * @retval None
  */
	
void I2C_EE_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStruct;

	// 打开串口I2C GPIOB的时钟
	EEPROM_I2C_GPIO_APBxClkCmd(EEPROM_I2C_SCL_GPIO_CLK | EEPROM_I2C_SDA_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	EEPROM_I2C_APBxClkCmd(EEPROM_I2C_CLK, ENABLE);

	// 将I2C_SCL的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  // 将I2C_SDA的GPIO配置为 Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置I2C的工作参数
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;//使能应答
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7位地址
	I2C_InitStruct.I2C_ClockSpeed = EEPROM_I2C_BAUDRATE;//400khz
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;//2:1
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = TM32_I2C_OWN_ADDR;
	
	// 完成I2c的初始化配置
	I2C_Init(EEPROM_I2C, &I2C_InitStruct);

	// 使能串口
	I2C_Cmd(EEPROM_I2C, ENABLE);
}



/* 向EEPROM写入一个字节 */
void EEPROM_Byte_Write(uint8_t addr, uint8_t data) {
	//起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//检测EV5事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//发送eeprom设备地址 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	//检测EV6、EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	//发送要操作的存储单元的地址
	I2C_SendData(EEPROM_I2C, addr);
	
	//检测EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	//发送要存储的数据
	I2C_SendData(EEPROM_I2C, data);

	//检测EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	//检测EV8_2事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	//数据传输完成
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	
}

/* 向EEPROM写入多个字节（页写入），每次写入不能超过8个字节 */
void EEPROM_Page_Write(uint8_t addr, uint8_t* data, uint8_t numByteToWrite) {
	//起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//检测EV5事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//发送eeprom设备地址 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	//检测EV6、EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	//发送要操作的存储单元的地址
	I2C_SendData(EEPROM_I2C, addr);
	
	//检测EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	
	while(numByteToWrite) {
		//发送要存储的数据
		I2C_SendData(EEPROM_I2C, *data);
		data++;
		numByteToWrite--;
		
		//检测EV8事件
		while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	}

	
	//检测EV8_2事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	//数据传输完成
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	
}

/* 该函数的功能是可以不用对齐8字节也能写入EEPROM */
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
	
	//Addr是用来检测是否能被8整除
	Addr = WriteAddr % I2C_PageSize;
	
	count = I2C_PageSize - Addr;
	
	//NumOfPage是记录有多少页
	NumOfPage = NumByteToWrite / I2C_PageSize;
	
	//NumOfSingle记录最后一页需要写入多少个字节
	NumOfSingle = NumByteToWrite % I2C_PageSize;
	
	//如果字节总数对齐字节8
	if( 0 == Addr ) {
		//如果一页未满
		if( 0 == NumOfPage ) {
			EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
			EEPROM_WaitForWriteEnd();//等待写入完成
		} else {	//如果不止一页，而且对齐字节8
			while(NumOfPage--) {
				EEPROM_Page_Write(WriteAddr, pBuffer, I2C_PageSize);
				EEPROM_WaitForWriteEnd();//等待写入完成
				WriteAddr += I2C_PageSize;
				pBuffer += I2C_PageSize;		
			}
			if(0 == NumOfPage && NumOfSingle != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
				EEPROM_WaitForWriteEnd();//等待写入完成
			}
		}
	} else { //如果字节总数不对齐字节8
		//如果一页未满
		if( 0 == NumOfPage ) {
			EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
			EEPROM_WaitForWriteEnd();//等待写入完成
		} else { ////如果不止一页，而且对齐字节8
			NumByteToWrite = NumByteToWrite - count;
			NumOfPage =  NumByteToWrite / I2C_PageSize;
			NumOfSingle = NumByteToWrite % I2C_PageSize;	
			
			if(count != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, count);
				EEPROM_WaitForWriteEnd();//等待写入完成
				WriteAddr = WriteAddr + count;
				pBuffer = pBuffer + count;
			}
			
			while(NumOfPage != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, I2C_PageSize);
				EEPROM_WaitForWriteEnd();//等待写入完成
				--NumOfPage;
				WriteAddr = WriteAddr + I2C_PageSize;
				pBuffer = pBuffer + I2C_PageSize;
			}
			
			if(NumOfSingle != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
				EEPROM_WaitForWriteEnd();//等待写入完成
				
			}
		}
	} 
}

/* 从EEPROM读取数据 */
void EEPROM_Read(uint8_t addr, uint8_t* data, uint8_t num) {
	//起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//检测EV5事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//发送eeprom设备地址 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	//检测EV6、EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	//发送要操作的存储单元的地址
	I2C_SendData(EEPROM_I2C, addr);
	
	//检测EV8事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	
	
	//第二次起始信号
	//起始信号
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//检测EV5事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//发送eeprom设备地址 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Receiver);
	
	//检测EV6事件
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	
	
	while(num) {
		//如果为最后一个字节
		if(1 == num) {
			I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
			//检测EV7事件
			//while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);		
			*data = I2C_ReceiveData(EEPROM_I2C);		
		}		
		
		//检测EV7事件
		while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
		
		//接收数据
		*data = I2C_ReceiveData(EEPROM_I2C);

		//检测EV7事件 add by lzh
		//while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);

		
		data++;
		
		num--;
	}
	
	
	//数据传输完成
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	//重新配置ACK使能，以便下次通讯
	I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
}


/* 等待EEPROM内部时序完成 */
void EEPROM_WaitForWriteEnd(void) {
	do 
	{
		//产生起始信号
		I2C_GenerateSTART(EEPROM_I2C,ENABLE);
		while( I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_SB) == RESET );
		
		//发送设备地址
		I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Transmitter);
	}
	while( I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_ADDR) == RESET );	

	//EEPROM内部时序完成传输完成
	I2C_GenerateSTOP(EEPROM_I2C,ENABLE);	

}


