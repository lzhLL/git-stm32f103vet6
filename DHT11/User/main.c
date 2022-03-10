#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
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
	SysTick_Init();		/* ��ʼ��ϵͳ��ʱ�� */
	USART_Config();		/* ��ʼ���������� */
	DHT11_Init();			/* ��ʼ��DTT11������ */
	
	printf("DHT11��ʪ�ȴ�����ʵ��\n\r");
	
	while(1) {
		if( DHT11_Read_TempAndHumidity(&DHT11_Data) == SUCCESS) {
			printf("��ȡ�ɹ���\n\r�¶ȣ�%d.%d �棬 ʪ�ȣ�%d.%d \n", \
			DHT11_Data.temp_int, DHT11_Data.temp_deci, DHT11_Data.humi_int, DHT11_Data.humi_deci);
		} else {
			printf("��ȡ��ʪ��ʧ�ܣ�\n");
		}
		
		Delay(5000);
	}
	
}
/*************************************END OF FILE******************************/
