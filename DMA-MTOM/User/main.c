#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
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
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	uint8_t status = 0;
	
	LED_GPIO_Config();//LED��GPIO��ʼ������
	
	//��ʼ��ʱ��������
	GPIO_ResetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
	GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
	GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
	Delay(5000);
	
	MtoM_DMA_Config();

	//���DMA1��6ͨ�����ݴ���ɹ�,������ѭ��
	while( DMA_GetFlagStatus(MTM_DMA_FLAG_TC) == RESET );
	
	status = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	if(0 == status) {
		//�����
		GPIO_ResetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		Delay(5000);
	} else {
		//���̵�
		GPIO_ResetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
		GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
		Delay(5000);
	}
	
	while(1) {
	
	}
	
}
