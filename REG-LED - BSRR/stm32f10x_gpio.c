#include "stm32f10x_gpio.h"

//�൱�ڽ�ODR����Ĵ�����1 
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BSRR |= GPIO_Pin;
	
	return ;
}

//�൱�ڽ�ODR����Ĵ�����0
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BRR |= GPIO_Pin;
	
	return ;
}



