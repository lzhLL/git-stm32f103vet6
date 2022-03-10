#ifndef __BSP_DHT11_H__
#define __BSP_DHT11_H__

#include "stm32f10x.h"
#include "./dwt_delay/core_delay.h" 

/************************** DHT11 �������Ͷ���********************************/
typedef struct {
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
	
} DHT11_Data_TypeDef;


/************************** ��ʱ********************************/
#define DHT11_DELAY_US(us)  CPU_TS_Tmr_Delay_US(us)	//1us
#define DHT11_DELAY_MS(ms)  CPU_TS_Tmr_Delay_MS(ms)	//1ms

/************************** DHT11 �������Ŷ���********************************/
#define      DHT11_Dout_GPIO_PORT                      GPIOE
#define      DHT11_Dout_GPIO_PIN                       GPIO_Pin_6

#define      DHT11_Dout_SCK_APBxClkCmd              	 RCC_APB2PeriphClockCmd
#define      DHT11_Dout_GPIO_CLK                       RCC_APB2Periph_GPIOE


/************************** DHT11 �����궨��********************************/
#define      DHT11_Dout_0					GPIO_ResetBits(DHT11_Dout_GPIO_PORT, DHT11_Dout_GPIO_PIN)	//��PE6Ϊ0
#define      DHT11_Dout_1					GPIO_SetBits(DHT11_Dout_GPIO_PORT, DHT11_Dout_GPIO_PIN)		//��PE6Ϊ1
#define			 DHT11_Dout_IN()			GPIO_ReadInputDataBit(DHT11_Dout_GPIO_PORT, DHT11_Dout_GPIO_PIN)									//��ȡPE6�ĵ�ƽ




/************************** ��������********************************/
void DHT11_Init(void);
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef* DHT11_Data);

#endif /* __BSP_DHT11_H__ */
