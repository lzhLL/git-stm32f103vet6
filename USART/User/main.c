#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"

extern uint8_t ucTemp;

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
	
//	unsigned char buf = 'a';
//	uint8_t buffer[10] = "abcdef";
	LED_GPIO_Config();//LED��GPIO��ʼ������
	USART_Config();		//��ʼ����������
	
//	Usart_SendByte(DEBUG_USARTx, buf);
//	Usart_SendHalfWord(DEBUG_USARTx, 0xff56);
	//Usart_SendArray(DEBUG_USARTx, buffer,  10);
	Usart_SendStr(DEBUG_USARTx, "��ӭʹ�����ܼҾ�ϵͳ��\n");
	printf("��������stm32f103\n");
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
