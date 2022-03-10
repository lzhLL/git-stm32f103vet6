//bsp:board support package板级支持包
#include "bsp_led.h"

//LED的GPIO初始化配置
void LED_GPIO_Config(void) {

	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = LED_ALL_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLOCK, ENABLE);
	
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
}
