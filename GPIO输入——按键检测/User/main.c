#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_key.h"

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
	KEY_GPIO_Config();//KEY1��GPIO��ʼ������
#if 1
	while(1) {
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON ) {
			LED_ALL_TOGGLE;
		} 
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON) {
			LED_B_TOGGLE;
		}
	}
	
#elif 0
	while(1) {
		Key_Func(KEY1_GPIO_PORT, KEY1_GPIO_PIN);

}

#endif
}
