#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_systick.h"

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
		GPIO_ResetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		//Delay(5000);
		SysTick_Delay_ms(1000);
		
		GPIO_ResetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		SysTick_Delay_ms(1000);
		
		GPIO_ResetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		SysTick_Delay_ms(1000);	
	}
	
}
