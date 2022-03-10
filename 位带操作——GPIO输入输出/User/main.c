#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_key.h"

#define PBIO_ODR_ADDR		(GPIOB_BASE + 0x0C)
#define PBOUT(n)				(*(unsigned int*)((PBIO_ODR_ADDR & 0xF0000000) + 0x02000000 + ((PBIO_ODR_ADDR & 0x00FFFFFF) << 5) + (n << 2) ))

#define PAIO_IDR_ADDR		(GPIOA_BASE + 0x08)
#define PCIO_IDR_ADDR		(GPIOC_BASE + 0x08)
#define PAIN(n)				(*(unsigned int*)((PAIO_IDR_ADDR & 0xF0000000) + 0x02000000 + ((PAIO_IDR_ADDR & 0x00FFFFFF) << 5) + (n << 2) ))
#define PCIN(n)				(*(unsigned int*)((PCIO_IDR_ADDR & 0xF0000000) + 0x02000000 + ((PCIO_IDR_ADDR & 0x00FFFFFF) << 5) + (n << 2) ))


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
	KEY_GPIO_Config();//KEY1的GPIO初始化配置
#if 0
	while(1) {
		PBOUT(5) = 0;
		PBOUT(1) = 1;
		PBOUT(0) = 1;
		Delay(5000);
		
		PBOUT(0) = 0;
		PBOUT(1) = 1;
		PBOUT(5) = 1;
		Delay(5000);	
		
  	PBOUT(1) = 0;
		PBOUT(0) = 1;
		PBOUT(5) = 1;
		Delay(5000);	
	}
	
	
#elif 1
	while(1) {
		if(1 == PAIN(0)) {
			while(1 == PAIN(0));
			LED_ALL_TOGGLE;
		} 
		if(1 == PCIN(13)) {
			while(1 == PCIN(13));
			LED_B_TOGGLE;
		} 

	}
	
#elif 0
	while(1) {
		Key_Func(KEY1_GPIO_PORT, KEY1_GPIO_PIN);

}

#endif
}
