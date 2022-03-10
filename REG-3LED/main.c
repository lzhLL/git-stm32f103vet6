#if 0
#include <reg52.h>

sbit LED = P0^0

void main(void) {
	P0 = 0xfe;		//总线操作

	LED = 0;			//位操作
	
	return ;
}


#endif




/* 写一个延时函数，实现闪烁PB0 PB1 PB5  */
#include "stm32f10x.h"

void LedInit(void);
void SystemInit(void);
void delay(unsigned int n);

int main(void) {
	LedInit();
	while(1) {
		//将GPIOB_ODR寄存器输出bit0、bit1、bit5输出0(点亮LED_GGB灯)
		*((unsigned int*) 0x40010c0c) &= ~((1 << 0) | (1 << 1) | (1 << 5));
		delay(100000);
		//将GPIOB_ODR寄存器输出bit0、bit1、bit5输出1(熄灭LED_GGB灯)
		*((unsigned int*) 0x40010c0c) |= ((1 << 0) | (1 << 1) | (1 << 5));
		delay(100000);	
	}
	
	return 0;
}


void LedInit(void) {
	/* RCC_APB2ENR， 打开GPIOB的时钟， 偏移量为0x18 ，基地址为AHB, rcc起始地址为0x40021000 */
	*((unsigned int*) 0x40021018) |= (1 << 3);//打开GPIOB时钟
	
	//配置GPIOB_CRL寄存器为输出模式
	*((unsigned int*) 0x40010c00) &= ~((256 << 0) | (20 << 0) | (21 << 0) | (22 << 0) | (23 << 0));	//前8位置0,bit20~23置0
	*((unsigned int*) 0x40010c00) |= ((1 << 0) | (1 << 4) | (1 << 20));		//bit0置1
	return ;
}

void SystemInit(void) { 

	
	//函数体为空，目的是为了骗过编译器不报错 
	return ;
}


void delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}

