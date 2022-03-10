#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_dma_mtom.h"

extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];
	
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
	uint8_t status = 0;
	
	LED_GPIO_Config();//LED的GPIO初始化配置
	
	//开始的时候，亮蓝灯
	GPIO_ResetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
	GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
	GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
	Delay(5000);
	
	MtoM_DMA_Config();

	//如果DMA1的6通道数据传输成功,则跳出循环
	while( DMA_GetFlagStatus(MTM_DMA_FLAG_TC) == RESET );
	
	status = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	if(0 == status) {
		//亮红灯
		GPIO_ResetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		Delay(5000);
	} else {
		//亮绿灯
		GPIO_ResetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		Delay(5000);
	}
	
	while(1) {
	
	}
	
}
