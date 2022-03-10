/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   HC-SR501��������Ӧ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h" 

//����������
void MCO_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
}


	/// ����ȷ����ʱ
void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */ 
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	  	
	/* ��ʼ��EXTI�жϣ���Ӧ��������Դ�ᴥ���ж�*/
	EXTI_SR501_Config(); 
	
	//MCO_GPIO_Config();//��������ʼ��
	
	/* �ȴ��жϣ�����ʹ���жϷ�ʽ��CPU������ѯ���� */
	while(1)                            
	{
		if( GPIO_ReadInputDataBit(SR501_INT_GPIO_PORT,SR501_INT_GPIO_PIN)  == 0 )
		{			
			GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
			RCC_MCOConfig(RCC_MCO_NoClock);//û�˾������Ͳ�����
			 
		}
	
		Delay(0xFFF);
	}
}
/*********************************************END OF FILE**********************/
