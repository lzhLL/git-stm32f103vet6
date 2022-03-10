#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"

#define LED_G_GPIO_PIN		GPIO_Pin_0
#define LED_B_GPIO_PIN		GPIO_Pin_1
#define LED_R_GPIO_PIN		GPIO_Pin_5
#define LED_ALL_GPIO_PIN	(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5)


#define LED_GPIO_PORT		GPIOB
#define LED_GPIO_CLOCK	RCC_APB2Periph_GPIOB

#define ON	1
#define OFF	(!ON)

#define LED_RGB(a)	if(a) GPIO_ResetBits(LED_GPIO_PORT, LED_ALL_GPIO_PIN); else GPIO_SetBits(LED_GPIO_PORT, LED_ALL_GPIO_PIN);
#define LED_G_TOGGLE			{LED_GPIO_PORT->ODR ^= GPIO_Pin_0;}

void LED_GPIO_Config(void);

#endif
