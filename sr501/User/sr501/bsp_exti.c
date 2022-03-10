/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  lizh
  * @version V1.0
  * @date    2022-03-04
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 开发板 :野火指南者STM32F103VET6
  * 
  ******************************************************************************
  */
	
	
#include "bsp_exti.h"


static void EXTI_NVIC_Config(void) {	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/* 配置NVIC为优先级组1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = SR501_INT_EXTI_IRQ;		/* 配置中断源：PA4 */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	/* 配置抢占优先级 */
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;					/* 配置子优先级 */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;						/* 使能中断通道 */

	NVIC_Init(&NVIC_InitStruct);
	
}


//使能中断请求:PA4外部中断初始化函数
void EXIT_SR501_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//配置中断优先级
	EXTI_NVIC_Config();
	
/*--------------------------GPIO配置-----------------------------*/
	RCC_APB2PeriphClockCmd(SR501_INT_GPIO_CLK, ENABLE);//打开APB2时钟
	
	GPIO_InitStruct.GPIO_Pin = SR501_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; 	/* 配置为下拉输入 */	
	
	GPIO_Init(SR501_INT_GPIO_PORT, &GPIO_InitStruct);
	
	
	//初始化EXTI(选输入线)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);					//打开AFIO寄存器的时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);		//选择作为EXTI Line的GPIO脚。
	
	EXTI_InitStruct.EXTI_Line = SR501_INT_EXTI_LINE;		//对应PA4的引脚
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;		/* EXTI为中断模式 */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//触发选择：上升沿
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	

}
