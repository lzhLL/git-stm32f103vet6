#include "bsp_key.h"
#include "bsp_led.h"

//KEY1、KEY2的GPIO初始化配置
void KEY_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN | KEY2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	
	//开时钟
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(KEY2_GPIO_CLOCK, ENABLE);
	
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);	
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);	
	
	
}


uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if( KEY_ON == GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) ) {
		//松手检测
		while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON );

		return KEY_ON;	
	} else {
		return KEY_OFF;
	}


}

void Key_Func(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if( KEY_ON == GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) ) {
		//松手检测
		LED_RGB(ON);
		while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON );
		LED_RGB(OFF);
			
	} 


}
