#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c_gpio.h"
#include "bsp_i2c_ee.h"




//extern uint8_t ucTemp;

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
	USART_Config();		//初始化串口配置
	LED_BLUE;
	printf("开发板是stm32f103\n");
	printf("eeprom 软件模拟i2c测试例程 \r\n");
	ee_Erase();	//擦除EEPROM
	if( ee_Test() == 1 ) {
		LED_GREEN;
	} else {
		LED_RED;
	}
	while(1);
	
}
