//bsp:board support package板级支持包
#include "bsp_led.h"

//LED的GPIO初始化配置
void LED_GPIO_Config(void) {
	/* 定义一个GPIO_InitTypeDef类型的结构体 */
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* 开启LED相关的GPIO外设时钟 */
	RCC_APB2PeriphClockCmd(LED_B_GPIO_CLOCK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED_ALL_GPIO_PIN;
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	
	/*设置引脚速率为50MHz */ 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

	/* 关闭所有led灯	*/
	GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
		
	/* 关闭所有led灯	*/
	GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);	 
		
	/* 关闭所有led灯	*/
	GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}
