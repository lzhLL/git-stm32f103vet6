#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"

uint8_t I2C_Test(void);

extern uint8_t ucTemp;
uint8_t read_ee_buf[256] = {0};
uint8_t write_ee_buf[256] = {0};

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
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	LED_GPIO_Config();//LED��GPIO��ʼ������
	USART_Config();		//��ʼ����������
	I2C_EE_Config();	//EEPROM��ʼ��
	
	LED_BLUE;
	Usart_SendStr(DEBUG_USARTx, "����һ��I2CͨѶʵ�飡\n");
	printf("����һ��I2CͨѶʵ��\n");
	
  if( I2C_Test() == 1) {
		LED_GREEN;
	} else {
		LED_RED;
	}
	
	while(1) {
//		switch(ucTemp) {
//			case 0x01:	
//				LED_RED;
//				break;
//			
//			case 0x02:	
//				LED_GREEN;

//				break;

//			case 0x03:	
//				LED_BLUE;

//				break;
//			
//			default:
//				LED_RGBOFF;
//				break;
//		}
		
	}
	
}

uint8_t I2C_Test(void) {
	uint16_t i = 0;
	printf("д�������\n\r");
	
	for(i = 0; i < 256; i++) {
		write_ee_buf[i] = i;
		
		printf("%3d ", write_ee_buf[i]);
		if( (i % 16) == 15) {
			printf("\r\n");
		}
	}
	
	I2C_EE_BufferWrite(write_ee_buf, 0, 256);
	printf("\n\rд��ɹ�!\n\r");
	printf("\n\r����������\n\r");
	
	EEPROM_Read(0, read_ee_buf, 256);
	for(i = 0; i < 256; i++) {	
		printf("%3d ", read_ee_buf[i]);
		if( (i % 16) == 15) {
			printf("\r\n");
		}
	}	
	
	return 1;
}
