#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"

//换成PC2 12通道 ADC1

// ADC_GPIO宏定义
// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
#define  ADC_GPIO_PORT       						GPIOC  
#define  ADC_GPIO_PIN        						GPIO_Pin_2
#define  ADC_GPIO_CLK           				(RCC_APB2Periph_GPIOC)
#define  ADC_GPIO_APBxClock_FUN   			RCC_APB2PeriphClockCmd

//ADC编号选择
// 可以是ADC1/2,如果使用ADC3,中断相关的要改成ADC3的
#define  ADC_APBxClock_FUN   						RCC_APB2PeriphClockCmd
#define  ADC_x													ADC1
#define  ADC_CLK                				RCC_APB2Periph_ADC1

//ADC 通道选择
#define  ADC_CHANNEL										ADC_Channel_12

//ADC 中断相关宏定义
#define  ADC_IRQ												ADC1_2_IRQn
#define  ADC_IRQHandler									ADC1_2_IRQHandler

void ADCx_Init(void);
uint16_t ADC_Trans(void);//取烟雾的平均值


extern __IO uint16_t ADC_ConvertedValue;

#endif  /* __BSP_ADC_H */

