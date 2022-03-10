#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
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
	// 来到这里的时候，系统的时钟已经被配置成72M。
	
	LED_GPIO_Config();//LED的GPIO初始化配置
	
	while(1) {
		LED_YELLOW;
		Delay(5000);	
		LED_RGBOFF;
		Delay(5000);
	}
	
}
