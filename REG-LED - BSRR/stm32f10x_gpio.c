#include "stm32f10x_gpio.h"

//相当于将ODR输出寄存器置1 
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BSRR |= GPIO_Pin;
	
	return ;
}

//相当于将ODR输出寄存器置0
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BRR |= GPIO_Pin;
	
	return ;
}



