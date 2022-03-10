/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  lizh
  * @version V1.0
  * @date    2022-03-04
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  * @attention
  *
  * ������ :Ұ��ָ����STM32F103VET6
  * 
  ******************************************************************************
  */
	
	
#include "bsp_exti.h"


static void EXTI_NVIC_Config(void) {	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/* ����NVICΪ���ȼ���1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = SR501_INT_EXTI_IRQ;		/* �����ж�Դ��PA4 */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	/* ������ռ���ȼ� */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;					/* ���������ȼ� */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;						/* ʹ���ж�ͨ�� */

	NVIC_Init(&NVIC_InitStruct);
	
}


//ʹ���ж�����:PA4�ⲿ�жϳ�ʼ������
void EXIT_SR501_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//�����ж����ȼ�
	EXTI_NVIC_Config();
	
/*--------------------------GPIO����-----------------------------*/
	RCC_APB2PeriphClockCmd(SR501_INT_GPIO_CLK, ENABLE);//��APB2ʱ��
	
	GPIO_InitStruct.GPIO_Pin = SR501_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; 	/* ����Ϊ�������� */	
	
	GPIO_Init(SR501_INT_GPIO_PORT, &GPIO_InitStruct);
	
	
	//��ʼ��EXTI(ѡ������)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);					//��AFIO�Ĵ�����ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);		//ѡ����ΪEXTI Line��GPIO�š�
	
	EXTI_InitStruct.EXTI_Line = SR501_INT_EXTI_LINE;		//��ӦPA4������
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;		/* EXTIΪ�ж�ģʽ */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//����ѡ��������
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	

}
