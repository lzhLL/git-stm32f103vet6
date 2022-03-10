#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_adc.h"



extern uint8_t ucTemp;



void Delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5000; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}

int main(void) {
	// 来到这里的时候，系统的时钟已经被配置成72M。
	//用于保存转换计算后的电压值
	float ADC_ConverValueLocal;
	__IO uint16_t adc_value = 0;
	LED_GPIO_Config();//LED的GPIO初始化配置
	USART_Config();		//初始化串口配置
	ADCx_Init();				//ADC初始化
	
	Usart_SendStr(DEBUG_USARTx, "烟雾传感器MQ-2的实验\n");
	printf("开发板是stm32f103\n");
	while(1) {
		adc_value = ADC_Trans();
		ADC_ConverValueLocal = (float)(adc_value * (3.3 / 4096) );
		printf("\n\r ADC的数值为：0x%x  \r\n", adc_value);
		printf("\n\r ADC的电压值为：%fV \r\n", ADC_ConverValueLocal);
		Delay(1000);
	}
	
}


