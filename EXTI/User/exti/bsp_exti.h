#ifndef __BSP_EXTI_H__
#define __BSP_EXTI_H__

#include "stm32f10x.h"

#define KEY1_INT_GPIO_PIN			GPIO_Pin_0
#define KEY1_INT_GPIO_PORT		GPIOA
#define KEY1_INT_GPIO_CLOCK		RCC_APB2Periph_GPIOA

#define KEY2_INT_GPIO_PIN			GPIO_Pin_13
#define KEY2_INT_GPIO_PORT		GPIOC
#define KEY2_INT_GPIO_CLOCK		RCC_APB2Periph_GPIOC



static void EXTI_NVIC_Config(void);
void EXIT_Key_Config(void);


#endif
