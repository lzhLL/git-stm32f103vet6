//bsp:board support package�弶֧�ְ�
#include "bsp_led.h"

//LED��GPIO��ʼ������
void LED_GPIO_Config(void) {
	/* ����һ��GPIO_InitTypeDef���͵Ľṹ�� */
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* ����LED��ص�GPIO����ʱ�� */
	RCC_APB2PeriphClockCmd(LED_B_GPIO_CLOCK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED_ALL_GPIO_PIN;
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	
	/*������������Ϊ50MHz */ 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

	/* �ر�����led��	*/
	GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
		
	/* �ر�����led��	*/
	GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);	 
		
	/* �ر�����led��	*/
	GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}
