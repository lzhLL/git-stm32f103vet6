#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
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
	// 来到这里的时候，系统的时钟已经被配置成72M。
	
//	unsigned char buf = 'a';
//	uint8_t buffer[10] = "abcdef";
	LED_GPIO_Config();//LED的GPIO初始化配置
	USART_Config();		//初始化串口配置
	
//	Usart_SendByte(DEBUG_USARTx, buf);
//	Usart_SendHalfWord(DEBUG_USARTx, 0xff56);
	//Usart_SendArray(DEBUG_USARTx, buffer,  10);
	Usart_SendStr(DEBUG_USARTx, "欢迎使用智能家居系统！\n");
	printf("开发板是stm32f103\n");
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
