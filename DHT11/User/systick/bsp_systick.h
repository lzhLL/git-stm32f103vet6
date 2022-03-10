#ifndef _BSP_SYSTICK_H
#define _BSP_SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);         // ��λ1us


#define Delay_ms(x) Delay_us(1000*x)	 //��λms

#endif /*_BSP_SYSTICK_H*/




