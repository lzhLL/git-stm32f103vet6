#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_dht11.h"
#include "./systick/bsp_SysTick.h"

void Delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5000; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}

int main(void) {
	DHT11_Data_TypeDef	DHT11_Data;
	SysTick_Init();		/* 初始化系统定时器 */
	USART_Config();		/* 初始化串口配置 */
	DHT11_Init();			/* 初始化DTT11的引脚 */
	
	printf("DHT11温湿度传感器实验\n\r");
	
	while(1) {
		if( DHT11_Read_TempAndHumidity(&DHT11_Data) == SUCCESS) {
			printf("读取成功！\n\r温度：%d.%d ℃， 湿度：%d.%d \n", \
			DHT11_Data.temp_int, DHT11_Data.temp_deci, DHT11_Data.humi_int, DHT11_Data.humi_deci);
		} else {
			printf("读取温湿度失败！\n");
		}
		
		Delay(5000);
	}
	
}
/*************************************END OF FILE******************************/
