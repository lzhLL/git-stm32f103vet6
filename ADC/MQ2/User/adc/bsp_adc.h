#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"

//����PC2 12ͨ�� ADC1

// ADC_GPIO�궨��
// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
#define  ADC_GPIO_PORT       						GPIOC  
#define  ADC_GPIO_PIN        						GPIO_Pin_2
#define  ADC_GPIO_CLK           				(RCC_APB2Periph_GPIOC)
#define  ADC_GPIO_APBxClock_FUN   			RCC_APB2PeriphClockCmd

//ADC���ѡ��
// ������ADC1/2,���ʹ��ADC3,�ж���ص�Ҫ�ĳ�ADC3��
#define  ADC_APBxClock_FUN   						RCC_APB2PeriphClockCmd
#define  ADC_x													ADC1
#define  ADC_CLK                				RCC_APB2Periph_ADC1

//ADC ͨ��ѡ��
#define  ADC_CHANNEL										ADC_Channel_12

//ADC �ж���غ궨��
#define  ADC_IRQ												ADC1_2_IRQn
#define  ADC_IRQHandler									ADC1_2_IRQHandler

void ADCx_Init(void);
uint16_t ADC_Trans(void);//ȡ�����ƽ��ֵ


extern __IO uint16_t ADC_ConvertedValue;

#endif  /* __BSP_ADC_H */

