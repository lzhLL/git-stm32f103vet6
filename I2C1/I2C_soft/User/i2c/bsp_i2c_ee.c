#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "bsp_usart.h" 

/*
*********************************************************************************************************
*	�� �� ��: ee_CheckOk
*	����˵��: �жϴ���EERPOM�Ƿ�����
*	��    �Σ���
*	�� �� ֵ: 1 ��ʾ������ 0 ��ʾ������
*********************************************************************************************************
*/
uint8_t ee_CheckOk(void)
{
	if (i2c_CheckDevice(EEPROM_DEV_ADDR) == 0) {
		return 1;
	} else {
		/* ʧ�ܺ��мǷ���I2C����ֹͣ�ź� */
		i2c_Stop();		
		return 0;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: ee_WriteBytes
*	����˵��: ����EEPROMָ����ַд���������ݣ�����ҳд�������д��Ч��
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 			_usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 			_pWriteBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 1��ʾ�ɹ�, 0��ʾʧ��
*********************************************************************************************************
*/
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize) {
	uint16_t i, m, usAddr;
	
	usAddr = _usAddress;
	for(i = 0; i < _usSize; i++) {
		/* �����͵�1���ֽڻ���ҳ���׵�ַʱ����Ҫ���·��������źź͵�ַ */
		if(0 == i || (usAddr & (EEPROM_PAGE_SIZE - 1)) == 0 ) {
			i2c_Stop();
			for(m = 0; m < 1000; m++) {
				i2c_Start();
				i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);	/* �����豸��ַ+д���� */
				if (i2c_WaitAck() == 0) {
					break;
				}				
			}
			
			if (m  == 1000) {
				goto cmd_fail;	/* EEPROM����д��ʱ */
			}			
			
			
			i2c_SendByte((uint8_t)usAddr);
			
			if (i2c_WaitAck() != 0) {
				goto cmd_fail;	/* EEPROM������Ӧ�� */
			}
		}
		/* ��ʼд������ */
		i2c_SendByte(_pWriteBuf[i]);
		if (i2c_WaitAck() != 0) {
				goto cmd_fail;	/* EEPROM������Ӧ�� */
		}
		
		usAddr++;	/* ��ַ��1 */
		
		
	}
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;

}

/*
*********************************************************************************************************
*	�� �� ��: ee_ReadBytes
*	����˵��: �Ӵ���EEPROMָ����ַ����ʼ��ȡ��������
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pReadBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize) {
	uint16_t i;
	i2c_Start();
	i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);	/* �˴���дָ�� */
	if (i2c_WaitAck() != 0) {
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)_usAddress);//�������Ķ��ĵ�ַ
	if (i2c_WaitAck() != 0) {
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}
	
	i2c_Start();
	i2c_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_RD);	/* �˴��Ƕ�ָ�� */
	if (i2c_WaitAck() != 0) {
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}
	
	for (i = 0; i < _usSize; i++) {
		_pReadBuf[i] = i2c_ReadByte();	/* ��1���ֽ� */
		if(i != _usSize-1 ) {
			i2c_Ack();	//��������Ӧ���ź�
		} else {
			i2c_NAck();	/* ���1���ֽڶ�����������ͷ�Ӧ���ź�*/
		}
	}
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;	
	
cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;	
}


void ee_Erase(void)
{
	uint16_t i;
	uint8_t send_buf[EEPROM_SIZE];
	uint8_t read_buf[EEPROM_SIZE] = {0};
	
	/* ��仺���� */
	for (i = 0; i < EEPROM_SIZE; i++)
	{
		send_buf[i] = 0xFF;
	}
	if( ee_CheckOk() == 0 ) {
		printf("û�м�⵽EEPROM!!!\r\n");
		return ;
	}
	/* дEEPROM, ��ʼ��ַ = 0�����ݳ���Ϊ 256 */
	if (ee_WriteBytes(send_buf, 0, EEPROM_SIZE) == 0) {
		printf("����eeprom����\r\n");
		return;
	} else {
		printf("����eeprom�ɹ���\r\n");
		ee_ReadBytes(read_buf, 0, EEPROM_SIZE);
		for(i = 0; i < EEPROM_SIZE; i++) {
			printf(" %02X", read_buf[i]);
			if( (i & 15) == 15 ) {
				printf("\r\n");
			}
		}
	}
}

/*--------------------------------------------------------------------------------------------------*/
static void ee_Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*
 * eeprom AT24C02 ��д����
 * ��������1���쳣����0
 */
uint8_t ee_Test(void) {
  uint16_t i;
	uint8_t write_buf[EEPROM_SIZE] = {0};
  uint8_t read_buf[EEPROM_SIZE] = {0};
	
	if (ee_CheckOk() == 0) {
		printf("û�м�⵽����EEPROM!\r\n");
		return 0;
	}
	/* �����Ի����� */
	for(i = 0; i < EEPROM_SIZE; i++) {
		write_buf[i] = i;
	}
	
	if( ee_WriteBytes(write_buf, 0, EEPROM_SIZE) == 0 ) {
		printf("дeeprom����\r\n");
		return 0;
	} else {
		printf("дeeprom�ɹ���\r\n");
	}
	
  /*д��֮����Ҫ�ʵ�����ʱ��ȥ������Ȼ�����*/
  ee_Delay(0x0FFFFF);
/*-----------------------------------------------------------------------------------*/
  if (ee_ReadBytes(read_buf, 0, EEPROM_SIZE) == 0) {
		printf("��eeprom����\r\n");
		return 0;
	} else {		
		printf("��eeprom�ɹ����������£�\r\n");
	}
	
	for(i = 0; i < EEPROM_SIZE; i++) {
		if(read_buf[i] != write_buf[i]) {
			printf("0x%02X ", read_buf[i]);
			printf("����:EEPROM������д������ݲ�һ��");
			return 0;
		}
		printf(" %02X", read_buf[i]);
		
		if ((i & 15) == 15) {
			printf("\r\n");	
		}
	}
	printf("eeprom��д���Գɹ�\r\n");
	return 1;
}

/*********************************************END OF FILE**********************/
