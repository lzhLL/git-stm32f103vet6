//bsp:board support package�弶֧�ְ�
#include "bsp_led.h"

//LED��GPIO��ʼ������
void LED_GPIO_Config(void) {

	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = LED_ALL_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLOCK, ENABLE);
	
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
}
