#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
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
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	//���ڱ���ת�������ĵ�ѹֵ
	float ADC_ConverValueLocal;
	__IO uint16_t adc_value = 0;
	LED_GPIO_Config();//LED��GPIO��ʼ������
	USART_Config();		//��ʼ����������
	ADCx_Init();				//ADC��ʼ��
	
	Usart_SendStr(DEBUG_USARTx, "��������MQ-2��ʵ��\n");
	printf("��������stm32f103\n");
	while(1) {
		adc_value = ADC_Trans();
		ADC_ConverValueLocal = (float)(adc_value * (3.3 / 4096) );
		printf("\n\r ADC����ֵΪ��0x%x  \r\n", adc_value);
		printf("\n\r ADC�ĵ�ѹֵΪ��%fV \r\n", ADC_ConverValueLocal);
		Delay(1000);
	}
	
}


