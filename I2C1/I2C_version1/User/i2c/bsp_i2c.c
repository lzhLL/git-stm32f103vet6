#include "bsp_i2c.h"

/**
  * @brief  I2C eeprom ���ã�������������
  * @param  None
  * @retval None
  */
	
void I2C_EE_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStruct;

	// �򿪴���I2C GPIOB��ʱ��
	EEPROM_I2C_GPIO_APBxClkCmd(EEPROM_I2C_SCL_GPIO_CLK | EEPROM_I2C_SDA_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	EEPROM_I2C_APBxClkCmd(EEPROM_I2C_CLK, ENABLE);

	// ��I2C_SCL��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  // ��I2C_SDA��GPIO����Ϊ Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	
	// ����I2C�Ĺ�������
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;//ʹ��Ӧ��
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7λ��ַ
	I2C_InitStruct.I2C_ClockSpeed = EEPROM_I2C_BAUDRATE;//400khz
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;//2:1
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = TM32_I2C_OWN_ADDR;
	
	// ���I2c�ĳ�ʼ������
	I2C_Init(EEPROM_I2C, &I2C_InitStruct);

	// ʹ�ܴ���
	I2C_Cmd(EEPROM_I2C, ENABLE);
}



/* ��EEPROMд��һ���ֽ� */
void EEPROM_Byte_Write(uint8_t addr, uint8_t data) {
	//��ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���EV5�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//����eeprom�豸��ַ 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	//���EV6��EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	//����Ҫ�����Ĵ洢��Ԫ�ĵ�ַ
	I2C_SendData(EEPROM_I2C, addr);
	
	//���EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	//����Ҫ�洢������
	I2C_SendData(EEPROM_I2C, data);

	//���EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	//���EV8_2�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	//���ݴ������
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	
}

/* ��EEPROMд�����ֽڣ�ҳд�룩��ÿ��д�벻�ܳ���8���ֽ� */
void EEPROM_Page_Write(uint8_t addr, uint8_t* data, uint8_t numByteToWrite) {
	//��ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���EV5�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//����eeprom�豸��ַ 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	//���EV6��EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	//����Ҫ�����Ĵ洢��Ԫ�ĵ�ַ
	I2C_SendData(EEPROM_I2C, addr);
	
	//���EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	
	while(numByteToWrite) {
		//����Ҫ�洢������
		I2C_SendData(EEPROM_I2C, *data);
		data++;
		numByteToWrite--;
		
		//���EV8�¼�
		while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	}

	
	//���EV8_2�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	//���ݴ������
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	
}

/* �ú����Ĺ����ǿ��Բ��ö���8�ֽ�Ҳ��д��EEPROM */
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
	
	//Addr����������Ƿ��ܱ�8����
	Addr = WriteAddr % I2C_PageSize;
	
	count = I2C_PageSize - Addr;
	
	//NumOfPage�Ǽ�¼�ж���ҳ
	NumOfPage = NumByteToWrite / I2C_PageSize;
	
	//NumOfSingle��¼���һҳ��Ҫд����ٸ��ֽ�
	NumOfSingle = NumByteToWrite % I2C_PageSize;
	
	//����ֽ����������ֽ�8
	if( 0 == Addr ) {
		//���һҳδ��
		if( 0 == NumOfPage ) {
			EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
			EEPROM_WaitForWriteEnd();//�ȴ�д�����
		} else {	//�����ֹһҳ�����Ҷ����ֽ�8
			while(NumOfPage--) {
				EEPROM_Page_Write(WriteAddr, pBuffer, I2C_PageSize);
				EEPROM_WaitForWriteEnd();//�ȴ�д�����
				WriteAddr += I2C_PageSize;
				pBuffer += I2C_PageSize;		
			}
			if(0 == NumOfPage && NumOfSingle != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
				EEPROM_WaitForWriteEnd();//�ȴ�д�����
			}
		}
	} else { //����ֽ������������ֽ�8
		//���һҳδ��
		if( 0 == NumOfPage ) {
			EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
			EEPROM_WaitForWriteEnd();//�ȴ�д�����
		} else { ////�����ֹһҳ�����Ҷ����ֽ�8
			NumByteToWrite = NumByteToWrite - count;
			NumOfPage =  NumByteToWrite / I2C_PageSize;
			NumOfSingle = NumByteToWrite % I2C_PageSize;	
			
			if(count != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, count);
				EEPROM_WaitForWriteEnd();//�ȴ�д�����
				WriteAddr = WriteAddr + count;
				pBuffer = pBuffer + count;
			}
			
			while(NumOfPage != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, I2C_PageSize);
				EEPROM_WaitForWriteEnd();//�ȴ�д�����
				--NumOfPage;
				WriteAddr = WriteAddr + I2C_PageSize;
				pBuffer = pBuffer + I2C_PageSize;
			}
			
			if(NumOfSingle != 0) {
				EEPROM_Page_Write(WriteAddr, pBuffer, NumOfSingle);
				EEPROM_WaitForWriteEnd();//�ȴ�д�����
				
			}
		}
	} 
}

/* ��EEPROM��ȡ���� */
void EEPROM_Read(uint8_t addr, uint8_t* data, uint8_t num) {
	//��ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���EV5�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//����eeprom�豸��ַ 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	//���EV6��EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	//����Ҫ�����Ĵ洢��Ԫ�ĵ�ַ
	I2C_SendData(EEPROM_I2C, addr);
	
	//���EV8�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	
	
	
	//�ڶ�����ʼ�ź�
	//��ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2C, ENABLE);
	
	//���EV5�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	//����eeprom�豸��ַ 
	I2C_Send7bitAddress(EEPROM_I2C, EEPROM_ADDR, I2C_Direction_Receiver);
	
	//���EV6�¼�
	while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	
	
	while(num) {
		//���Ϊ���һ���ֽ�
		if(1 == num) {
			I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
			//���EV7�¼�
			//while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);		
			*data = I2C_ReceiveData(EEPROM_I2C);		
		}		
		
		//���EV7�¼�
		while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
		
		//��������
		*data = I2C_ReceiveData(EEPROM_I2C);

		//���EV7�¼� add by lzh
		//while( I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);

		
		data++;
		
		num--;
	}
	
	
	//���ݴ������
	I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
	
	//��������ACKʹ�ܣ��Ա��´�ͨѶ
	I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
}


/* �ȴ�EEPROM�ڲ�ʱ����� */
void EEPROM_WaitForWriteEnd(void) {
	do 
	{
		//������ʼ�ź�
		I2C_GenerateSTART(EEPROM_I2C,ENABLE);
		while( I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_SB) == RESET );
		
		//�����豸��ַ
		I2C_Send7bitAddress(EEPROM_I2C,EEPROM_ADDR,I2C_Direction_Transmitter);
	}
	while( I2C_GetFlagStatus(EEPROM_I2C, I2C_FLAG_ADDR) == RESET );	

	//EEPROM�ڲ�ʱ����ɴ������
	I2C_GenerateSTOP(EEPROM_I2C,ENABLE);	

}


