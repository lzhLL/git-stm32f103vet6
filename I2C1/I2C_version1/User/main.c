#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"

extern uint8_t ucTemp;
uint8_t read_ee_data[10] = {0};
uint8_t write_ee_data[8] = {2,3,4,5,6,7};
uint8_t pBuffer[22] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
void Delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5000; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}


//1.��ʼ��IIC��ص�GPIO
//2.����IIC����Ĺ���ģʽ
//3.��дIICд��EEPROM��Byte write����
//4.��дIIC��ȡEEPROM��RANDOM Read����
//5.ʹ��read������write�������ж�дУ��
//6.��дpage write ��seq read������У��

int main(void) {
	uint8_t i = 0;
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	LED_GPIO_Config();//LED��GPIO��ʼ������
	USART_Config();		//��ʼ����������
	I2C_EE_Config();	//EEPROM��ʼ��
	
	Usart_SendStr(DEBUG_USARTx, "����һ��I2CͨѶʵ�飡\n");
	printf("����һ��I2CͨѶʵ��\n");
	
	//д��һ���ֽ�
	EEPROM_Byte_Write(11, 0x55); 
	
	//�ȴ�д��EEPROM���
	EEPROM_WaitForWriteEnd();
	
	//��������
	EEPROM_Read(11, read_ee_data, 1);
	
	printf("���յ�������Ϊ:0x%x\r\n", read_ee_data[0]);
	
	//д��8���ֽ�
	EEPROM_Page_Write(17, write_ee_data, 6);
	//�ȴ�д��EEPROM���
	EEPROM_WaitForWriteEnd();	
	//��������
	EEPROM_Read(17, read_ee_data, 6);
	for(i = 0; i < 6; i++) {
		printf("%d\r\n", read_ee_data[i]);
	}
	
	I2C_EE_BufferWrite(pBuffer, 17, 22);
	EEPROM_Read(17, read_ee_data, 22);
	for(i = 0; i < 22; i++) {
		printf("%d ", read_ee_data[i]);
		if( (i % 8) == 7) {
			printf("\r\n");
		}
	}
	
	while(1) {
		switch(ucTemp) {
			case 0x01:	
				LED_RED;
				break;
			
			case 0x02:	
				LED_GREEN;

				break;

			case 0x03:	
				LED_BLUE;

				break;
			
			default:
				LED_RGBOFF;
				break;
		}
		
	}
	
}
