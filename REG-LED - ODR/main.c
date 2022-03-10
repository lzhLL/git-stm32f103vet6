
#include "stm32f10x.h"

int main(void) {
	
#if 0
	/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	*((unsigned int*) 0x40021018) |= (1 << 3);//打开GPIOB时钟
	
	//配置GPIOB_CRL寄存器为输出模式
	*((unsigned int*) 0x40010c00) &= ~(16 << 0);	//前四位置0
	*((unsigned int*) 0x40010c00) |= (1 << 0);		//bit0置1
	
	//将GPIOB_ODR寄存器输出bit0输出0(点亮LED_G灯)
	*((unsigned int*) 0x40010c0c) &= ~(1 << 0);
	
#elif 0
	
	/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	RCC_APB2ENR |= (1 << 3);//打开GPIOB时钟
	
	//配置GPIOB_CRL寄存器为输出模式
	GPIOB_CRL &= ~(16 << 0);	//前四位置0
	GPIOB_CRL |= (1 << 0);		//bit0置1
	
	//将GPIOB_ODR寄存器输出bit0输出0(点亮LED_G灯)
	GPIOB_ODR &= ~(1 << 0);
	
#elif 0
		/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	RCC->APB2ENR |= (1 << 3);//打开GPIOB时钟
	
	//配置GPIOB_CRL寄存器为输出模式
	GPIOB->CRL &= ~(16 << 0);	//前四位置0
	GPIOB->CRL |= (1 << 0);		//bit0置1
	
	//将GPIOB_ODR寄存器输出bit0输出0(点亮LED_G灯)
	GPIOB->ODR &= ~(1 << 0);
	//GPIOB->ODR |= (1 << 0);
	
#elif 1
		/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	RCC->APB2ENR |= (1 << 3);//打开GPIOB时钟
	
	//配置GPIOB_CRL寄存器为输出模式
	GPIOB->CRL &= ~(16 << 0);	//前四位置0
	GPIOB->CRL |= (1 << 0);		//bit0置1
	
	//将GPIOB_ODR寄存器输出bit0输出0(点亮LED_G灯)
	GPIOB->ODR &= ~(1 << 0);
	
#endif	
	return 0;

}

void SystemInit(void) { 

	
	//函数体为空，目的是为了骗过编译器不报错 
	return ;
}

