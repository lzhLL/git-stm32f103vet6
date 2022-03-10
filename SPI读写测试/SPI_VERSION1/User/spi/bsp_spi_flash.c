#include "bsp_spi_flash.h"

static __IO uint32_t SPITimeout = SPIT_LONG_TIMEOUT;

/**
  * @brief  I2C eeprom ���ã�������������
  * @param  None
  * @retval None
  */
void SPI_FLASH_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStruct;

	// ������spi��ʱ��
	FLASH_SPI_APBxClock_FUN(FLASH_SPI_CLK, ENABLE);

	// ��SPI_GPIO��ʱ��
	FLASH_SPI_GPIO_APBxClock_FUN(FLASH_SPI_GPIO_CLK, ENABLE);

	// ��I2C_SCK��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_SCK_PORT, &GPIO_InitStructure);

		// ��I2C_MOSI��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_MOSI_PORT, &GPIO_InitStructure);
	
	// ��I2C_MISO��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_MISO_PORT, &GPIO_InitStructure);

	//��ʼ��CS���ţ�ʹ��������ƣ�����ֱ�����ó��������
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_GPIO_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_GPIO_CS_PORT, &GPIO_InitStructure);
	FLASH_SPI_CS_HIGH;
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2 ;
	//SPIʹ��ģʽ3
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge ;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High ;
	SPI_InitStruct.SPI_CRCPolynomial = 0;//��ʹ��CRCУ��
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b ;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB ;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft ;
	
	// ���SPI�ĳ�ʼ������
	SPI_Init(FLASH_SPIx, &SPI_InitStruct);
	
	// ʹ��SPI
	SPI_Cmd(FLASH_SPIx, ENABLE);
}

//���Ͳ�����һ���ֽ�
uint8_t SPI_FLASH_SendByte(uint8_t data) {
	SPITimeout = SPIT_FLAG_TIMEOUT;
	
	//��鲢�ȴ���TX������Ϊ��
	while( SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET) {
		SPITimeout--;
		if(SPITimeout == 0) {
			return SPI_TIMEOUT_UserCallback(0);
		}
	}
	
	//��������
	SPI_I2S_SendData(FLASH_SPIx, data);
	
	SPITimeout = SPIT_FLAG_TIMEOUT;
	//��鲢�ȴ���RX�������ǿ�
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

//��ȡID��
uint32_t SPI_Read_ID(void) {
	uint32_t flash_id = 0;
	//Ƭѡ���ͣ�����ʱ��
	FLASH_SPI_CS_LOW;
	//����9f�����ȡID
	SPI_FLASH_SendByte(READ_JEDEC_ID);
	
	flash_id = SPI_FLASH_SendByte(DUMMY);
	
	flash_id = flash_id << 8;
	
	flash_id |= SPI_FLASH_SendByte(DUMMY);
	
	flash_id = flash_id << 8;
	
	flash_id |= SPI_FLASH_SendByte(DUMMY);
	
	FLASH_SPI_CS_HIGH;
	
	return flash_id;
}

//����FLASHָ��������
void SPI_Erase_Ssector(uint32_t addr) {
	SPI_Write_Enable();
	//Ƭѡ���ͣ�����ʱ��
	FLASH_SPI_CS_LOW;
	//����0X20��������
	SPI_FLASH_SendByte(SECTOR_ERASE);	
	
	//���Ͳ�����ַ
	SPI_FLASH_SendByte((addr >> 16) & 0xf);
	SPI_FLASH_SendByte((addr >> 8) & 0xf);
	SPI_FLASH_SendByte(addr);
	
	FLASH_SPI_CS_HIGH;
	
	//�ȴ�FLASH�ڲ�ʱ��������
	SPI_WaitForWriteEnd();
	
	return;
} 

//��ȡflash������
void SPI_Read_Data(uint32_t addr, uint8_t* read_buff, uint32_t numByteToRead) {
	//Ƭѡ���ͣ�����ʱ��
	FLASH_SPI_CS_LOW;
	//����0x05��ȡ����
	SPI_FLASH_SendByte(READ_DATA);	
	
	//����Ҫ��ȡ�ĵ�ַ
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

//�ȴ�FLASH�ڲ�ʱ��������
void SPI_WaitForWriteEnd(void) {
	uint8_t status_reg = 0;
	//Ƭѡ���ͣ�����ʱ��
	FLASH_SPI_CS_LOW;
	
	//���Ͷ�ȡ״̬�Ĵ�������
	SPI_FLASH_SendByte(READ_STATUS);	
	
	do {
		status_reg = SPI_FLASH_SendByte(DUMMY);	
	} 
	while((status_reg & 0x01) == 1);
	
	FLASH_SPI_CS_HIGH;
}

//д��ʹ��
void SPI_Write_Enable(void) {
	//Ƭѡ���ͣ�����ʱ��
	FLASH_SPI_CS_LOW;
	//����дʹ������
	SPI_FLASH_SendByte(WRITE_ENABLE);	
	FLASH_SPI_CS_HIGH;

}

//��FLASHд������
void SPI_Write_Data(uint32_t addr, uint8_t* write_buff, uint32_t numByteToWrite) {
	SPI_Write_Enable();
	//Ƭѡ���ͣ�����ʱ��
	FLASH_SPI_CS_LOW;
	//����0x02д������
	SPI_FLASH_SendByte(WRITE_DATA);	
	
	//����Ҫд��ĵ�ַ
	SPI_FLASH_SendByte((addr >> 16) & 0xf);
	SPI_FLASH_SendByte((addr >> 8) & 0xf);
	SPI_FLASH_SendByte(addr);
	
	while(numByteToWrite) {
		SPI_FLASH_SendByte(*write_buff);
		write_buff++;
		numByteToWrite--;
	}
	
	FLASH_SPI_CS_HIGH;
	
	//�ȴ�FLASH�ڲ�ʱ��������
	SPI_WaitForWriteEnd();
	
	return;
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode��������룬����������λ���ĸ����ڳ���.
  * @retval ����0����ʾIIC��ȡʧ��.
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FLASH_ERROR("I2C �ȴ���ʱ!errorCode = %d",errorCode);
  
  return 0;
}
