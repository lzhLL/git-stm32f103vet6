#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void SystemInit(void);

int main(void) {
	
#if 0
	/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	*((unsigned int*) 0x40021018) |= (1 << 3);//打开GPIOB时钟
	
	//配置GPIOB_CRL寄存器为通用推挽输出模式，最大速度为10MHZ
	*((unsigned int*) 0x40010c00) &= ~(16 << 0);	//前四位置0
	*((unsigned int*) 0x40010c00) |= (1 << 0);		//bit0置1
	
	//将GPIOB_ODR寄存器输出bit0输出0(点亮LED_G灯)
	*((unsigned int*) 0x40010c0c) &= ~(1 << 0);
	
#elif 0
	/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	RCC->APB2ENR |= (1 << 3);//打开GPIOB时钟

	//配置GPIOB_CRL寄存器为输出模式
	GPIOB->CRL &= ~((256 << 0) | (20 << 0) | (21 << 0) | (22 << 0) | (23 << 0));	//前8位置0,bit20~23置0
	GPIOB->CRL |= ((1 << 0) | (1 << 4) | (1 << 20));		//bit0置1
	
	//将GPIOB_BSRR寄存器的bit0置1, 目的是置GPIOB_ODRbit0为1(熄灭LED_G灯)
	//GPIO_SetBits(GPIOB, GPIO_Pin_0);
	
	//将GPIOB_BRR寄存器的bit0置1, 目的是置GPIOB_ODRbit0为0(点亮LED_G灯)
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	
#elif 1
	/* RCC_APB2ENR GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	RCC->APB2ENR |= (1 << 3);//打开GPIOB时钟

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//将GPIOB_BSRR寄存器的bit0置1, 目的是置GPIOB_ODRbit0为1(熄灭LED_G灯)
	//GPIO_SetBits(GPIOB, GPIO_Pin_0);
	
	//将GPIOB_BRR寄存器的bit0置1, 目的是置GPIOB_ODRbit0为0(点亮LED_G灯)
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
	
	
#endif
	return 0;

}

void SystemInit(void) { 

	
	//函数体为空，目的是为了骗过编译器不报错 
	return ;
}




