#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"

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
	
	LED_GPIO_Config();//LED��GPIO��ʼ������
	
	while(1) {
		LED_YELLOW;
		Delay(5000);	
		LED_RGBOFF;
		Delay(5000);
	}
	
}
