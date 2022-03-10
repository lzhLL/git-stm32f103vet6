#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_exti.h"

//void MCO_GPIO_Config(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStruct;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA, &GPIO_InitStruct);	
//}

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
	
	LED_GPIO_Config();//LED的GPIO初始化配置
	EXIT_SR501_Config();
	MCO_GPIO_Config();
	while(1) {
		//RCC_MCOConfig(RCC_MCO_SYSCLK);
		if( GPIO_ReadInputDataBit(SR501_INT_GPIO_PORT, SR501_INT_GPIO_PIN) == 0) {
			GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
		}
		
		Delay(0xFFF);
	}
	
}
