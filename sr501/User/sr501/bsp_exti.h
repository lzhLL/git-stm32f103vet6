#ifndef __BSP_EXTI_H__
#define __BSP_EXTI_H__

#include "stm32f10x.h"


#define		SR501_INT_GPIO_PORT					GPIOA
#define		SR501_INT_GPIO_PIN					GPIO_Pin_4
#define		SR501_INT_GPIO_CLK					RCC_APB2Periph_GPIOA

#define		SR501_INT_EXTI_PORTSOURCE		GPIO_PortSourceGPIOA
#define 	SR501_INT_EXTI_PINSOURCE    GPIO_PinSource4
#define 	SR501_INT_EXTI_LINE         EXTI_Line4
#define 	SR501_INT_EXTI_IRQ					EXTI4_IRQn


static void EXTI_NVIC_Config(void);
void EXIT_SR501_Config(void);


#endif
