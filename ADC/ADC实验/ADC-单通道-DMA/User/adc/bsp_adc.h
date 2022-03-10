#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"



// ADC_GPIO宏定义
// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
#define  ADC_GPIO_PORT       						GPIOC  
#define  ADC_GPIO_PIN        						GPIO_Pin_1
#define  ADC_GPIO_CLK           				(RCC_APB2Periph_GPIOC)
#define  ADC_GPIO_APBxClock_FUN   			RCC_APB2PeriphClockCmd

//ADC编号选择
// 可以是ADC1/2,如果使用ADC3,中断相关的要改成ADC3的
#define  ADC_APBxClock_FUN   						RCC_APB2PeriphClockCmd
#define  ADC_x													ADC1
#define  ADC_CLK                				RCC_APB2Periph_ADC1

//ADC 通道选择
#define  ADC_CHANNEL										ADC_Channel_11

//DMA1
#define  ADC_DMA_CLK               			RCC_AHBPeriph_DMA1
#define  ADC_DMA_CHANNEL           			DMA1_Channel1

#define  ADC_DMA_FLAG_TC           			DMA1_FLAG_TC4

void ADCx_Init	(void);
uint16_t ADC_Trans(void);

#endif  /* __BSP_ADC_H */

