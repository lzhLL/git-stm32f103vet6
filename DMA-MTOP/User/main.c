#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_dma_mtp.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];

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
	uint16_t i = 0;
	USART_Config();
	for(i = 0; i < SENDBUFF_SIZE; i++) {
		SendBuff[i] = 'p';
	}
	
	LED_GPIO_Config();//LED��GPIO��ʼ������
	
	USARTx_DMA_Config();
	USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
	
	while(1) {
		GPIO_ResetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		Delay(5000);
		
		GPIO_ResetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		Delay(5000);	
		
		GPIO_ResetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		Delay(5000);	
	}
	
}
