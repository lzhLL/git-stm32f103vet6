#include "bsp_i2c_gpio.h"

static void i2c_CfgGpio(void);

static void i2c_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
  
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
	*/
	for (i = 0; i < 10; i++);
}



/* I2C��ʼ�ź� */
void i2c_Start(void) {
	EEPROM_I2C_SDA_1();		//һ��ʼSDA�Ǹߵ�ƽ
	EEPROM_I2C_SCL_1();		//һ��ʼSCL�Ǹߵ�ƽ
	i2c_Delay();
	EEPROM_I2C_SDA_0();		//��SDA����������
	i2c_Delay();
	//EEPROM_I2C_SCL_0();		//��SCLʱ��������
	//i2c_Delay();

	return ;
	
}

/* I2Cֹͣ�ź� */
void i2c_Stop(void) {
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	EEPROM_I2C_SDA_0();		//��SDA����������
	EEPROM_I2C_SCL_1();
	i2c_Delay();
	EEPROM_I2C_SDA_1();		//��SDA����������

	return ;
}


/* ����˵��: CPU��I2C�����豸����8bit���� */
void i2c_SendByte(uint8_t _ucByte) {
	uint8_t i;
	EEPROM_I2C_SCL_0();	//�������ݱ仯
	i2c_Delay();
	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{	
		if (_ucByte & 0x80) {		//������λ��1���ͷ��͸ߵ�ƽ������ͷ��͵͵�ƽ
			EEPROM_I2C_SDA_1();
		} else {
			EEPROM_I2C_SDA_0();
		}
		_ucByte <<= 1;	/* ����һ��bit */
		
		EEPROM_I2C_SCL_1();		//SCL�ߵ�ƽ��������Ч
		i2c_Delay();	
		
		EEPROM_I2C_SCL_0();		//�������ݱ仯
		i2c_Delay();	
		
	}
	
	EEPROM_I2C_SDA_1(); // �ͷ�����	(����Ӧ���ź�)
	i2c_Delay();
	
	return;
}



/* ����˵��: CPU��I2C�����豸��ȡ8bit���� */
uint8_t i2c_ReadByte(void) {
	//�����Ǵ��е�
	uint8_t i;
	uint8_t value;
	
	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	
	/* SCL�����������ͣ����߶�ȡ���ݣ������������ݱ仯 */
	for(i = 0; i < 8; i++) {
		value <<= 1;
		EEPROM_I2C_SCL_1();//SCL�ߵ�ƽ��������Ч
		i2c_Delay();
		if (EEPROM_I2C_SDA_READ()) {	//���������bitΪ1����ô����1
			value++;
		}
		EEPROM_I2C_SCL_0();	//�������ݱ仯
		i2c_Delay();
	}
	
	return value;
}

/* ����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź� */
uint8_t i2c_WaitAck(void) {
	uint8_t reply;
	
	EEPROM_I2C_SDA_1();	/* CPU�ͷ�SDA���ߣ��ɴӻ��ӹ������� */
	i2c_Delay();
	
	EEPROM_I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
	
	//��ȡSDA�����ߵĵ�9bit
	if( EEPROM_I2C_SDA_READ() ) {
		reply = 1;
	} else {
		reply = 0;
	}
	
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	
	return reply;
	
}


/* ����˵��: CPU����һ��ACK�ź� */
void i2c_Ack(void) {
	EEPROM_I2C_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	EEPROM_I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();
	EEPROM_I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}

/* ����˵��: CPU����1��NACK�ź� */
void i2c_NAck(void) {
	EEPROM_I2C_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	EEPROM_I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	EEPROM_I2C_SCL_0();
	i2c_Delay();	
}

/* ����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ�� */
static void i2c_CfgGpio(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(EEPROM_I2C_GPIO_PORT_RCC, ENABLE);	/* ��GPIOBʱ�� */
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* ��©��� */
	GPIO_Init(EEPROM_I2C_GPIO_PORT, &GPIO_InitStructure);	

	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
	i2c_Stop();
	
	return ;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_CheckDevice
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    �Σ�_Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address) {
	uint8_t ucAck;
	
	i2c_CfgGpio();		/* ����GPIO */
	
	i2c_Start();		/* ���������ź� */
	
	/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
	i2c_SendByte(_Address | EEPROM_I2C_WR);
	ucAck = i2c_WaitAck();	/* ����豸��ACKӦ�� */
	//i2c_Stop();			/* ����ֹͣ�ź� */
	
	return ucAck;

}
