#include "bsp_exti.h"

//static�ؼ���������������ֻ�ܱ�EXIT_Key_Config(void)�������ã������������ò��˵�
static void EXTI_NVIC_Config(void) {	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//�����ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
	

	//�����ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
}


//ʹ���ж�����:key1�ⲿ�жϳ�ʼ������
void EXIT_Key_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//�����ж����ȼ�
	EXTI_NVIC_Config();
	
/* ��ʼ��GPIOA */
		//��APB2ʱ��
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLOCK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�������룬GPIO��ƽ���ⲿ����
	
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);
	
	
/* ��ʼ��GPIOC */
		//��APB2ʱ��
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLOCK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�������룬GPIO��ƽ���ⲿ����
	
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStruct);	
	
	
	
	//��ʼ��EXTI(ѡ������)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);					//��AFIO�Ĵ�����ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);		//ѡ����ΪEXTI Line��GPIO�š�
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;		//��ӦPA0������
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//�ж�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	//����ѡ��������
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
	//��ʼ��EXTI(ѡ������)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);					//��AFIO�Ĵ�����ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);		//ѡ����ΪEXTI Line��GPIO�š�
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line13;		//��ӦPA0������
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//�ж�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	//����ѡ��������
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);

}
