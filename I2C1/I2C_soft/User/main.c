#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c_gpio.h"
#include "bsp_i2c_ee.h"




//extern uint8_t ucTemp;

void Delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5000; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}



int main(void) {
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	LED_GPIO_Config();//LED��GPIO��ʼ������
	USART_Config();		//��ʼ����������
	LED_BLUE;
	printf("��������stm32f103\n");
	printf("eeprom ���ģ��i2c�������� \r\n");
	ee_Erase();	//����EEPROM
	if( ee_Test() == 1 ) {
		LED_GREEN;
	} else {
		LED_RED;
	}
	while(1);
	
}
