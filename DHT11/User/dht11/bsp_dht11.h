#ifndef __BSP_DHT11_H__
#define __BSP_DHT11_H__

#include "stm32f10x.h"
#include "./dwt_delay/core_delay.h" 

/************************** DHT11 数据类型定义********************************/
typedef struct {
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
	
} DHT11_Data_TypeDef;


/************************** 延时********************************/
#define DHT11_DELAY_US(us)  CPU_TS_Tmr_Delay_US(us)	//1us
#define DHT11_DELAY_MS(ms)  CPU_TS_Tmr_Delay_MS(ms)	//1ms

/************************** DHT11 连接引脚定义********************************/
#define      DHT11_Dout_GPIO_PORT                      GPIOE
#define      DHT11_Dout_GPIO_PIN                       GPIO_Pin_6

#define      DHT11_Dout_SCK_APBxClkCmd              	 RCC_APB2PeriphClockCmd
#define      DHT11_Dout_GPIO_CLK                       RCC_APB2Periph_GPIOE


/************************** DHT11 函数宏定义********************************/
#define      DHT11_Dout_0					GPIO_ResetBits(DHT11_Dout_GPIO_PORT, DHT11_Dout_GPIO_PIN)	//置PE6为0
#define      DHT11_Dout_1					GPIO_SetBits(DHT11_Dout_GPIO_PORT, DHT11_Dout_GPIO_PIN)		//置PE6为1
#define			 DHT11_Dout_IN()			GPIO_ReadInputDataBit(DHT11_Dout_GPIO_PORT, DHT11_Dout_GPIO_PIN)									//读取PE6的电平




/************************** 函数声明********************************/
void DHT11_Init(void);
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef* DHT11_Data);

#endif /* __BSP_DHT11_H__ */
